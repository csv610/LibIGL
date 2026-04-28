#include "get_mesh.h"
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/jet.h>
#include <Eigen/Core>
#include <argparse/argparse.hpp>
#include <string>


int main(int argc, char * argv[])
{
  argparse::ArgumentParser program("610_CSGTree");
  program.add_argument("-i1", "--input1").required().help("Path to cube mesh");
  program.add_argument("-i2", "--input2").required().help("Path to sphere mesh");
  program.add_argument("-i3", "--input3").required().help("Path to x-cylinder mesh");
  program.add_argument("-i4", "--input4").required().help("Path to y-cylinder mesh");
  program.add_argument("-i5", "--input5").required().help("Path to z-cylinder mesh");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  using namespace Eigen;
  using namespace std;
  using namespace igl;
  cout<<R"(
 [,]  Toggle between boolean sub-tree operations
 )";

  MatrixXi FA,FB,FC,FD,FE;
  MatrixXd VA,VB,VC,VD,VE;
  // Read in inputs as double precision floating point meshes
  read_triangle_mesh(program.get<std::string>("--input1")     ,VA,FA);
  read_triangle_mesh(program.get<std::string>("--input2")   ,VB,FB);
  read_triangle_mesh(program.get<std::string>("--input3"),VC,FC);
  read_triangle_mesh(program.get<std::string>("--input4"),VD,FD);
  read_triangle_mesh(program.get<std::string>("--input5"),VE,FE);
  igl::opengl::glfw::Viewer viewer;

  int num_views = 5+4;
  int view_id = num_views-1;
  const auto & update = [&]()
  {
    viewer.data().clear();
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::VectorXd I;
    get_mesh(VA,FA,VB,FB,VC,FC,VD,FD,VE,FE,view_id,V,F,I);
    viewer.data().set_mesh(V,F);
    MatrixXd C;
    jet(I,1,5,C);
    viewer.data().set_colors(C);
  };
  update();

  viewer.callback_key_down = 
    [&](igl::opengl::glfw::Viewer &viewer, unsigned char key, int mods)->bool
    {
      switch(key)
      {
        case ']':
          view_id = (view_id+1)%num_views;
          break;
        case '[':
          view_id = (view_id+num_views-1)%num_views;
          break;
        default:
          return false;
      }
      update();
      return true;
    };
  viewer.launch();
}
