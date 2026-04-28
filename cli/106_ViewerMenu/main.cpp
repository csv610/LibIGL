#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <iostream>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("106_ViewerMenu");

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

  igl::opengl::glfw::imgui::ImGuiPlugin plugin;
  viewer.plugins.push_back(&plugin);
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  plugin.widgets.push_back(&menu);

  double doubleVariable = 0.1f;

  menu.callback_draw_viewer_menu = [&]()
  {
    menu.draw_viewer_menu();

    if (ImGui::CollapsingHeader("New Group", ImGuiTreeNodeFlags_DefaultOpen))
    {
      ImGui::InputDouble("double", &doubleVariable, 0, 0, "%.4f");

      static bool boolVariable = true;
      if (ImGui::Checkbox("bool", &boolVariable))
      {
        std::cout << "boolVariable: " << std::boolalpha << boolVariable << std::endl;
      }

      enum Orientation { Up = 0, Down, Left, Right };
      static Orientation dir = Up;
      ImGui::Combo("Direction", (int *)(&dir), "Up\0Down\0Left\0Right\0\0");

      static int num_choices = 3;
      static std::vector<std::string> choices;
      static int idx_choice = 0;
      if (ImGui::InputInt("Num letters", &num_choices))
      {
        num_choices = std::max(1, std::min(26, num_choices));
      }
      if (num_choices != (int)choices.size())
      {
        choices.resize(num_choices);
        for (int i = 0; i < num_choices; ++i)
          choices[i] = std::string(1, 'A' + i);
        if (idx_choice >= num_choices)
          idx_choice = num_choices - 1;
      }
      ImGui::Combo("Letter", &idx_choice, choices);

      if (ImGui::Button("Print Hello", ImVec2(-1, 0)))
      {
        std::cout << "Hello\n";
      }
    }
  };

  menu.callback_draw_custom_window = [&]()
  {
    ImGui::SetNextWindowPos(ImVec2(180.f * menu.menu_scaling(), 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 160), ImGuiCond_FirstUseEver);
    ImGui::Begin(
        "New Window", nullptr,
        ImGuiWindowFlags_NoSavedSettings
    );

    ImGui::PushItemWidth(-80);
    ImGui::DragScalar("double", ImGuiDataType_Double, &doubleVariable, 0.1, 0, 0, "%.4f");
    ImGui::PopItemWidth();

    static std::string str = "bunny";
    ImGui::InputText("Name", str);

    ImGui::End();
  };

  viewer.data().set_mesh(V, F);
  viewer.data().add_label(viewer.data().V.row(0) + viewer.data().V_normals.row(0).normalized() * 0.005, "Hello World!");
  viewer.launch();

  return 0;
}
