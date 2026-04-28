#include <igl/opengl/glfw/Viewer.h>
#include <argparse/argparse.hpp>
#include <igl/read_triangle_mesh.h>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("104_Colors");

  program.add_argument("-i", "--input")
    .help("Path to input mesh file")
    .required();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  Eigen::MatrixXd C;

  auto input_path = program.get<std::string>("--input");
  igl::read_triangle_mesh(input_path, V, F);

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);

  C =
    (V.rowwise() - V.colwise().minCoeff()).array().rowwise() /
    (V.colwise().maxCoeff() - V.colwise().minCoeff()).array();

  viewer.data().set_colors(C);
  viewer.launch();

  return 0;
}
