# 907 Dynamic AABB

### (1) What does the code do?
This code demonstrates a dynamic AABB (Axis-Aligned Bounding Box) tree that can be updated in real-time as mesh vertices are moved. It allows for interactive deformation of the mesh while maintaining an efficient spatial data structure for intersection queries.

### (2) How many parameters are present in the code and how they impact the final results?
- `depth`: Controls the level of detail when visualizing the AABB tree's boxes. A higher depth shows more, smaller boxes that more tightly bound the geometry.

### (3) What the optimal value of the input parameters?
A `depth` of 3 to 7 is usually optimal for visualization, as it clearly shows the hierarchy without over-cluttering the scene.

### (4) What are industrial applications of this concept?
Real-time collision detection in video games, interactive sculpting tools, and cloth or soft-body simulations in physics engines.

### (5) How this could be useful for downstream applications.
A dynamic AABB tree is critical for any application involving moving geometry, such as character animation, real-time physics, and interactive 3D modeling.
