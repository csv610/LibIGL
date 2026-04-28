#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/exact_geodesic.h>
#include <igl/jet.h>
#include <igl/slice.h>
#include <iostream>
#include <vector>
#include <string>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;

  argparse::ArgumentParser program("1005_GeodesicVoronoiDiagram");
  program.add_argument("-i", "--input")
    .help("Path to mesh file")
    .required();
  program.add_argument("-n", "--num_sources")
    .help("Number of Voronoi sources to identify")
    .default_value(10)
    .scan<'i', int>();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  string mesh_path = program.get<string>("--input");
  int n = program.get<int>("--num_sources");

  MatrixXd V;
  MatrixXi F;
  if (!igl::read_triangle_mesh(mesh_path, V, F)) {
    cerr << "Error: Could not read mesh from " << mesh_path << endl;
    return 1;
  }

  cout << "Identifying " << n << " sources using Optimized Farthest Point Sampling..." << endl;

  VectorXi VS(n);       // Selected sources
  VectorXd min_D(V.rows()); // Minimum distance to any identified source
  min_D.setConstant(numeric_limits<double>::infinity());
  VectorXi J(V.rows()); // Index of closest source
  J.setConstant(-1);

  // Targets are always all vertices
  VectorXi VT = VectorXi::LinSpaced(V.rows(), 0, V.rows() - 1);
  VectorXi FS, FT;

  // First source is vertex 0
  int current_new_source = 0;

  for (int i = 0; i < n; ++i) {
    cout << "Step " << (i+1) << "/" << n << ": Adding source at vertex " << current_new_source << "..." << endl;
    VS(i) = current_new_source;

    // 1. Compute exact geodesic distance from ONLY the NEWEST source
    VectorXi single_source(1);
    single_source(0) = current_new_source;
    VectorXd new_D;
    igl::exact_geodesic(V, F, single_source, FS, VT, FT, new_D);

    // 2. Update the running minimum distance and Voronoi labels
    for (int v = 0; v < V.rows(); ++v) {
      if (new_D(v) < min_D(v)) {
        min_D(v) = new_D(v);
        J(v) = i; // This vertex now belongs to the i-th Voronoi cell
      }
    }

    if (i < n - 1) {
      // 3. The next source is the vertex farthest from the current set of sources
      int max_idx;
      min_D.maxCoeff(&max_idx);
      current_new_source = max_idx;
    }
  }

  // After FPS, we re-run exact_geodesic once with all sources to get the true Voronoi labels J
  // Using the new 8-parameter overload
  cout << "Calculating true Geodesic Voronoi Diagram labels..." << endl;
  igl::exact_geodesic(V, F, VS, FS, VT, FT, min_D, J);

  cout << "Finished. Sources found at vertex indices: " << VS.transpose() << endl;

  // Create colors for the Voronoi cells
  MatrixXd C(V.rows(), 3);
  MatrixXd SourceColors;
  igl::jet(VectorXd::LinSpaced(n, 0, 1).eval(), false, SourceColors);

  for (int v = 0; v < V.rows(); ++v) {
    C.row(v) = SourceColors.row(J(v));
  }

  // Launch viewer
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_colors(C);
  
  // Highlight the sources as red points
  MatrixXd V_sources;
  igl::slice(V, VS, 1, V_sources);
  viewer.data().add_points(V_sources, RowVector3d(1, 0, 0));
  viewer.data().point_size = 10;

  cout << "\nShowing Geodesic Voronoi Diagram with " << n << " cells." << endl;
  cout << "Red dots indicate the source vertices." << endl;

  viewer.launch();

  return 0;
}
