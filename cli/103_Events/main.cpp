#include <igl/opengl/glfw/Viewer.h>
#include <iostream>
#include <argparse/argparse.hpp>
#include <igl/read_triangle_mesh.h>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("103_Events");

  program.add_argument("-i1", "--input1")
    .help("First mesh file")
    .required();

  program.add_argument("-i2", "--input2")
    .help("Second mesh file")
    .required();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  Eigen::MatrixXd V1, V2;
  Eigen::MatrixXi F1, F2;

  auto mesh1_path = program.get<std::string>("--input1");
  auto mesh2_path = program.get<std::string>("--input2");

  igl::read_triangle_mesh(mesh1_path, V1, F1);
  igl::read_triangle_mesh(mesh2_path, V2, F2);

  std::cout << "1 Switch to bump mesh\n2 Switch to fertility mesh\n";

  igl::opengl::glfw::Viewer viewer;
  viewer.callback_key_down = [&](igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier) {
    std::cout << "Key: " << key << " " << (unsigned int)key << std::endl;
    if (key == '1') {
      viewer.data().clear();
      viewer.data().set_mesh(V1, F1);
      viewer.core().align_camera_center(V1, F1);
    } else if (key == '2') {
      viewer.data().clear();
      viewer.data().set_mesh(V2, F2);
      viewer.core().align_camera_center(V2, F2);
    }
    return false;
  };
  viewer.data().set_mesh(V1, F1);
  viewer.launch();

  return 0;
}
