import os

dirs = [
    "201_Normals", "202_GaussianCurvature", "203_CurvatureDirections", "204_Gradient", "205_Laplacian",
    "206_GeodesicDistance", "207_PolygonLaplacian", "301_Slice", "302_Sort", "303_LaplaceEquation",
    "304_LinearEqualityConstraints", "305_QuadraticProgramming", "306_EigenDecomposition",
    "401_BiharmonicDeformation", "402_PolyharmonicDeformation", "403_BoundedBiharmonicWeights",
    "404_DualQuaternionSkinning", "405_AsRigidAsPossible"
]

for d in dirs:
    path = os.path.join(d, "main.cpp")
    if not os.path.exists(path): continue
    if d in ["201_Normals", "202_GaussianCurvature"]: continue
    
    with open(path, 'r') as f:
        content = f.read()
    
    lines = content.split('\n')
    new_lines = []
    i = 0
    changed = False
    while i < len(lines):
        line = lines[i]
        if ".add_argument" in line:
            statement_lines = [line]
            j = i + 1
            while j < len(lines) and ";" not in lines[j-1]:
                statement_lines.append(lines[j])
                j += 1
            statement = "\n".join(statement_lines)
            
            if any(kw in statement for kw in ["--input", "-i", "--selection", "--tgf", "--pose", "--weights"]):
                if ".default_value" in statement:
                    start_idx = statement.find(".default_value(")
                    if start_idx != -1:
                        depth = 0
                        end_idx = -1
                        for k in range(start_idx + 14, len(statement)):
                            if statement[k] == '(': depth += 1
                            elif statement[k] == ')':
                                if depth == 0:
                                    end_idx = k
                                    break
                                else:
                                    depth -= 1
                        
                        if end_idx != -1:
                            new_statement = statement[:start_idx] + ".required()" + statement[end_idx+1:]
                            new_lines.extend(new_statement.split('\n'))
                            i = j
                            changed = True
                            continue
            
            new_lines.extend(statement_lines)
            i = j
        else:
            new_lines.append(line)
            i += 1
            
    if changed:
        new_content = "\n".join(new_lines)
        with open(path, 'w') as f:
            f.write(new_content)
        print(f"Updated {path}")
