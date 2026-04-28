# 1004 Spline Distance

### (1) What does the code do?
This program computes the signed distance and winding number for 2D cubic Bezier splines. It uses an accelerated AABB tree to find the closest points on the splines efficiently.

### (2) How many parameters are present in the code and how they impact the final results?
The parameters are fixed based on the input control points and indices, though the user can toggle between different visualization modes (Signed Distance, Winding Number, etc.).

### (3) What the optimal value of the input parameters?
N/A.

### (4) What are industrial applications of this concept?
Computer-Aided Design (CAD) for spline-based modeling, high-quality vector graphics (Illustrator/CorelDraw), and high-resolution CNC path planning.

### (5) How this could be useful for downstream applications.
This is essential for robust point inclusion tests for spline-defined regions, offset spline generation, and preparing vector art for physical fabrication.
