# 206_GeodesicDistance

### (1) What does the code do?
This example computes the exact geodesic distance from a source vertex to all other vertices on a triangle mesh. It uses the Mitchell-Mount-Papadimitriou (MMP) algorithm (via `igl::exact_geodesic`) to find the shortest path along the surface. The user can interactively select a source vertex by clicking on the mesh, and the code updates the distance field, visualizing it with a colormap and isolines.

### (2) How many parameters are present in the code and how they impact the final results?
There are two main parameters:
1.  **--input (-i)**: Path to the mesh file (e.g., .obj, .off). This determines the geometry and topology on which distances are calculated.
2.  **--view**: A boolean flag that launches the interactive viewer. Without this, the code performs the computation for a default vertex but does not provide visual feedback.

### (3) What the optimal value of the input parameters?
The optimal `--input` is a clean, manifold triangle mesh. The `--view` flag should be enabled to allow for interactive exploration and selection of different source vertices.

### (4) What are industrial applications of this concept?
-   **Manufacturing**: Planning optimal tool paths for CNC machining on complex curved surfaces.
-   **Computer Graphics**: Texture mapping (geodesic-based parameterization) and character animation (distance-based skinning).
-   **Medical Imaging**: Measuring distances on anatomical models, such as the surface of the brain or bones, for surgical planning.
-   **Geology**: Analyzing terrain and calculating travel distances over geographical surfaces.

### (5) How this could be useful for downstream applications.
Geodesic distance computation is a fundamental building block for:
-   **Remeshing**: Placing vertices uniformly based on surface distance.
-   **Shape Analysis**: Calculating shape descriptors and finding correspondences between different meshes.
-   **Pathfinding**: Autonomous navigation for robots moving on non-planar surfaces.
-   **Clustering**: Segmenting meshes into regions based on proximity to seed points.
