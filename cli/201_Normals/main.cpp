#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/per_vertex_normals.h>
#include <igl/per_face_normals.h>
#include <igl/per_corner_normals.h>
#include <iostream>
#include <string>
#include <fstream>
#include <argparse/argparse.hpp>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

Eigen::MatrixXd N_vertices;
Eigen::MatrixXd N_faces;
Eigen::MatrixXd N_corners;


// This function is called every time a keyboard button is pressed
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
  switch(key)
  {
    case '1':
      viewer.data().set_normals(N_faces);
      return true;
    case '2':
      viewer.data().set_normals(N_vertices);
      return true;
    case '3':
      viewer.data().set_normals(N_corners);
      return true;
    default: break;
  }
  return false;
}

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("Mesh_Normals");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("-c", "--crease")
    .help("Crease angle for corner normals (degrees)")
    .required()
    .scan<'g', double>();
  program.add_argument("-o", "--output")
    .help("Path to output JSON file")
    .default_value(std::string(""));
  program.add_argument("-t", "--type")
    .help("Type of normals to save (face, vertex, corner)")
    .default_value(std::string("vertex"));
  program.add_argument("--view")
    .help("Launch viewer")
    .default_value(false)
    .implicit_value(true);

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  std::string mesh_path = program.get<std::string>("--input");
  double crease_angle = program.get<double>("--crease");

  // Load a mesh in OFF format
  if (!igl::read_triangle_mesh(mesh_path, V, F)) {
    std::cerr << "Failed to load mesh from " << mesh_path << std::endl;
    return 1;
  }

  // Compute per-face normals
  igl::per_face_normals(V,F,N_faces);

  // Compute per-vertex normals
  igl::per_vertex_normals(V,F,N_vertices);

  // Compute per-corner normals, |dihedral angle| > crease_angle degrees --> crease
  igl::per_corner_normals(V,F,crease_angle,N_corners);

  std::string output_path = program.get<std::string>("--output");
  if (!output_path.empty()) {
    std::ofstream out(output_path);
    if (out.is_open()) {
        std::string type = program.get<std::string>("--type");
        Eigen::MatrixXd* N_ptr = &N_vertices;
        if (type == "face") N_ptr = &N_faces;
        else if (type == "corner") N_ptr = &N_corners;
        
        out << "{\n";
        out << "  \"type\": \"" << type << "\",\n";
        out << "  \"crease_angle\": " << crease_angle << ",\n";
        out << "  \"data\": [\n";
        for (int i = 0; i < N_ptr->rows(); ++i) {
            out << "    [" << (*N_ptr)(i, 0) << ", " << (*N_ptr)(i, 1) << ", " << (*N_ptr)(i, 2) << "]";
            if (i < N_ptr->rows() - 1) out << ",";
            out << "\n";
        }
        out << "  ]\n";
        out << "}\n";
        out.close();
        std::cout << "Successfully saved " << type << " normals to " << output_path << std::endl;
    } else {
        std::cerr << "Error: Could not open output file " << output_path << std::endl;
        return 1;
    }
  }

  if (program.get<bool>("--view")) {
    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.callback_key_down = &key_down;
    viewer.data().show_lines = false;
    viewer.data().set_mesh(V, F);
    viewer.data().set_normals(N_faces);
    std::cout<<
      "Press '1' for per-face normals."<<std::endl<<
      "Press '2' for per-vertex normals."<<std::endl<<
      "Press '3' for per-corner normals."<<std::endl;
    viewer.launch();
  }

  return 0;
}
