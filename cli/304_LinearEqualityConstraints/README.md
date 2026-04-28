# 304 Linear Equality Constraints

## (1) What does the code do?
This example demonstrates how to solve a quadratic minimization problem subject to linear equality constraints using `igl::min_quad_with_fixed`. It specifically solves a bi-harmonic problem (minimizing the Laplacian energy) on a 3D mesh. It shows the difference between a solution with only fixed-value constraints (Dirichlet boundary conditions) and a solution that additionally includes a linear equality constraint (e.g., forcing two vertices to have the same value).

## (2) How many parameters are present in the code and how they impact the final results?
- **Input mesh (-i)**: The geometry on which the bi-harmonic equation is solved.
- **Fixed vertices (b, bc)**: In the code, two vertices (left hand and left foot) are fixed to values 1 and -1.
- **Linear equality constraint (Aeq, Beq)**: A constraint is added that forces the values at two other vertices (right hand and right foot) to be equal (their difference is zero).

The results are visualized as a scalar field (pseudocolors) representing the solution Z.

## (3) What the optimal value of the input parameters?
There aren't "optimal" values in the sense of performance tuning, but the input mesh should be a manifold triangle mesh for the cotangent Laplacian to be well-behaved. The choice of fixed points and equality constraints depends on the desired interpolation or deformation effect.

## (4) What are industrial applications of this concept?
- **Geometric Modeling**: Smooth surface deformation and hole filling.
- **Physics Simulation**: Solving heat equations or structural mechanics problems with specific constraints (e.g., rigid links between parts).
- **Data Interpolation**: Smoothly interpolating values across a surface while maintaining specific relationships between different regions.

## (5) How this could be useful for downstream applications.
This technique is fundamental for constrained mesh deformation, where a user wants to move parts of a mesh while keeping others fixed or maintaining specific geometric relationships (like symmetry or planarity) through linear constraints.
