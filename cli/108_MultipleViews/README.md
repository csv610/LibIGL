# 108_MultipleViews

## (1) What does the code do?
This tutorial demonstrates how to create multiple viewports (split screens) within the same window. Each viewport can have its own camera settings and can be configured to show different meshes or different perspectives of the same scene.

## (2) How many parameters are present in the code and how they impact the final results?
There are 2 parameters:
- `-i1/--input1`: Path to the first mesh file, displayed in the first viewport.
- `-i2/--input2`: Path to the second mesh file, displayed in the second viewport.

## (3) What the optimal value of the input parameters?
The optimal values are two different mesh files (e.g., `cube.obj` and `sphere.obj`) to clearly distinguish between the two viewports.

## (4) What are industrial applications of this concept?
Industrial applications include side-by-side comparison of different design versions in CAD, simultaneous viewing of top/front/side projections in modeling software, and comparative medical imaging analysis.

## (5) How this could be useful for downstream applications.
Multiple views are essential for A/B testing of geometric algorithms, where one view shows the original mesh and the other shows the processed result, allowing for immediate visual validation of the algorithm's performance.
