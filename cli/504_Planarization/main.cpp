#include <igl/placeholders.h>
#include <igl/jet.h>
#include <igl/planarize_quad_mesh.h>
#include <igl/quad_planarity.h>
#include <igl/read_triangle_mesh.h>
#include <igl/write_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>
#include <argparse/argparse.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct AppState {
    Eigen::MatrixXd V_orig;
    Eigen::MatrixXi F_quad;
    Eigen::MatrixXi F_tri;
    
    Eigen::MatrixXd V_planar;
    
    bool showing_planar = true;

    void update_viewer(igl::opengl::glfw::Viewer& viewer) {
        const Eigen::MatrixXd& V = showing_planar ? V_planar : V_orig;
        
        viewer.data().clear();
        viewer.data().set_mesh(V, F_tri);
        
        // Calculate planarity
        Eigen::VectorXd planarity;
        igl::quad_planarity(V, F_quad, planarity);
        
        Eigen::MatrixXd C_quad;
        igl::jet(planarity, 0.0, 0.01, C_quad);
        
        Eigen::MatrixXd C_tri(F_tri.rows(), 3);
        C_tri << C_quad, C_quad;
        viewer.data().set_colors(C_tri);
        
        // Add edges for quads
        for (int i = 0; i < 4; ++i) {
            viewer.data().add_edges(
                V(F_quad.col(i).eval(), igl::placeholders::all),
                V(F_quad.col((i + 1) % 4).eval(), igl::placeholders::all),
                Eigen::RowVector3d(0, 0, 0)
            );
        }
        
        std::cout << "Showing " << (showing_planar ? "PLANARIZED" : "ORIGINAL") << " mesh. "
                  << "Mean planarity: " << planarity.mean() << std::endl;
    }
};

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier, AppState& state) {
    
    
    if (key == '1') {
        state.showing_planar = false;
        state.update_viewer(viewer);
        return true;
    } else if (key == '2') {
        state.showing_planar = true;
        state.update_viewer(viewer);
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("504_Planarization");
    program.add_argument("-i", "--input").required().help("Path to input quad mesh (.off, .obj, etc.)");
    program.add_argument("-o", "--output").help("Path to save the planarized quad mesh");
    program.add_argument("-v", "--view").default_value(false).implicit_value(true).help("Launch the interactive viewer");
    program.add_argument("--iters").default_value(100).scan<'i', int>().help("Number of planarization iterations");
    program.add_argument("--step").default_value(0.005).scan<'g', double>().help("Step size for planarization");
    program.add_argument("-s", "--score").help("Path to save planarity scores (CSV)");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    AppState state;
    if (!igl::read_triangle_mesh(program.get<std::string>("--input"), state.V_orig, state.F_quad)) {
        std::cerr << "Error: Could not load mesh from " << program.get<std::string>("--input") << std::endl;
        return 1;
    }

    if (state.F_quad.cols() != 4) {
        std::cerr << "Error: Input mesh must be a quad mesh (faces must have 4 vertices)." << std::endl;
        return 1;
    }

    // Prepare triangulation for visualization
    state.F_tri.resize(2 * state.F_quad.rows(), 3);
    state.F_tri << state.F_quad.col(0), state.F_quad.col(1), state.F_quad.col(2),
                   state.F_quad.col(2), state.F_quad.col(3), state.F_quad.col(0);

    // Initial planarity
    Eigen::VectorXd planarity_before;
    igl::quad_planarity(state.V_orig, state.F_quad, planarity_before);
    std::cout << "Initial Planarity - Mean: " << planarity_before.mean() 
              << ", Max: " << planarity_before.maxCoeff() << std::endl;

    // Run planarization
    int iters = program.get<int>("--iters");
    double step = program.get<double>("--step");
    std::cout << "Running " << iters << " iterations of planarization with step " << step << "..." << std::endl;
    igl::planarize_quad_mesh(state.V_orig, state.F_quad, iters, step, state.V_planar);

    // Final planarity
    Eigen::VectorXd planarity_after;
    igl::quad_planarity(state.V_planar, state.F_quad, planarity_after);
    std::cout << "Final Planarity   - Mean: " << planarity_after.mean() 
              << ", Max: " << planarity_after.maxCoeff() << std::endl;

    // Save results
    if (program.present("--output")) {
        std::string out_path = program.get<std::string>("--output");
        if (igl::write_triangle_mesh(out_path, state.V_planar, state.F_quad)) {
            std::cout << "Planarized mesh saved to: " << out_path << std::endl;
        }
    }

    if (program.present("--score")) {
        std::string score_path = program.get<std::string>("--score");
        std::ofstream f(score_path);
        if (f.is_open()) {
            f << "stage,mean,max\n";
            f << "before," << planarity_before.mean() << "," << planarity_before.maxCoeff() << "\n";
            f << "after," << planarity_after.mean() << "," << planarity_after.maxCoeff() << "\n";
            std::cout << "Scores saved to: " << score_path << std::endl;
        }
    }

    // Viewer
    if (program.get<bool>("--view")) {
        igl::opengl::glfw::Viewer viewer;
        
        viewer.callback_key_down = [&](igl::opengl::glfw::Viewer& v, unsigned char k, int m) { return key_down(v, k, m, state); };
        
        std::cout << "\nViewer Controls:\n"
                  << "  [1] Show original mesh\n"
                  << "  [2] Show planarized mesh\n"
                  << "  [L] Toggle lines\n"
                  << std::endl;
                  
        state.update_viewer(viewer);
        viewer.data().invert_normals = true;
        viewer.data().show_lines = false;
        viewer.launch();
    }

    return 0;
}
