# 303_LaplaceEquation

### (1) What does the code do?
This example solves the Laplace equation ($\Delta u = 0$) on a triangle mesh with Dirichlet boundary conditions. It identifies the boundary of the mesh, fixes the values at these boundary vertices (using their Z-coordinates), and then computes the values for all interior vertices that minimize the Dirichlet energy. This results in a "harmonic" field that transitions smoothly from the boundary values.

### (2) How many parameters are present in the code and how they impact the final results?
There is one primary parameter:
1.  **--input (-i)**: Path to the mesh file. The mesh must have at least one boundary (i.e., it cannot be a closed manifold like a sphere) for the Dirichlet boundary conditions to be meaningful.
The boundary values are automatically determined by the Z-coordinates of the boundary vertices, so the geometric orientation of the input mesh directly impacts the resulting scalar field.

### (3) What the optimal value of the input parameters?
A mesh with a clearly defined, single boundary (like a disc or an open surface) is ideal for visualizing the harmonic interpolation. The mesh should be well-scaled to avoid numerical issues during the linear system solve.

### (4) What are industrial applications of this concept?
-   **Physics Simulation**: Modeling steady-state heat distribution, inviscid fluid flow, and electrostatics.
-   **Surface Fairing**: Smoothing out noisy regions of a mesh by replacing them with harmonic surfaces.
-   **Hole Filling**: Closing gaps in 3D scans by interpolating surface data from the edges of the hole.

### (5) How this could be useful for downstream applications.
-   **Parameterization**: Harmonic maps are a key component of UV unwrapping algorithms.
-   **Shape Interpolation**: Smoothly blending between two shapes or textures based on boundary constraints.
-   **Deformation Transfer**: Propagating changes from one part of a model to another while maintaining smooth surface properties.
