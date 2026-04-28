# 305 Quadratic Programming

## (1) What does the code do?
This code solves a quadratic programming (QP) problem with both equality and inequality constraints (box constraints) using `igl::active_set`. It minimizes a bi-harmonic energy while forcing the solution to stay within the range [0, 1] and satisfying an integral equality constraint (sum of values weighted by mass matrix equals a constant).

## (2) How many parameters are present in the code and how they impact the final results?
- **Input mesh (-i)**: The domain for the QP.
- **Fixed point (b, bc)**: One vertex is fixed to value 1.
- **Box constraints (lx, ux)**: The solution is constrained to be between 0 and 1.
- **Equality constraint (Beq)**: The integral of the solution over the mesh is set to a specific value (default 0.08, adjustable with ',' and '.').

Increasing the equality constraint value 'Beq' forces the solution to "spread" more to satisfy the higher integral requirement.

## (3) What the optimal value of the input parameters?
Optimal values depend on the application. For visualization, the equality constraint 'Beq' should be chosen such that it doesn't conflict too strongly with the boundary conditions, or the active set solver might take many iterations to converge.

## (4) What are industrial applications of this concept?
- **Shape Optimization**: Designing surfaces that satisfy specific area or volume constraints.
- **Contact Mechanics**: Simulating objects that cannot penetrate each other (inequality constraints).
- **Image Processing**: Non-negative matrix factorization or image restoration with intensity bounds.

## (5) How this could be useful for downstream applications.
It provides a robust way to solve constrained optimization problems where simple linear solves are insufficient because of inequalities (like "no-penetration" or "non-negativity" requirements).
