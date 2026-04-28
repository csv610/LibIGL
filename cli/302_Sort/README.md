# 302_Sort

### (1) What does the code do?
This example demonstrates how to sort mesh elements spatially. Specifically, it computes the barycenters (centroids) of all faces in a mesh and sorts them lexicographically. The sorted order is then visualized using a colormap, and the sorted indices can be exported to a JSON file.

### (2) How many parameters are present in the code and how they impact the final results?
There are three main parameters:
1.  **--input (-i)**: (Required) Path to the mesh file. This is the source data for the sorting operation.
2.  **--output (-o)**: Path to a JSON file where the sorted face indices will be saved. If omitted, no file is written.
3.  **--view**: A boolean flag to launch the interactive viewer. This allows for visual inspection of the sorted order (visualized as a color gradient across the mesh).

### (3) What the optimal value of the input parameters?
Any manifold or non-manifold triangle mesh is suitable. The `--view` flag is recommended for immediate verification of the sorting result.

### (4) What are industrial applications of this concept?
-   **Computer Graphics**: Sorting faces for correct transparency rendering (back-to-front) or optimizing depth-buffer performance.
-   **Collision Detection**: Spatially sorting objects or primitives to accelerate intersection tests in physics engines.
-   **Data Compression**: Reordering mesh elements to improve vertex cache locality and compression ratios.

### (5) How this could be useful for downstream applications.
-   **Spatial Indexing**: Providing a foundation for building BVHs (Bounding Volume Hierarchies) or Octrees.
-   **Occlusion Culling**: Identifying which parts of a model are likely to be hidden based on their spatial order from the camera.
-   **Sequential Processing**: Efficiently streaming or processing mesh data in a predictable spatial order.
