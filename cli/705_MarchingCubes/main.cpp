#include <igl/marching_cubes.h>
#include <igl/signed_distance.h>
#include <igl/read_triangle_mesh.h>
#include <igl/voxel_grid.h>
#include <igl/opengl/glfw/Viewer.h>
#include <argparse/argparse.hpp>
#include <Eigen/Core>
#include <iostream>
#include <string>


int main(int argc, char * argv[])
{
  using namespace Eigen;
  using namespace std;
  using namespace igl;

  argparse::ArgumentParser program("705_MarchingCubes");
  program.add_argument("-i", "--input").required().help("Path to mesh file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  MatrixXi F;
  MatrixXd V;
  // Read in inputs as double precision floating point meshes
  read_triangle_mesh(program.get<std::string>("--input"),V,F);
  cout<<"Creating grid..."<<endl;
  // number of vertices on the largest side
  const int s = 100;
  // create grid
  MatrixXd GV;
  Eigen::RowVector3i res;
  igl::voxel_grid(V,0,s,1,GV,res);
 
  // compute values
  cout<<"Computing distances..."<<endl;
  VectorXd S,B;
  {
    VectorXi I;
    MatrixXd C,N;
    signed_distance(GV,V,F,SIGNED_DISTANCE_TYPE_PSEUDONORMAL,S,I,C,N);
    // Convert distances to binary inside-outside data --> aliasing artifacts
    B = S;
    for_each(B.data(),B.data()+B.size(),[](double& b){b=(b>0?1:(b<0?-1:0));});
  }
  cout<<"Marching cubes..."<<endl;
  MatrixXd SV,BV;
  MatrixXi SF,BF;
  igl::marching_cubes(S,GV,res(0),res(1),res(2),0,SV,SF);
  igl::marching_cubes(B,GV,res(0),res(1),res(2),0,BV,BF);

  cout<<R"(Usage:
'1'  Show original mesh.
'2'  Show marching cubes contour of signed distance.
'3'  Show marching cubes contour of indicator function.
)";
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(SV,SF);
  viewer.callback_key_down =
    [&](igl::opengl::glfw::Viewer & viewer, unsigned char key, int mod)->bool
    {
      switch(key)
      {
        default:
          return false;
        case '1':
          viewer.data().clear();
          viewer.data().set_mesh(V,F);
          break;
        case '2':
          viewer.data().clear();
          viewer.data().set_mesh(SV,SF);
          break;
        case '3':
          viewer.data().clear();
          viewer.data().set_mesh(BV,BF);
          break;
      }
      viewer.data().set_face_based(true);
      return true;
    };
  viewer.launch();
}
