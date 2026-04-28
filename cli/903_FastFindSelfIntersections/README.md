# 903 Fast Find Self-Intersections

### (1) What does the code do?
This program identifies all pairs of faces in a triangle mesh that intersect each other. It uses a spatial acceleration structure (AABB tree) combined with robust geometric predicates to efficiently detect these self-intersections, which are then highlighted in the viewer.

### (2) How many parameters are present in the code and how they impact the final results?
The code does not expose user-tunable parameters beyond the input mesh. The algorithm is designed to be fully automatic and exhaustive in its detection.

### (3) What the optimal value of the input parameters?
N/A (The algorithm's correctness is independent of parameter tuning).

### (4) What are industrial applications of this concept?
Mesh validation is critical for 3D printing (where self-intersections cause slicing errors), CAD/CAM quality control, and collision detection in mechanical assembly simulations.

### (5) How this could be useful for downstream applications.
Detecting self-intersections is the first step in mesh repair, Boolean operations, and ensuring the topological integrity of models used for finite element analysis (FEA).
