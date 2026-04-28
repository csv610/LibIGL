# LibIGL User Guide: A Journey into Geometry Processing
*An Undergraduate's Companion to Discrete Differential Geometry*

---

## 1. Introduction: Why LibIGL?
Welcome to the world of Geometry Processing! Unlike many traditional graphics libraries that focus on rendering, **libigl** is designed for *geometry processing*. It treats a 3D mesh not just as a visual object, but as a discrete surface that obeys mathematical laws.

LibIGL is unique because:
*   **Header-only:** Most features require no complex installation.
*   **Eigen-centric:** It uses the Eigen C++ library for all linear algebra, making it feel like MATLAB in C++.
*   **Flat Structure:** There are no complex object hierarchies. You pass matrices in, and you get matrices out.

---

## 2. The Core Data Structures
In LibIGL, a triangle mesh is represented by two primary matrices:

### The Vertex Matrix `V`
A `#V by 3` matrix where each row represents the $(x, y, z)$ coordinates of a vertex.
```cpp
Eigen::MatrixXd V; // Double precision for coordinates
```

### The Face Matrix `F`
A `#F by 3` matrix of integers. Each row represents a triangle, containing the indices of the three vertices in `V` that form it.
```cpp
Eigen::MatrixXi F; // Integers for indices
```

---

## 3. Basic Mesh Operations
### Reading and Writing
Before you can process geometry, you must load it. LibIGL supports `.obj`, `.off`, `.stl`, and `.ply`.
```cpp
#include <igl/read_triangle_mesh.h>
#include <igl/write_triangle_mesh.h>

igl::read_triangle_mesh("bunny.obj", V, F);
igl::write_triangle_mesh("output.obj", V, F);
```

### Computing Normals
Normals are essential for lighting and understanding surface orientation.
```cpp
#include <igl/per_vertex_normals.h>
Eigen::MatrixXd N;
igl::per_vertex_normals(V, F, N);
```

---

## 4. Differential Geometry on Meshes
This is where the math happens. LibIGL makes complex operations like the **Laplace-Beltrami Operator** accessible.

### The Laplacian
The Laplacian $\Delta$ tells us about the "smoothness" or "curvature" of a point. In LibIGL, we compute the discrete Laplacian using the "cotangent weights" method.
```cpp
#include <igl/cotmatrix.h>
Eigen::SparseMatrix<double> L;
igl::cotmatrix(V, F, L);
```

### Gaussian Curvature
Understanding how "pointy" or "flat" a surface is at each vertex.
```cpp
#include <igl/gaussian_curvature.h>
Eigen::VectorXd K;
igl::gaussian_curvature(V, F, K);
```

---

## 5. Tetrahedral Mesh Generation (TetMeshing)
While surface meshes (triangles) are great for rendering, many simulations (like Finite Element Method or FEM) require a **volume mesh**. A volume mesh is typically composed of **tetrahedra** (four-sided solids).

### Using TetGen
LibIGL provides a wrapper for the famous **TetGen** library. Note that this is in the `copyleft` namespace because of TetGen's licensing.

```cpp
#include <igl/copyleft/tetgen/tetrahedralize.h>

Eigen::MatrixXd TV; // Tet mesh vertices
Eigen::MatrixXi TT; // Tet mesh indices (#T x 4)
Eigen::MatrixXi TF; // Tet mesh boundary faces

// "pq1.414a0.01" are tetgen switches for:
// p: constrained Delaunay
// q: quality (radius-edge ratio)
// a: maximum volume constraint
igl::copyleft::tetgen::tetrahedralize(V, F, "pq1.414a0.01", TV, TT, TF);
```

### Representation
*   **TV:** Similar to `V`, a `#TV by 3` matrix of vertices.
*   **TT:** A `#T by 4` matrix where each row indices four vertices in `TV` that form a tetrahedron.

---

## 6. Visualizing Your Work
LibIGL includes a powerful, lightweight viewer based on GLFW and ImGui.

```cpp
#include <igl/opengl/glfw/Viewer.h>

igl::opengl::glfw::Viewer viewer;
viewer.data().set_mesh(V, F);
viewer.launch();
```
*   **Mouse Drag:** Rotate the mesh.
*   **Scroll:** Zoom in/out.
*   **Shift + Mouse:** Translate (Pan).

---

## 7. Building CLI Applications
For research and batch processing, we often build Command Line Interface (CLI) apps. These apps typically follow this pattern:
1.  **Parse Arguments:** Use `argparse` to get input/output paths.
2.  **Process Geometry:** Apply rotations, translations, or curvature analysis.
3.  **Export Result:** Save the modified mesh or a rendered image.

*Example: Random Rotation*
```cpp
Eigen::Quaterniond q = igl::random_quaternion<double>();
V = (V * q.toRotationMatrix().transpose()).eval();
```

---

## 8. Mathematical Exercise for Students
Try to implement a "Mesh Smoothing" filter. 
1. Compute the Laplacian $L$.
2. Update the vertices: $V_{new} = V + \lambda L V$.
3. Observe how the mesh loses its sharp features and becomes "blurry."

---

## 9. Where to Go Next?
Check the `tutorial/` folder for 100+ interactive examples covering:
*   **Parameterization:** Flattening a 3D mesh to a 2D UV map.
*   **Deformation:** Moving a handle and watching the rest of the mesh follow "As-Rigid-As-Possible" (ARAP).
*   **Boolean Operations:** Merging or subtracting two meshes.

Happy Coding!
