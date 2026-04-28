#include <igl/opengl/glfw/Viewer.h>
#include <igl/read_triangle_mesh.h>
#include <igl/stb/read_image.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: 111_MatCap_bin <mesh.obj> [matcap.png]" << std::endl;
    return 1;
  }
  igl::opengl::glfw::Viewer v;
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(argv[1],V,F);
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R,G,B,A;
  igl::stb::read_image(argc>2?argv[2]: TUTORIAL_SHARED_PATH "/jade.png",R,G,B,A);
  v.data().set_mesh(V,F);
  v.data().set_texture(R,G,B,A);
  v.data().use_matcap = true;
  v.data().show_lines = false;
  v.launch();
}
