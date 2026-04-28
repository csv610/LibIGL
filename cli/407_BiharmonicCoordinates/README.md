# 407_BiharmonicCoordinates

### (1) What does the code do?
This code demonstrates how to use **Biharmonic Coordinates** to transfer deformations from a low-resolution "proxy" mesh to a high-resolution "target" mesh. The low-resolution mesh is animated using a dynamic ARAP simulation (including gravity and collisions), and its movements are interpolated across the high-resolution mesh using pre-computed biharmonic weights.

### (2) How many parameters are present in the code and how they impact the final results?
The main parameters are:
*   **Low-Res Mesh (-i1/--input1):** The proxy mesh used for simulation.
*   **High-Res Mesh (-i2/--input2):** The high-detail mesh that receives the deformation.
*   **Interpolation Order (k):** Hardcoded to 2 for biharmonic interpolation. This controls the smoothness of the weight functions.
*   **ARAP Dynamics (h, ym):** Time step and Young's modulus for the physical simulation.

### (3) What the optimal value of the input parameters?
*   **Interpolation Order:** `k=2` is the standard for biharmonic coordinates, providing $C^1$ smoothness. While `k=3` (triharmonic) provides $C^2$ smoothness, it is more computationally expensive and often unnecessary for visual applications.
*   **Proxy Mesh:** The low-resolution mesh should ideally be a simplified version of the high-resolution mesh to ensure that the closest-point mapping between handles and target vertices is accurate.

### (4) What are industrial applications of this concept?
Biharmonic coordinates are widely used for **Cage-based Deformation** and **Free-Form Deformation (FFD)** in tools like Blender and Maya. It allows artists to animate complex characters by only manipulating a simple surrounding cage or a low-poly proxy.

### (5) How this could be useful for downstream applications.
This technique is vital for:
*   Real-time animation of high-poly cinematic characters.
*   Efficient physical simulations (simulating the proxy is much faster than simulating the full model).
*   Transferring motion between different models with similar topology.
