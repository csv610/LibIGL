# 704_SignedDistance

## (1) What does the code do?
This code calculates the signed distance from points on a cross-sectional plane to a 3D triangle mesh. It visualizes the distance field using a colormap, where different colors represent the distance from the surface, and the sign indicates whether a point is inside or outside the mesh. The implementation supports two methods for determining the sign: pseudonormals (best for watertight meshes) and fast winding numbers (more robust for general meshes).

## (2) How many parameters are present in the code and how they impact the final results?
- **Input Mesh (`-i`, `--input`)**: The 3D model (typically a `.mesh` file containing a tetrahedral convex hull and a surface) to calculate distances against.
- **Slice Position (`slice_z`)**: Controlled via `,` and `.` keys, it moves the visualization plane along the Z-axis, allowing inspection of the distance field at different depths.
- **Signing Method**: Toggled with `1` (Fast Winding Number) and `2` (Pseudonormals). Fast Winding Number is more robust to self-intersections and open boundaries, while Pseudonormals are standard for clean, manifold meshes.
- **Surface Overlay**: Toggled with `[space]`, it shows the original surface mesh for reference.

## (3) What the optimal value of the input parameters?
- **Input Mesh**: For pseudonormal signing, the mesh should ideally be a closed manifold. For fast winding numbers, the mesh can be more complex.
- **Method Selection**: Use Pseudonormals for high precision on clean geometry. Use Fast Winding Number for "dirty" geometry with holes or self-intersections.

## (4) What are industrial applications of this concept?
- **Collision Detection**: Efficiently determining if an object has penetrated a boundary in physics engines.
- **3D Printing**: Generating offset surfaces to create shells or hollow out solid models to save material.
- **CAD**: Performing robust boolean operations (union, intersection, subtraction) using level set representations.

## (5) How this could be useful for downstream applications.
- **Implicit Modeling**: Converting explicit boundary representations (meshes) into implicit functions for easier blending and morphing.
- **Path Planning**: Creating potential fields for robotics where the signed distance helps maintain a safety margin from obstacles.
- **Reconstruction**: Serving as a basis for surface reconstruction algorithms like Marching Cubes.
