#include <igl/barycenter.h>
#include <igl/colon.h>
#include <igl/jet.h>
#include <igl/read_triangle_mesh.h>
#include <igl/slice_into.h>
#include <igl/sortrows.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("302_Sort");
  program.add_argument("-i", "--input")
    .required()
    .help("Path to mesh file");
  program.add_argument("-o", "--output")
    .default_value(std::string(""))
    .help("Path to output JSON file");
  program.add_argument("--view")
    .default_value(false)
    .implicit_value(true)
    .help("Enable interactive viewer");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  using namespace Eigen;
  using namespace std;
  MatrixXd V;
  MatrixXi F;
  if (!igl::read_triangle_mesh(program.get<std::string>("--input"),V,F)) {
    std::cerr << "Error: Could not read mesh from " << program.get<std::string>("--input") << std::endl;
    return 1;
  }

  // Sort barycenters lexicographically
  MatrixXd BC,sorted_BC;
  igl::barycenter(V,F,BC);
  VectorXi I,J;
  // sorted_BC = BC(I,:)
  igl::sortrows(BC,true,sorted_BC,I);

  // Output to JSON if requested
  std::string output_path = program.get<std::string>("--output");
  if (!output_path.empty()) {
    nlohmann::json j;
    j["num_faces"] = F.rows();
    std::vector<int> sorted_indices(I.data(), I.data() + I.size());
    j["sorted_face_indices"] = sorted_indices;
    
    std::ofstream o(output_path);
    if (o.is_open()) {
      o << j.dump(4) << std::endl;
      std::cout << "Saved sorted indices to: " << output_path << std::endl;
    } else {
      std::cerr << "Error: Could not write to " << output_path << std::endl;
    }
  }

  // Get sorted "place" from sorted indices
  J.resize(I.rows());
  // J(I) = 1:numel(I)
  igl::slice_into(igl::colon<int>(0,I.size()-1),I,J);

  // Pseudo-color based on sorted place
  MatrixXd C;
  igl::jet(J,true,C);

  // Plot the mesh with pseudocolors if requested
  if (program.get<bool>("--view")) {
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.data().set_colors(C);
    viewer.launch();
  } else {
    std::cout << "Processing complete. (Viewer skipped; use --view to enable it)" << std::endl;
  }
}
