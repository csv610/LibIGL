#include <igl/opengl/glfw/Viewer.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <map>
#include <argparse/argparse.hpp>

int main(int argc, char * argv[])
{
argparse::ArgumentParser program("108_MultipleViews");
 
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

  std::string mesh1_path = std::string(TUTORIAL_SHARED_PATH) + "/" + program.get<std::string>("--input1");
  std::string mesh2_path = std::string(TUTORIAL_SHARED_PATH) + "/" + program.get<std::string>("--input2");

  igl::opengl::glfw::Viewer viewer;

  viewer.load_mesh_from_file(mesh1_path);
  viewer.load_mesh_from_file(mesh2_path);

  unsigned int left_view, right_view;
  int cube_id = viewer.data_list[0].id;
  int sphere_id = viewer.data_list[1].id;
  viewer.callback_init = [&](igl::opengl::glfw::Viewer &)
  {
    viewer.core().viewport = Eigen::Vector4f(0, 0, 640, 800);
    left_view = viewer.core_list[0].id;
    right_view = viewer.append_core(Eigen::Vector4f(640, 0, 640, 800));
    return false;
  };

  viewer.callback_key_down = [&](igl::opengl::glfw::Viewer &, unsigned int key, int mod)
  {
    if (key == GLFW_KEY_SPACE)
    {
      viewer.data(cube_id).set_visible(false, left_view);
      viewer.data(sphere_id).set_visible(false, right_view);
    }
    return false;
  };

  viewer.callback_post_resize = [&](igl::opengl::glfw::Viewer &v, int w, int h) {
    v.core( left_view).viewport = Eigen::Vector4f(0, 0, w / 2, h);
    v.core(right_view).viewport = Eigen::Vector4f(w / 2, 0, w - (w / 2), h);
    return true;
  };

  viewer.launch();
  return EXIT_SUCCESS;
}
