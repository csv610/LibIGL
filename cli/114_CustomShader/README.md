# 114 Custom Shader

### (1) What does the code do?
This code demonstrates how to override the default libigl shader with a **custom GLSL shader**. Specifically, it implements a vertex and fragment shader that adds a **Fresnel effect** to the mesh. The Fresnel effect makes the surface more reflective at glancing angles, which is a key property of many real-world materials like glass, water, and car paint.

### (2) How many parameters are present in the code and how they impact the final results?
*   **Mesh file path** (required): The 3D model to be rendered with the custom shader.
*   **Hardcoded Shader Parameters**: The GLSL code inside `main.cpp` contains parameters like `specular_exponent`, `fresnel_exponent`, and `lighting_factor` which control the intensity and "sharpness" of the Fresnel reflection.

### (3) What the optimal value of the input parameters?
*   **Mesh**: A smooth, organic mesh (like the bunny or armadillo) is best for visualizing the Fresnel effect, as it provides a wide range of surface normal orientations relative to the viewer.
*   **Shader constants**: A high `specular_exponent` (e.g., 50+) creates a very polished look, while a lower value makes the material look more matte.

### (4) What are industrial applications of this concept?
*   **Game Engines**: Writing custom shaders is the standard way to achieve unique visual styles (Non-Photorealistic Rendering) or high-end material effects.
*   **Scientific Visualization**: Using custom shaders to map data (like stress, temperature, or flow) directly onto a mesh surface using GPU-accelerated colormaps.
*   **Automotive Design**: Simulating complex paint finishes with multi-layered Fresnel and pearlescent effects.

### (5) How this could be useful for downstream applications.
Learning to inject custom shaders into a viewer allows developers to:
*   **Optimize Performance**: Offload complex visual calculations to the GPU.
*   **Interactive Analysis**: Visualize geometric properties (like curvature or thickness) in real-time as the mesh is deformed or modified.
*   **Stylized Rendering**: Create blueprints, toon-shaded previews, or X-ray views for technical documentation or user interfaces.
