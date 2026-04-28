# 806_HeatGeodesics

### (1) What does the code do?
This code implements the **Heat Method** for computing geodesic distances on a triangle mesh. It solves a heat diffusion problem, computes the gradients of the resulting temperature field, and then integrates a vector field to recover the distance from a source point (selected by the user via mouse click).

### (2) How many parameters are present in the code and how they impact the final results?
- **Diffusion Time `t`**: This parameter controls the "scale" of the heat diffusion.
- **`use_intrinsic_delaunay`**: A toggle that determines whether to use intrinsic Delaunay edges for the discrete differential operators. This significantly improves numerical stability on meshes with poor-quality (thin/long) triangles.

### (3) What the optimal value of the input parameters?
- **`t`**: The optimal value is typically the **square of the average edge length** (`h^2`). If `t` is too small, the solution becomes numerically unstable; if too large, the distance approximation becomes "blurry."
- **Intrinsic Delaunay**: Should be enabled (`true`) for any mesh that isn't composed of nearly equilateral triangles to ensure robustness.

### (4) What are industrial applications of this concept?
- **Robotics**: Path planning on complex surfaces (manifolds).
- **Texture Mapping**: Computing low-distortion UV coordinates.
- **Biometrics**: Analyzing the shape of faces or other biological surfaces.
- **Shape Matching**: Finding correspondences between different 3D models.

### (5) How this could be useful for downstream applications.
Geodesic distances are a fundamental primitive in geometry processing. They are used for remeshing, computing isolines, Voronoi partitioning on surfaces, and any application that requires understanding the "true" distance between points as constrained to a surface, rather than simple Euclidean distance.
