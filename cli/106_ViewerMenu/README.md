# 106_ViewerMenu

## (1) What does the code do?
This tutorial demonstrates how to integrate and customize a Graphical User Interface (GUI) using the ImGui library within the libigl viewer. It shows how to create custom menus, buttons, checkboxes, and windows to interactively control application variables.

## (2) How many parameters are present in the code and how they impact the final results?
There is 1 parameter:
- `-i/--input`: Path to the input mesh file. This mesh is loaded into the viewer, while the custom GUI elements allow the user to interact with the viewer's state and other dummy variables.

## (3) What the optimal value of the input parameters?
The optimal value is a path to a valid mesh file like `bunny.off`.

## (4) What are industrial applications of this concept?
Industrial applications include building control panels for complex engineering software, parameter tuning for 3D printing preparation, and interactive medical visualization tools where users adjust rendering settings.

## (5) How this could be useful for downstream applications.
Providing a GUI is essential for making complex geometric algorithms accessible to non-technical users. It allows for real-time parameter exploration, which is crucial for fine-tuning algorithms like mesh refinement or physical simulations.
