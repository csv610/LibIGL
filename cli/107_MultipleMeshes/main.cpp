#include <igl/opengl/glfw/Viewer.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("107_MultipleMeshes");

  program.add_argument("-i", "--input")
    .help("Comma-separated list of mesh files to load")
    .required();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  std::string mesh_list = program.get<std::string>("--input");
  std::vector<std::string> names;
  std::stringstream ss(mesh_list);
  std::string name;
  while (std::getline(ss, name, ',')) {
    names.push_back(name);
  }

  igl::opengl::glfw::Viewer viewer;
  std::map<int, Eigen::RowVector3d> colors;
  int last_selected = -1;

  for (const auto& n : names)
  {
    std::string full_path = std::string(TUTORIAL_SHARED_PATH) + "/" + n;
    viewer.load_mesh_from_file(full_path);
    colors.emplace(viewer.data().id, 0.5 * Eigen::RowVector3d::Random().array() + 0.5);
  }

  viewer.callback_key_down =
    [&](igl::opengl::glfw::Viewer&, unsigned int key, int mod)
  {
    if (key == GLFW_KEY_BACKSPACE)
    {
      int old_id = viewer.data().id;
      if (viewer.erase_mesh(viewer.selected_data_index))
      {
        colors.erase(old_id);
        last_selected = -1;
      }
      return true;
    }
    return false;
  };

  viewer.callback_pre_draw =
    [&](igl::opengl::glfw::Viewer&)
  {
    if (last_selected != viewer.selected_data_index)
    {
      for (auto& data : viewer.data_list)
      {
        data.set_colors(colors[data.id]);
      }
      viewer.data_list[viewer.selected_data_index].set_colors(Eigen::RowVector3d(0.9, 0.1, 0.1));
      last_selected = viewer.selected_data_index;
    }
    return false;
  };

  viewer.launch();
  return EXIT_SUCCESS;
}
