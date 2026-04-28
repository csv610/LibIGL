# 906 Trim with Solid

### (1) What does the code do?
This program trims a triangle mesh against a solid (watertight) mesh. It classifies the input mesh's patches as being inside or outside the solid volume and performs robust intersection handling to create a clean, trimmed surface.

### (2) How many parameters are present in the code and how they impact the final results?
The code exposes different intersection resolution strategies:
- `CHECK_EACH_PATCH`: A faster method that focuses on patch classification.
- `RESOLVE_BOTH_AND_RESTORE_THEN_CHECK_EACH_PATCH`: A more robust (but slower) method that handles complex self-intersections and ensures topological consistency.

### (3) What the optimal value of the input parameters?
For high-quality geometry processing, the robust `RESOLVE_BOTH...` method is preferred, as it handles edge cases (like tangencies) that might cause the faster method to fail.

### (4) What are industrial applications of this concept?
CAD/CAM boolean operations, jewelry design (engraving), and surgical simulations where a tool must "cut" or "trim" tissue.

### (5) How this could be useful for downstream applications.
This is essential for Constructive Solid Geometry (CSG), mesh refinement, and preparing complex assemblies for physical simulation (e.g., CFD).
