# 402 Polyharmonic Deformation

## (1) What does the code do?
This program explores poly-harmonic interpolation, where the order of the Laplacian 'k' in the equation $\Delta^k \phi = 0$ can be varied. It solves this equation on a 2D domain and visualizes the resulting "bump" as it evolves for different values of k (harmonic, bi-harmonic, tri-harmonic, etc.).

## (2) How many parameters are present in the code and how they impact the final results?
- **Input mesh (-i)**: The 2D domain (usually a disk or annulus).
- **Harmonic order (k)**: Adjustable with ',' and '.'.
    - k=1 (Harmonic): Least smooth, "tent-like" behavior at constraints.
    - k=2 (Bi-harmonic): C1 continuity at constraints, standard smooth bump.
    - k=3 (Tri-harmonic): Even smoother transitions.

Increasing k results in a "flatter" bump with smoother transitions at the boundaries.

## (3) What the optimal value of the input parameters?
k=2 (bi-harmonic) is most commonly used in geometric modeling as it provides a good trade-off between smoothness (C1) and avoiding the "overshoot" that can happen with higher-order polynomials.

## (4) What are industrial applications of this concept?
- **Spline Surfaces**: Designing smooth transitions in CAD.
- **Signal Processing**: High-order filtering of signals on graphs or meshes.
- **Scientific Visualization**: Creating smooth isosurfaces from sparse data points.

## (5) How this could be useful for downstream applications.
It allows for fine-tuning the "stiffness" or "smoothness" of an interpolation field. In weight computation for skinning (like Bounded Biharmonic Weights), the order of the Laplacian determines the falloff behavior of the influence of different handles.
