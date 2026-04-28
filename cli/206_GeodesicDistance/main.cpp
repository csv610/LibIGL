#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/exact_geodesic.h>
#include <igl/unproject_onto_mesh.h>
#include <igl/parula.h>
#include <igl/isolines_map.h>
#include <igl/PI.h>
#include <iostream>
#include <fstream>
#include <string>
#include <argparse/argparse.hpp>


int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;

  argparse::ArgumentParser program("206_GeodesicDistance");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("-s", "--source")
    .help("Index of the source vertex")
    .default_value(0)
    .scan<'i', int>();
  program.add_argument("-o", "--output")
    .help("Path to output distance file")
    .default_value(std::string(""));
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
  std::string output_path = program.get<std::string>("--output");
  if (output_path.empty()) {
    size_t lastdot = mesh_path.find_last_of(".");
    if (lastdot == std::string::npos) {
      output_path = mesh_path + ".dists";
    } else {
      output_path = mesh_path.substr(0, lastdot) + ".dists";
    }
  }

  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  // Load a mesh in OFF format
  igl::read_triangle_mesh(mesh_path, V, F);

  const auto update_distance = [&](igl::opengl::glfw::Viewer* viewer, const int vid)
  {
    Eigen::VectorXi VS,FS,VT,FT;
    // The selected vertex is the source
    VS.resize(1);
    VS << vid;
    // All vertices are the targets
    VT.setLinSpaced(V.rows(),0,V.rows()-1);
    Eigen::VectorXd d;
    std::cout<<"Computing geodesic distance to vertex "<<vid<<"..."<<std::endl;
    igl::exact_geodesic(V,F,VS,FS,VT,FT,d);

    // Save to file
    std::ofstream out(output_path);
    if (out.is_open()) {
      for (int i = 0; i < d.size(); ++i) {
        out << i << " " << d(i) << "\n";
      }
      std::cout << "Distances saved to: " << output_path << std::endl;
    } else {
      std::cerr << "Error: Could not open " << output_path << " for writing." << std::endl;
    }

    if (viewer) {
      // Plot the mesh
      Eigen::MatrixXd CM;
      igl::parula(Eigen::VectorXd::LinSpaced(21,0,1).eval(),false,CM);
      igl::isolines_map(Eigen::MatrixXd(CM),CM);
      viewer->data().set_colormap(CM);
      viewer->data().set_data(d);
    }
  };

  if (program.get<bool>("--view")) {
    igl::opengl::glfw::Viewer viewer;

    // Plot a distance when a vertex is picked
    viewer.callback_mouse_down =
    [&](igl::opengl::glfw::Viewer& __viewer, int, int)->bool
    {
      int fid;
      Eigen::Vector3f bc;
      // Cast a ray in the view direction starting from the mouse position
      double x = __viewer.current_mouse_x;
      double y = __viewer.core().viewport(3) - __viewer.current_mouse_y;
      if(igl::unproject_onto_mesh(
        Eigen::Vector2f(x,y),
        __viewer.core().view,
        __viewer.core().proj,
        __viewer.core().viewport,
        V,
        F,
        fid,
        bc))
      {
        int max;
        bc.maxCoeff(&max);
        int vid = F(fid,max);
        update_distance(&__viewer, vid);
        return true;
      }
      return false;
    };
    viewer.data().set_mesh(V,F);
    viewer.data().show_lines = false;

    cout << "Click on mesh to define new source.\n" << std::endl;
    update_distance(&viewer, program.get<int>("--source"));
    return viewer.launch();
  } else {
    // Default to provided source vertex if no viewer
    update_distance(nullptr, program.get<int>("--source"));
  }

  return 0;
}
