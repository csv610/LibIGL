# 710_SCAF

### (1) What does the code do?
This code demonstrates the Symmetric Dirichlet Energy via Augmented Lagrangian (SCAF) algorithm for mesh parameterization. It computes a low-distortion, flip-free 2D embedding (UV mapping) of a 3D triangle mesh. The algorithm is particularly robust at preventing triangle inversions even under extreme deformations or poor initializations.

### (2) How many parameters are present in the code and how they impact the final results?
The primary parameters include:
*   `--input (-i)`: (Required) The path to the input 3D triangle mesh.
*   `Iteration Count`: Each press of the spacebar executes one solver iteration, further reducing the mapping distortion.
*   `Mapping Energy`: The code uses the Symmetric Dirichlet energy, which penalizes both area and angular distortion.
*   `uv_scale`: A hardcoded visualization parameter (`0.2f`) that scales the UV coordinates for display purposes.

### (3) What the optimal value of the input parameters?
*   **Input Mesh:** A manifold triangle mesh with at least one boundary loop is ideal. SCAF can handle meshes with holes by automatically filling them during initialization.
*   **Iterations:** SCAF typically converges to a high-quality solution within 5-15 iterations for most meshes.

### (4) What are industrial applications of this concept?
*   **Digital Content Creation (DCC):** Professional UV unwrapping for high-resolution 3D characters and environments.
*   **Apparel Industry:** Flattening 3D garment designs into 2D patterns for fabric cutting.
*   **Cartography:** Creating conformal or area-preserving projections of geographic data.

### (5) How this could be useful for downstream applications.
SCAF provides a high-reliability mapping that can be used for:
*   Baking high-resolution textures or normal maps from high-poly to low-poly models.
*   Generating clean domains for surface-based neural networks.
*   Defining coordinate systems for procedural texturing and geometry synthesis.
