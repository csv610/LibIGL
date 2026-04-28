# 306 Eigen Decomposition

## (1) What does the code do?
This program computes the first few generalized eigenvalues and eigenvectors of the Discrete Laplace-Beltrami operator (using `igl::eigs`). These are known as the "Manifold Harmonics". The code visualizes these eigenvectors as scalar fields on the mesh and can also use them to displace vertices for 2D meshes.

## (2) How many parameters are present in the code and how they impact the final results?
- **Input mesh (-i)**: The geometry used to build the Laplacian.
- **Number of eigenvectors (k)**: The code computes the first 5 non-trivial eigenvectors.

The eigenvectors represent different "frequencies" of the surface. Lower-order eigenvectors represent low-frequency, global variations, while higher-order ones represent more localized, high-frequency details.

## (3) What the optimal value of the input parameters?
For spectral analysis, the mesh should be well-tessellated. The number of eigenvectors 'k' depends on how much "spectral resolution" is needed for the application.

## (4) What are industrial applications of this concept?
- **Shape Analysis/Matching**: Using spectral signatures to compare 3D models.
- **Geometry Compression**: Representing shapes as a sum of basis functions (spectral compression).
- **Modal Analysis**: In structural engineering, finding the natural vibration modes of a part.

## (5) How this could be useful for downstream applications.
Spectral methods are powerful for smoothing, filtering, and finding correspondences between different shapes. They provide a "Fourier transform" for surfaces.
