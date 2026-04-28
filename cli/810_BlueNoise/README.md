# Blue Noise Sampling

### (1) What does the code do?
The code generates a blue noise point sampling on the surface of a 3D triangle mesh. Unlike white noise (random sampling), blue noise distributions have a characteristic "even" spacing between points, avoiding both clusters and large gaps. This is achieved using the `igl::blue_noise` function, which implements a Poisson-disk-like sampling on the mesh.

### (2) How many parameters are present in the code and how they impact the final results?
There is one primary parameter:
- **`num_points`**: The desired number of points to sample.
This parameter is used to heuristically determine a radius `r` for the blue noise sampling. A larger `num_points` results in a smaller radius and a denser, more uniform distribution of points.

### (3) What the optimal value of the input parameters?
The "optimal" value depends entirely on the resolution of the mesh and the requirements of the downstream task. For general visualization or stippling, 50,000 points (the default) provides a good balance between density and performance on typical models like the elephant.

### (4) What are industrial applications of this concept?
- **Computer Graphics:** Digital stippling, artistic rendering, and texture synthesis.
- **Physics Simulation:** Generating well-spaced particles for SPH (Smoothed Particle Hydrodynamics) or other particle-based methods.
- **Manufacturing:** Optimal placement of sensors or structural components on a surface.

### (5) How this could be useful for downstream applications.
Blue noise sampling is an excellent starting point for:
- **Remeshing:** Providing initial sites for Voronoi-based remeshing (e.g., Centroidal Voronoi Tesselation).
- **Point Cloud Generation:** Creating high-quality point cloud representations of surfaces for machine learning.
- **Surface Reconstruction:** Providing uniform samples for testing reconstruction algorithms.
