#include <igl/gaussian_curvature.h>
#include <igl/massmatrix.h>
#include <igl/invert_diag.h>
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <argparse/argparse.hpp>

using namespace std;
using namespace Eigen;

int main(int argc, char *argv[])
{

  argparse::ArgumentParser program("202_GaussianCurvature");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("-o", "--output")
    .help("Path to output JSON file")
    .default_value(std::string(""));
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
  std::string output_path = program.get<std::string>("--output");

  MatrixXd V;
  MatrixXi F;
  igl::read_triangle_mesh(mesh_path, V, F);

  VectorXd K;
  // Compute integral of Gaussian curvature
  igl::gaussian_curvature(V,F,K);
  // Compute mass matrix
  SparseMatrix<double> M,Minv;
  igl::massmatrix(V,F,igl::MASSMATRIX_TYPE_DEFAULT,M);
  igl::invert_diag(M,Minv);
  // Divide by area to get integral average
  K = (Minv*K).eval();

  if (!output_path.empty()) {
    std::ofstream out(output_path);
    if (out.is_open()) {
      out << "{\n";
      out << "  \"input\": \"" << mesh_path << "\",\n";
      out << "  \"gaussian_curvature\": [\n";
      for (int i = 0; i < K.size(); ++i) {
        out << "    " << K(i) << (i == K.size() - 1 ? "" : ",") << "\n";
      }
      out << "  ]\n";
      out << "}\n";
      out.close();
      std::cout << "Output saved to " << output_path << std::endl;
    } else {
      std::cerr << "Failed to open output file: " << output_path << std::endl;
    }
  }

  if (program.get<bool>("--view")) {
    // Plot the mesh with pseudocolors
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.data().set_data(K);
    viewer.launch();
  }

  return 0;
}
