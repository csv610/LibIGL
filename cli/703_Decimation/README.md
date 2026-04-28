# 703_Decimation

## (1) What does the code do?
This code implements an incremental mesh decimation algorithm using edge collapse operations. It reduces the complexity of a triangle mesh by repeatedly collapsing edges that contribute least to the geometric error, effectively simplifying the mesh while maintaining its overall shape and topology. It uses `igl::collapse_least_cost_edge` and a priority queue to manage the cost of potential collapses.

## (2) How many parameters are present in the code and how they impact the final results?
The code has the following primary parameters:
- **Input Mesh (`-i`, `--input`)**: The path to the triangle mesh file to be decimated.
- **Internal Iteration Rate**: During animation, the code collapses 1% of the remaining edges in each frame (`max_iter = std::ceil(0.01 * Q.size())`). This impacts the speed of the simplification process.
- **Edge Cost Function**: The code uses `shortest_edge_and_midpoint` to calculate the cost of collapsing an edge. This determines which edges are prioritized for removal, directly affecting the quality of the simplified mesh.

## (3) What the optimal value of the input parameters?
- **Input Mesh**: Should be a manifold triangle mesh for best results.
- **Decimation Level**: There is no single "optimal" value, as it depends on the application's needs for fidelity vs. performance. Typically, reducing a mesh to 10-20% of its original face count provides a good balance for many visualization tasks.

## (4) What are industrial applications of this concept?
- **Video Games**: Generating Level of Detail (LOD) models to maintain high frame rates by using simpler meshes for distant objects.
- **CAD/CAM**: Simplifying complex engineering models for faster simulation, analysis, or web-based 3D viewing.
- **Digital Heritage**: Managing massive 3D scans by creating simplified versions for interactive display.

## (5) How this could be useful for downstream applications.
- **Real-time Rendering**: Decreases the number of primitives the GPU needs to process, improving rendering performance.
- **Collision Detection**: Coarser meshes allow for faster intersection tests in physics engines.
- **Geometry Processing**: Simplification can serve as a pre-processing step to speed up computationally expensive algorithms like global parameterization or complex simulations.
