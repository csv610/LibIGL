#include <igl/read_triangle_mesh.h>
#include <igl/heat_geodesics.h>
#include <igl/avg_edge_length.h>
#include <argparse/argparse.hpp>
#include <Eigen/Core>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

/**
 * CLI tool to calculate geodesic heat distance from given sources on a mesh.
 */
int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("heat_distance");
  program.add_argument("-i", "--input").required().help("Path to input mesh file");
  program.add_argument("-s", "--sources").required().help("Comma-separated list of source vertex indices (e.g., '0,10,42')");
  program.add_argument("-t", "--time").default_value(0.0).scan<'g', double>().help("Time parameter for heat diffusion (0.0 for auto: squared avg edge length)");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error parsing arguments: " << e.what() << std::endl;
    std::cerr << program << std::endl;
    return 1;
  }

  std::string mesh_path = program.get<std::string>("--input");
  std::string sources_str = program.get<std::string>("--sources");
  double t = program.get<double>("--time");

  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  if (!igl::read_triangle_mesh(mesh_path, V, F)) {
    std::cerr << "Error: could not read mesh file " << mesh_path << std::endl;
    return 1;
  }

  // Automatic time parameter selection if not provided
  if (t == 0.0) {
    t = std::pow(igl::avg_edge_length(V, F), 2);
  }

  // Parse source indices
  std::vector<int> sources_vec;
  std::stringstream ss(sources_str);
  std::string segment;
  while (std::getline(ss, segment, ',')) {
    try {
      if (!segment.empty()) {
        sources_vec.push_back(std::stoi(segment));
      }
    } catch (const std::exception& e) {
      std::cerr << "Error: invalid source index '" << segment << "'. Must be an integer." << std::endl;
      return 1;
    }
  }

  if (sources_vec.empty()) {
    std::cerr << "Error: no source indices provided." << std::endl;
    return 1;
  }

  Eigen::VectorXi gamma(sources_vec.size());
  for (size_t i = 0; i < sources_vec.size(); ++i) {
    if (sources_vec[i] < 0 || sources_vec[i] >= V.rows()) {
      std::cerr << "Error: source index " << sources_vec[i] << " out of bounds (0 to " << V.rows() - 1 << ")." << std::endl;
      return 1;
    }
    gamma(i) = sources_vec[i];
  }

  // Precompute heat geodesics data
  igl::HeatGeodesicsData<double> data;
  if (!igl::heat_geodesics_precompute(V, F, t, data)) {
    std::cerr << "Error: heat_geodesics_precompute failed." << std::endl;
    return 1;
  }

  // Solve for distance map
  Eigen::VectorXd D;
  igl::heat_geodesics_solve(data, gamma, D);

  // Output distance map of nodes
  // Each line corresponds to the distance of vertex i
  for (int i = 0; i < D.size(); ++i) {
    std::cout << D(i) << std::endl;
  }

  return 0;
}
