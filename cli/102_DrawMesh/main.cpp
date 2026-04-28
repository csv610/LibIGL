#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("102_DrawMesh");

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

  auto input_path = program.get<std::string>("--input");
  igl::read_triangle_mesh(input_path, V, F);

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.launch();

  return 0;
}
