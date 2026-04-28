# 401 Biharmonic Deformation

## (1) What does the code do?
This example implements smooth mesh deformation using bi-harmonic coordinates. It takes a mesh and a selection file (which defines "handles") and allows the user to deform the mesh by moving these handles. The deformation is computed using `igl::harmonic`, which solves the bi-harmonic equation to produce a smooth transition between handle positions.

## (2) How many parameters are present in the code and how they impact the final results?
- **Input mesh (-i)**: The base geometry.
- **Selection file (--selection)**: Defines which vertices are handles and their indices.
- **Deformation mode ('d')**: Toggles between "surface" bi-harmonic (interpolating positions) and "displacement" bi-harmonic (interpolating displacement vectors).

The "displacement" mode typically produces more intuitive results for large deformations as it preserves local details better.

## (3) What the optimal value of the input parameters?
Handles should be placed strategically to capture the intended degrees of freedom of the model. The mesh density should be sufficient to represent the smooth deformation field.

## (4) What are industrial applications of this concept?
- **Character Animation**: Deforming a 3D character mesh by moving "control points" or bones.
- **Digital Sculpting**: Allowing artists to pull and push parts of a high-resolution model smoothly.
- **CAD**: Modifying existing parts while maintaining smooth transitions.

## (5) How this could be useful for downstream applications.
Biharmonic deformation is a standard technique for "handle-based" editing, providing a good balance between smoothness and computational efficiency compared to more complex non-linear methods like ARAP (As-Rigid-As-Possible).
