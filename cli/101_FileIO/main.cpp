#include <igl/read_triangle_mesh.h>
#include <igl/writeOBJ.h>
#include <iostream>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("101_FileIO");

  program.add_argument("-i", "--input")
    .help("Path to input mesh file")
    .required();

  program.add_argument("-o", "--output")
    .help("Path to output mesh file")
    .default_value(std::string("cube.obj"));

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

  std::cout << "Vertices: " << std::endl << V << std::endl;
  std::cout << "Faces:    " << std::endl << F << std::endl;

  auto output_path = program.get<std::string>("--output");
  igl::writeOBJ(output_path, V, F);
  std::cout << "Saved to " << output_path << std::endl;

  return 0;
}
