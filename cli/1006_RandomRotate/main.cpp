#include <igl/read_triangle_mesh.h>
#include <igl/write_triangle_mesh.h>
#include <igl/random_quaternion.h>
#include <argparse/argparse.hpp>
#include <iostream>
#include <Eigen/Geometry>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("1006_RandomRotate");
  program.add_argument("-i", "--input").required().help("Path to input mesh file");
  program.add_argument("-o", "--output").required().help("Path to output mesh file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  Eigen::MatrixXd V;
  Eigen::MatrixXi F;

  std::string input_file = program.get<std::string>("--input");
  std::string output_file = program.get<std::string>("--output");

  // Load mesh
  if (!igl::read_triangle_mesh(input_file, V, F)) {
    std::cerr << "Error: Could not read mesh from " << input_file << std::endl;
    return 1;
  }

  // Generate a random rotation quaternion
  Eigen::Quaterniond q = igl::random_quaternion<double>();
  
  std::cout << "Applying random rotation: " 
            << q.w() << " + " << q.x() << "i + " << q.y() << "j + " << q.z() << "k" << std::endl;

  // Apply rotation to all vertices
  // V is #V x 3, so we multiply by the transposed rotation matrix
  V = (V * q.toRotationMatrix().transpose()).eval();

  // Save the result
  if (!igl::write_triangle_mesh(output_file, V, F)) {
    std::cerr << "Error: Could not write mesh to " << output_file << std::endl;
    return 1;
  }

  std::cout << "Successfully saved rotated mesh to " << output_file << std::endl;

  return 0;
}
