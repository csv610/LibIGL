#include <igl/read_triangle_mesh.h>
//#undef IGL_STATIC_LIBRARY
#include <igl/copyleft/cgal/mesh_boolean.h>
#include <igl/opengl/glfw/Viewer.h>

#include <argparse/argparse.hpp>
#include <Eigen/Core>
#include <iostream>
#include <string>


Eigen::MatrixXd VA,VB,VC;
Eigen::VectorXi J,I;
Eigen::MatrixXi FA,FB,FC;
igl::MeshBooleanType boolean_type(
  igl::MESH_BOOLEAN_TYPE_UNION);

const char * MESH_BOOLEAN_TYPE_NAMES[] =
{
  "Union",
  "Intersect",
  "Minus",
  "XOR",
  "Resolve",
};

void update(igl::opengl::glfw::Viewer &viewer)
{
  igl::copyleft::cgal::mesh_boolean(VA,FA,VB,FB,boolean_type,VC,FC,J);
  Eigen::MatrixXd C(FC.rows(),3);
  for(size_t f = 0;f<C.rows();f++)
  {
    if(J(f)<FA.rows())
    {
      C.row(f) = Eigen::RowVector3d(1,0,0);
    }else
    {
      C.row(f) = Eigen::RowVector3d(0,1,0);
    }
  }
  viewer.data().clear();
  viewer.data().set_mesh(VC,FC);
  viewer.data().set_colors(C);
  std::cout<<"A "<<MESH_BOOLEAN_TYPE_NAMES[boolean_type]<<" B."<<std::endl;
}

bool key_down(igl::opengl::glfw::Viewer &viewer, unsigned char key, int mods)
{
  switch(key)
  {
    default:
      return false;
    case '.':
      boolean_type =
        static_cast<igl::MeshBooleanType>(
          (boolean_type+1)% igl::NUM_MESH_BOOLEAN_TYPES);
      break;
    case ',':
      boolean_type =
        static_cast<igl::MeshBooleanType>(
          (boolean_type+igl::NUM_MESH_BOOLEAN_TYPES-1)%
          igl::NUM_MESH_BOOLEAN_TYPES);
      break;
    case '[':
      viewer.core().camera_dnear -= 0.1;
      return true;
    case ']':
      viewer.core().camera_dnear += 0.1;
      return true;
  }
  update(viewer);
  return true;
}

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("609_Boolean");
  program.add_argument("-i1", "--input1").required().help("Path to first mesh file");
  program.add_argument("-i2", "--input2").required().help("Path to second mesh file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  using namespace Eigen;
  using namespace std;
  igl::read_triangle_mesh(program.get<std::string>("--input1"),VA,FA);
  igl::read_triangle_mesh(program.get<std::string>("--input2"),VB,FB);
  // Plot the mesh with pseudocolors
  igl::opengl::glfw::Viewer viewer;

  // Initialize
  update(viewer);

  viewer.data().show_lines = true;
  viewer.callback_key_down = &key_down;
  viewer.core().camera_dnear = 3.9;
  cout<<
    "Press '.' to switch to next boolean operation type."<<endl<<
    "Press ',' to switch to previous boolean operation type."<<endl<<
    "Press ']' to push near cutting plane away from camera."<<endl<<
    "Press '[' to pull near cutting plane closer to camera."<<endl<<
    "Hint: investigate _inside_ the model to see orientation changes."<<endl;
  viewer.launch();
}
