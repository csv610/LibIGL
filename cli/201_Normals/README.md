# 201 Normals

### (1) What does the code do?
The code computes three different types of surface normals for a given triangle mesh:
- **Per-face normals**: Computed for each triangle, representing the orientation of the face.
- **Per-vertex normals**: Computed for each vertex, typically by averaging the normals of the incident faces (often weighted by area or angle).
- **Per-corner normals**: Computed for each corner (half-edge) of each face. This allows for sharp edges (creases) by assigning different normals to the same vertex depending on which face is being considered, controlled by a user-defined crease angle.

### (2) How many parameters are present in the code and how they impact the final results?
The code includes two primary input parameters:
- **Input Mesh (`-i`, `--input`)**: The path to the 3D mesh file. This is the geometry upon which normals are calculated.
- **Crease Angle (`-c`, `--crease`)**: A threshold angle (in degrees). If the dihedral angle between two adjacent faces exceeds this value, the edge between them is treated as a sharp crease, and the corner normals will not be averaged across it. This directly impacts the visual smoothness and shading of the mesh.
- **Output Path (`-o`, `--output`)** and **Type (`-t`, `--type`)**: Optional parameters to save the computed normals to a JSON file.

### (3) What the optimal value of the input parameters?
- **Crease Angle**: There is no single "optimal" value as it depends on the mesh geometry and desired aesthetic. However, a common default is **20 to 60 degrees**. Lower values (e.g., 20) result in more sharp edges, while higher values (e.g., 90+) result in a smoother appearance.
- **Normal Type**: Per-vertex normals are generally optimal for smooth shading (Gouraud/Phong), while per-face normals are better for flat shading. Per-corner normals are optimal for models with a mix of smooth surfaces and sharp features (like CAD models).

### (4) What are industrial applications of this concept?
- **Computer Graphics Rendering**: Normals are essential for calculating light reflection, shading, and visibility in 3D engines (Unity, Unreal).
- **Computer-Aided Design (CAD)**: Accurate corner normals are used to represent sharp features in mechanical parts.
- **Surface Analysis**: Normals are used to detect surface defects or analyze the orientation of components in manufacturing.

### (5) How this could be useful for downstream applications.
- **Curvature Estimation**: Many curvature algorithms (Gaussian, Mean) rely on accurate normal information.
- **Feature Detection**: Sharp edges identified during corner normal calculation can be used for mesh segmentation or feature-preserving simplification.
- **Collision Detection**: Normals are used to determine the direction of response forces when objects collide.
- **Ambient Occlusion**: Normal vectors are critical for calculating how much ambient light reaches a point on the surface.
