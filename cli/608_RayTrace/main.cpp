#include <igl/gaussian_curvature.h>
#include <igl/massmatrix.h>
#include <igl/invert_diag.h>
#include <igl/read_triangle_mesh.h>
#include <igl/stb/write_image.h>
#include <igl/PI.h>
#include <Eigen/Geometry>
// embree
#include <igl/embree/EmbreeRenderer.h>

#include <argparse/argparse.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("608_RayTrace");
  program.add_argument("-i", "--input").required().help("Path to mesh file");
  program.add_argument("-o", "--output").required().help("Path to output PNG file");
  program.add_argument("-z", "--zoom").default_value(1.5).help("Zoom level (magnification ratio)").scan<'g', double>();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  int width=640;
  int height=480;

  Eigen::MatrixXd V;
  Eigen::MatrixXi F;

  std::string mesh_file = program.get<std::string>("--input");
  std::string png_file = program.get<std::string>("--output");
  double zoom = program.get<double>("--zoom");

  // Load mesh
  igl::read_triangle_mesh(mesh_file.c_str(), V,F);

  Eigen::VectorXd K;
  // Compute integral of Gaussian curvature
  igl::gaussian_curvature(V,F,K);
  // Compute mass matrix
  Eigen::SparseMatrix<double> M,Minv;
  igl::massmatrix(V,F,igl::MASSMATRIX_TYPE_DEFAULT,M);
  igl::invert_diag(M,Minv);
  // Divide by area to get integral average
  K = (Minv*K).eval();

  // embree object
  igl::embree::EmbreeRenderer er;
  er.set_mesh(V,F,true);

  er.set_colors(Eigen::RowVector3d(0.5,0.5,0.5));
  //er.set_data(K,igl::COLOR_MAP_TYPE_JET);

  Eigen::Matrix3d rot_matrix;

  // specify rotation
  rot_matrix =  Eigen::AngleAxisd( 10*igl::PI/180.0, Eigen::Vector3d::UnitX())
              * Eigen::AngleAxisd(  5*igl::PI/180.0, Eigen::Vector3d::UnitY())
              * Eigen::AngleAxisd(  4*igl::PI/180.0, Eigen::Vector3d::UnitZ());
  er.set_rot(rot_matrix);

  er.set_zoom(zoom);
  er.set_orthographic(false);

  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R(width, height);
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> G(width, height);
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> B(width, height);
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> A(width, height);

  // render view using embree
  er.render_buffer(R,G,B,A);

  std::cout<<"Rendered scene saved to "<<png_file<<std::endl;

  // save to PNG file
  igl::stb::write_image(png_file.c_str(),R,G,B,A);
  return 0;
}
