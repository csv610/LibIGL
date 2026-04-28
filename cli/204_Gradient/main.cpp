#include <igl/avg_edge_length.h>
#include <igl/barycenter.h>
#include <igl/grad.h>
#include <igl/jet.h>
#include <igl/readDMAT.h>
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>

#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;

  argparse::ArgumentParser program("204_Gradient");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("-s", "--scalar")
    .help("Path to scalar field file (.dmat)")
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
  std::string scalar_path = program.get<std::string>("--scalar");

  MatrixXd V;
  MatrixXi F;

  // Load a mesh in OFF format
  igl::read_triangle_mesh(mesh_path, V, F);

  // Read scalar function values from a file, U: #V by 1
  VectorXd U;
  igl::readDMAT(scalar_path, U);

  // Compute gradient operator: #F*3 by #V
  SparseMatrix<double> G;
  igl::grad(V,F,G);

  // Compute gradient of U
  MatrixXd GU = Map<const MatrixXd>((G*U).eval().data(),F.rows(),3);
  // Compute gradient magnitude
  const VectorXd GU_mag = GU.rowwise().norm();

  if (program.get<bool>("--view")) {
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);

    viewer.data().set_data(U);

    // Average edge length divided by average gradient (for scaling)
    const double max_size = igl::avg_edge_length(V,F) / GU_mag.mean();
    // Draw a black segment in direction of gradient at face barycenters
    MatrixXd BC;
    igl::barycenter(V,F,BC);
    const RowVector3d black(0,0,0);
    viewer.data().add_edges(BC,BC+max_size*GU, black);

    // Hide wireframe
    viewer.data().show_lines = false;

    viewer.launch();
  }

  return 0;
}