# 113 Shadows

### (1) What does the code do?
This code demonstrates **shadow mapping** in the libigl viewer. It creates a ground plane (floor) automatically based on the mesh's bounding box and renders the mesh casting a shadow onto that floor. It also supports optional MatCap textures and custom light directions.

### (2) How many parameters are present in the code and how they impact the final results?
The code accepts several command-line arguments:
1.  **Mesh file path** (required): The 3D model that will cast the shadow.
2.  **MatCap image path** (optional): A texture to apply to the mesh.
3.  **lx, ly, lz** (optional): The x, y, and z components of the light direction.
4.  **ambient_from_matcap** (optional): A flag to derive the ambient light color from the MatCap texture.

The light direction determines the length and orientation of the shadow. The MatCap and ambient settings affect the surface shading of the object.

### (3) What the optimal value of the input parameters?
*   **Mesh**: Any valid triangle mesh. The shadow effect is most noticeable with meshes that have significant height or complex silhouettes.
*   **Light Direction**: A direction that is not directly vertical or horizontal relative to the floor (e.g., `1 2 0`) usually creates the most informative shadows.

### (4) What are industrial applications of this concept?
*   **Architectural Visualization**: Showing how buildings cast shadows on their surroundings throughout the day.
*   **E-commerce**: Providing a realistic "grounded" look for 3D product previews, helping users understand scale and position.
*   **Game Development**: Essential for visual depth and realism in any 3D environment.

### (5) How this could be useful for downstream applications.
Shadows are critical for **spatial perception**. In downstream applications like 3D assembly or medical planning, shadows help the user understand the relative distance between objects and surfaces. Implementing efficient shadow mapping is a prerequisite for any high-quality 3D visualization tool.
