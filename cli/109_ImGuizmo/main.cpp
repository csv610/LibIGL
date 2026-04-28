#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <GLFW/glfw3.h>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("109_ImGuizmo");

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

  igl::opengl::glfw::Viewer vr;
  vr.data().set_mesh(V, F);

  igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
  vr.plugins.push_back(&imgui_plugin);

  igl::opengl::glfw::imgui::ImGuizmoWidget gizmo;
  imgui_plugin.widgets.push_back(&gizmo);
  gizmo.T.block(0, 3, 3, 1) =
    0.5 * (V.colwise().maxCoeff() + V.colwise().minCoeff()).transpose().cast<float>();
  const Eigen::Matrix4f T0 = gizmo.T;
  gizmo.callback = [&](const Eigen::Matrix4f & T)
  {
    const Eigen::Matrix4d TT = (T * T0.inverse()).cast<double>().transpose();
    vr.data().set_vertices(
      (V.rowwise().homogeneous() * TT).rowwise().hnormalized());
    vr.data().compute_normals();
  };
  vr.callback_key_pressed = [&](decltype(vr)&, unsigned int key, int mod)
  {
    switch (key)
    {
      case ' ': gizmo.visible = !gizmo.visible; return true;
      case 'W': case 'w': gizmo.operation = ImGuizmo::TRANSLATE; return true;
      case 'E': case 'e': gizmo.operation = ImGuizmo::ROTATE;    return true;
      case 'R': case 'r': gizmo.operation = ImGuizmo::SCALE;     return true;
    }
    return false;
  };

  igl::opengl::glfw::imgui::ImGuiMenu menu;
  imgui_plugin.widgets.push_back(&menu);

  std::cout << R"(
W,w  Switch to translate operation
E,e  Switch to rotate operation
R,r  Switch to scale operation
)";
  vr.launch();
}
