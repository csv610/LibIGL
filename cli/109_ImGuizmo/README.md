# 109_ImGuizmo

## (1) What does the code do?
The code demonstrates interactive 3D mesh transformation using the ImGuizmo library. It provides an on-screen gizmo that allows the user to translate, rotate, and scale a mesh directly in the 3D viewer.

## (2) How many parameters are present in the code and how they impact the final results?
There is 1 parameter:
- `-i/--input`: Path to the input mesh file. This parameter specifies the object that the user will interactively transform.

## (3) What the optimal value of the input parameters?
The optimal value is a path to a well-defined mesh, such as `cow.off`.

## (4) What are industrial applications of this concept?
Industrial applications include 3D scene editing for movies and games, manual alignment of 3D scans in reverse engineering, and virtual staging in architecture.

## (5) How this could be useful for downstream applications.
Interactive transformation tools are vital for any application requiring manual alignment or placement of 3D objects. It can be used for initial setup before automated registration algorithms or for artistic mesh deformation.
