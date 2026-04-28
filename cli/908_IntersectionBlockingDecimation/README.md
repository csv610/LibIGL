# 908 Intersection-Blocking Decimation

### (1) What does the code do?
This program performs mesh decimation (simplification) while ensuring that no new self-intersections are introduced. It compares standard Q-Slim decimation with a robust version that uses an AABB tree to block any edge collapse that would cause a self-intersection.

### (2) How many parameters are present in the code and how they impact the final results?
- `target_m`: The target number of faces for the simplified mesh. A smaller target results in a coarser mesh.

### (3) What the optimal value of the input parameters?
A `target_m` of around 10% of the original face count is a common benchmark for evaluating the effectiveness of the intersection-blocking constraint.

### (4) What are industrial applications of this concept?
Low-poly model generation for real-time rendering, mesh optimization for 3D printing (where self-intersections are fatal), and creating clean simulation proxies.

### (5) How this could be useful for downstream applications.
It ensures that simplified models remain topologically valid and "printable," which is crucial for manufacturing and robust simulation pipelines.
