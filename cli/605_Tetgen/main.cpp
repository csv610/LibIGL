#include <igl/opengl/glfw/Viewer.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>
#include <igl/read_triangle_mesh.h>
#include <igl/writeMESH.h>
#include <igl/barycenter.h>
#include <argparse/argparse.hpp>
#include <iostream>
#include <string>


// Input polygon
Eigen::MatrixXd V;
Eigen::MatrixXi F;
Eigen::MatrixXd B;

// Tetrahedralized interior
Eigen::MatrixXd TV;
Eigen::MatrixXi TT;
Eigen::MatrixXi TF;

// This function is called every time a keyboard button is pressed
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
  using namespace std;
  using namespace Eigen;

  if (key >= '1' && key <= '9')
  {
    double t = double((key - '1')+1) / 9.0;

    VectorXd v = B.col(2).array() - B.col(2).minCoeff();
    v /= v.col(0).maxCoeff();

    vector<int> s;

    for (unsigned i=0; i<v.size();++i)
      if (v(i) < t)
        s.push_back(i);

    MatrixXd V_temp(s.size()*4,3);
    MatrixXi F_temp(s.size()*4,3);

    for (unsigned i=0; i<s.size();++i)
    {
      V_temp.row(i*4+0) = TV.row(TT(s[i],0));
      V_temp.row(i*4+1) = TV.row(TT(s[i],1));
      V_temp.row(i*4+2) = TV.row(TT(s[i],2));
      V_temp.row(i*4+3) = TV.row(TT(s[i],3));
      F_temp.row(i*4+0) << (i*4)+0, (i*4)+1, (i*4)+3;
      F_temp.row(i*4+1) << (i*4)+0, (i*4)+2, (i*4)+1;
      F_temp.row(i*4+2) << (i*4)+3, (i*4)+2, (i*4)+0;
      F_temp.row(i*4+3) << (i*4)+1, (i*4)+2, (i*4)+3;
    }

    viewer.data().clear();
    viewer.data().set_mesh(V_temp,F_temp);
    viewer.data().set_face_based(true);
  }


  return false;
}

int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("605_Tetgen");
  program.add_argument("-i", "--input").required().help("Path to mesh file");
  program.add_argument("-o", "--output").default_value(std::string("")).help("Path to output .mesh file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  using namespace Eigen;
  using namespace std;

  // Load a surface mesh
  igl::read_triangle_mesh(program.get<std::string>("--input"),V,F);

  // Tetrahedralize the interior
  igl::copyleft::tetgen::tetrahedralize(V,F,"pq1.414Y", TV,TT,TF);

  // Output to .mesh
  std::string output_path = program.get<std::string>("--output");
  if (output_path.empty()) {
    std::string input_path = program.get<std::string>("--input");
    size_t lastdot = input_path.find_last_of(".");
    if (lastdot == std::string::npos) {
      output_path = input_path + ".mesh";
    } else {
      output_path = input_path.substr(0, lastdot) + ".mesh";
    }
  }

  if (igl::writeMESH(output_path, TV, TT, TF)) {
    std::cout << "Saved volumetric mesh to: " << output_path << std::endl;
  } else {
    std::cerr << "Error: Could not save mesh to " << output_path << std::endl;
  }

  // Compute barycenters
  igl::barycenter(TV,TT,B);

  // Plot the generated mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.callback_key_down = &key_down;
  key_down(viewer,'5',0);
  viewer.launch();
}
