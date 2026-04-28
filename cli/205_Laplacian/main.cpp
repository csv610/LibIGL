#include <igl/barycenter.h>
#include <igl/cotmatrix.h>
#include <igl/doublearea.h>
#include <igl/grad.h>
#include <igl/jet.h>
#include <igl/massmatrix.h>
#include <igl/per_vertex_normals.h>
#include <igl/readDMAT.h>
#include <igl/read_triangle_mesh.h>
#include <igl/repdiag.h>
#include <igl/opengl/glfw/Viewer.h>

#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

Eigen::MatrixXd V,U;
Eigen::MatrixXi F;
Eigen::SparseMatrix<double> L;
igl::opengl::glfw::Viewer viewer;

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;

  argparse::ArgumentParser program("205_Laplacian");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("--view")
    .help("Launch viewer")
    .default_value(false)
    .implicit_value(true);

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  std::string mesh_path = program.get<std::string>("--input");

  // Load a mesh in OFF format
  igl::read_triangle_mesh(mesh_path, V, F);

  // Compute Laplace-Beltrami operator: #V by #V
  igl::cotmatrix(V,F,L);

  // Alternative construction of same Laplacian
  SparseMatrix<double> G,K;
  // Gradient/Divergence
  igl::grad(V,F,G);
  // Diagonal per-triangle "mass matrix"
  VectorXd dblA;
  igl::doublearea(V,F,dblA);
  // Place areas along diagonal #dim times
  const auto & T = 1.*(dblA.replicate(3,1)*0.5).asDiagonal();
  // Laplacian K built as discrete divergence of gradient or equivalently
  // discrete Dirichelet energy Hessian
  K = -G.transpose() * T * G;
  cout<<"|K-L|: "<<(K-L).norm()<<endl;

  const auto &key_down = [](igl::opengl::glfw::Viewer &viewer,unsigned char key,int mod)->bool
  {
    switch(key)
    {
      case 'r':
      case 'R':
        U = V;
        break;
      case ' ':
      {
        // Recompute just mass matrix on each step
        SparseMatrix<double> M;
        igl::massmatrix(U,F,igl::MASSMATRIX_TYPE_BARYCENTRIC,M);
        // Solve (M-delta*L) U = M*U
        const auto & S = (M - 0.001*L);
        Eigen::SimplicialLLT<Eigen::SparseMatrix<double > > solver(S);
        assert(solver.info() == Eigen::Success);
        U = solver.solve(M*U).eval();
        // Compute centroid and subtract (also important for numerics)
        VectorXd dblA;
        igl::doublearea(U,F,dblA);
        double area = 0.5*dblA.sum();
        MatrixXd BC;
        igl::barycenter(U,F,BC);
        RowVector3d centroid(0,0,0);
        for(int i = 0;i<BC.rows();i++)
        {
          centroid += 0.5*dblA(i)/area*BC.row(i);
        }
        U.rowwise() -= centroid;
        // Normalize to unit surface area (important for numerics)
        U.array() /= sqrt(area);
        break;
      }
      default:
        return false;
    }
    // Send new positions, update normals, recenter
    viewer.data().set_vertices(U);
    viewer.data().compute_normals();
    viewer.core().align_camera_center(U,F);
    return true;
  };


  // Use original normals as pseudo-colors
  MatrixXd N;
  igl::per_vertex_normals(V,F,N);
  MatrixXd C = N.rowwise().normalized().array()*0.5+0.5;

  if (program.get<bool>("--view")) {
    // Initialize smoothing with base mesh
    U = V;
    viewer.data().set_mesh(U, F);
    viewer.data().set_colors(C);
    viewer.callback_key_down = key_down;

    cout<<"Press [space] to smooth."<<std::endl;;
    cout<<"Press [r] to reset."<<std::endl;;
    return viewer.launch();
  }

  return 0;
}