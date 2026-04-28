# 1002 Eytzinger AABB

### (1) What does the code do?
This code implements an AABB tree using the Eytzinger layout (an array-based binary tree) for improved cache locality. It demonstrates distance queries to various primitives like edges, triangles, and variable-radius spheres.

### (2) How many parameters are present in the code and how they impact the final results?
- `max_depth` (default 7): Determines the grid resolution for the initial distance field computation. A higher depth results in a more detailed grid.

### (3) What the optimal value of the input parameters?
A `max_depth` of 7 is a good tradeoff for visualizing the tree's performance without excessive memory overhead.

### (4) What are industrial applications of this concept?
High-performance collision detection in physics engines, GPU-accelerated spatial queries, and ray tracing in graphics.

### (5) How this could be useful for downstream applications.
The Eytzinger layout can significantly improve the speed of spatial queries in large-scale geometry processing tasks where memory throughput is a bottleneck.
