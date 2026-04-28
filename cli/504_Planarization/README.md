# 504 Planarization

## (1) What does the code do?
This code demonstrates how to planarize a quad mesh using libigl. It implements an iterative local-global approach to move the vertices of a quad mesh such that each face becomes more planar while attempting to keep the overall shape close to the original mesh. It provides a viewer to compare the original and planarized meshes and visualizes the planarity score using a color map.

## (2) How many parameters are present in the code and how they impact the final results?
The code includes several parameters via command-line arguments:
- `--iters`: The number of planarization iterations. More iterations generally lead to better planarity but increase the computation time.
- `--step`: The step size for each iteration. A larger step size can lead to faster convergence but may cause instability or excessive distortion of the mesh.
- `--input`: Path to the input quad mesh.
- `--output`: Path to save the resulting planarized mesh.
- `--score`: Path to save the mean and maximum planarity scores before and after the process.

## (3) What the optimal value of the input parameters?
- `--iters`: 100 is typically sufficient for most meshes to reach a stable planar state.
- `--step`: 0.005 is a recommended default for meshes with coordinates in a typical unit range.

## (4) What are industrial applications of this concept?
Planarization is crucial in architectural geometry, particularly for designing glass facades where planar panels are significantly cheaper and easier to manufacture and install than curved ones. It is also used in sheet metal forming and other manufacturing processes where flat materials are joined.

## (5) How this could be useful for downstream applications.
Planar quad meshes are often required for certain types of physical simulations, architectural fabrication, and efficient rendering. Ensuring planarity can also simplify texture mapping and other geometric processing tasks that assume or benefit from flat polygonal faces.
