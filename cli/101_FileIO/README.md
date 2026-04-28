# 101_FileIO

## (1) What does the code do?
The code demonstrates basic mesh file I/O using libigl. It reads a triangle mesh from a specified input file (supporting formats like OFF, OBJ, etc.), prints its vertex and face data to the console, and then writes the mesh to a specified output file.

## (2) How many parameters are present in the code and how they impact the final results?
There are 2 parameters:
- `-i/--input`: Path to the input mesh file. This determines the source geometry to be processed.
- `-o/--output`: Path to the output mesh file. This determines where and in what format the resulting mesh will be saved.

## (3) What the optimal value of the input parameters?
The optimal value for the input parameter is any valid path to a clean, manifold triangle mesh file (e.g., `cube.off` or `bunny.off`). The output path should be a valid writable path with a desired extension like `.obj`.

## (4) What are industrial applications of this concept?
Industrial applications include 3D model format conversion, mesh preprocessing for CAD/CAM workflows, and data exchange between different specialized 3D modeling and simulation softwares.

## (5) How this could be useful for downstream applications.
This functionality is foundational for any mesh processing pipeline. Downstream applications rely on robust loading and saving of geometric data to perform analysis, deformation, or fabrication-ready optimizations.
