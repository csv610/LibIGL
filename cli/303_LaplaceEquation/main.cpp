#include <igl/boundary_facets.h>
#include <igl/colon.h>
#include <igl/cotmatrix.h>
#include <igl/jet.h>
#include <igl/min_quad_with_fixed.h>
#include <igl/read_triangle_mesh.h>
#include <igl/setdiff.h>
#include <igl/slice.h>
#include <igl/unique.h>
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Sparse>
#include <iostream>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  // --- Argument Parsing ---
  argparse::ArgumentParser program("303_LaplaceEquation");
  program.add_argument("-i", "--input")
    .required()
    .help("Path to mesh file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  using namespace Eigen;
  using namespace std;
  MatrixXd V;
  MatrixXi F;
  
  // --- Mesh Loading ---
  // Load the mesh from the provided path into vertices V and faces F.
  igl::read_triangle_mesh(program.get<std::string>("--input"),V,F);

  // --- Boundary Identification ---
  // 1. Find the boundary edges of the triangle mesh.
  MatrixXi E;
  igl::boundary_facets(F,E);
  // 2. Extract unique boundary vertex indices from the edges.
  VectorXi b,IA,IC;
  igl::unique(E,b,IA,IC);
  // 3. Partition all vertex indices into 'boundary' (b) and 'interior' (in).
  VectorXi all,in;
  igl::colon<int>(0,V.rows()-1,all);
  igl::setdiff(all,b,in,IA);

  // --- Laplacian Construction ---
  // Compute the sparse cotangent Laplacian matrix L.
  SparseMatrix<double> L,L_in_in,L_in_b;
  igl::cotmatrix(V,F,L);
  // Slice L to get sub-matrices for interior-interior and interior-boundary interactions.
  igl::slice(L,in,in,L_in_in);
  igl::slice(L,in,b,L_in_b);

  // --- Dirichlet Boundary Conditions ---
  // We use the Z-coordinate of the boundary vertices as our fixed values.
  VectorXd Z = V.col(2);
  VectorXd bc = Z(b);

  // --- Solve the Laplace Equation (Manual Method) ---
  // Solve the linear system: L_in_in * u_in = -L_in_b * u_b
  // SimplicialLLT is an efficient sparse Cholesky solver.
  SimplicialLLT<SparseMatrix<double > > solver(-L_in_in);
  Z(in) = solver.solve(L_in_b*bc).eval();

  // --- Alternative Method (Shorthand) ---
  // This uses libigl's utility for solving quadratic minimization problems with fixed values.
  igl::min_quad_with_fixed_data<double> mqwf;
  VectorXd B = VectorXd::Zero(V.rows(),1); // Linear term is zero
  VectorXd Beq;                            // No equality constraints
  SparseMatrix<double> Aeq;
  // Precompute the solver for minimizing u' * (-L) * u
  igl::min_quad_with_fixed_precompute((-L).eval(),b,Aeq,true,mqwf);
  igl::min_quad_with_fixed_solve(mqwf,B,bc,Beq,Z);

  // --- Visualization ---
  // Plot the mesh and color it based on the computed field Z.
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().show_lines = false;
  viewer.data().set_data(Z); // Set scalar field for pseudocolor mapping
  viewer.launch();
}
