# 1003 Winding Number 2D

### (1) What does the code do?
This program computes the winding number in 2D to determine the interior/exterior status of points relative to a 2D curve. It compares a naive $O(N)$ approach with a fast, accelerated version using an Eytzinger AABB tree.

### (2) How many parameters are present in the code and how they impact the final results?
The code does not expose many user parameters besides selecting the quantity to compute: Signed Distance, Winding Number, or Unsigned Distance.

### (3) What the optimal value of the input parameters?
N/A (Correctness is independent of parameter tuning).

### (4) What are industrial applications of this concept?
Vector graphics rendering (defining SVG fill rules), point-in-polygon tests in Geographic Information Systems (GIS), and font rendering in digital displays.

### (5) How this could be useful for downstream applications.
The winding number is a robust tool for point-in-curve testing and is foundational for 2D Boolean operations and robust mesh generation.
