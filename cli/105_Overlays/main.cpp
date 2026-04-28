#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <sstream>
#include <argparse/argparse.hpp>
#include <igl/read_triangle_mesh.h>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("105_Overlays");

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

  Eigen::Vector3d m = V.colwise().minCoeff();
  Eigen::Vector3d M = V.colwise().maxCoeff();

  Eigen::MatrixXd V_box(8, 3);
  V_box <<
    m(0), m(1), m(2),
    M(0), m(1), m(2),
    M(0), M(1), m(2),
    m(0), M(1), m(2),
    m(0), m(1), M(2),
    M(0), m(1), M(2),
    M(0), M(1), M(2),
    m(0), M(1), M(2);

  Eigen::MatrixXi E_box(12, 2);
  E_box <<
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    7, 3;

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().add_points(V_box, Eigen::RowVector3d(1, 0, 0));

  for (unsigned i = 0; i < E_box.rows(); ++i)
    viewer.data().add_edges(
      V_box.row(E_box(i, 0)),
      V_box.row(E_box(i, 1)),
      Eigen::RowVector3d(1, 0, 0));

  std::stringstream l1;
  l1 << m(0) << ", " << m(1) << ", " << m(2);
  viewer.data().add_label(m + Eigen::Vector3d(-0.007, 0, 0), l1.str());
  std::stringstream l2;
  l2 << M(0) << ", " << M(1) << ", " << M(2);
  viewer.data().add_label(M + Eigen::Vector3d(0.007, 0, 0), l2.str());
  viewer.data().show_custom_labels = true;

  igl::opengl::glfw::imgui::ImGuiPlugin plugin;
  viewer.plugins.push_back(&plugin);
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  plugin.widgets.push_back(&menu);
  menu.callback_draw_viewer_window = []() {};

  viewer.launch();
  return 0;
}
