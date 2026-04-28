# 103_Events

## (1) What does the code do?
The code demonstrates how to handle user interaction using keyboard callbacks in the libigl viewer. It loads two different meshes and allows the user to toggle between them by pressing the '1' and '2' keys.

## (2) How many parameters are present in the code and how they impact the final results?
There are 2 parameters:
- `-i1/--input1`: Path to the first mesh file (e.g., `bumpy.off`).
- `-i2/--input2`: Path to the second mesh file (e.g., `fertility.off`).
These parameters define the two models that the user can switch between during the interactive session.

## (3) What the optimal value of the input parameters?
The optimal values are paths to two distinct meshes with different topological or geometric features to clearly demonstrate the switching capability.

## (4) What are industrial applications of this concept?
Industrial applications include interactive design tools where users toggle between different design iterations, or medical software where doctors can switch between different anatomical layers or imaging modalities.

## (5) How this could be useful for downstream applications.
Event handling is essential for building interactive 3D applications. It enables the creation of user-controlled simulation environments, interactive parameter tuning, and custom modeling tools.
