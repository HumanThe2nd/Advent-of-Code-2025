# AOC Day 10 Part 2 Solution
# Created: 12/20/2025
# Requires 'pulp' package for linear programming.
# Install via pip if not already installed:
# pip install pulp
# NOTE: Create a separate file named 'input.txt' in the same directory with the input data.

import sys
import re
import pulp

def parse_line(line):
    """Parse a line of the form:
       [...] (a,b) (c,d,e) {t0,t1,...}
       Return list_of_button_index_lists, target_list (ints).
    """
    # find all parenthesis groups -> buttons
    buttons = []
    for m in re.finditer(r'\(([^)]*)\)', line):
        inside = m.group(1).strip()
        if inside == "":
            buttons.append([])
            continue
        nums = [int(x) for x in re.findall(r'\d+', inside)]
        buttons.append(nums)

    # find curly braces -> target
    m = re.search(r'\{([^}]*)\}', line)
    if not m:
        return None, None
    inside = m.group(1).strip()
    if inside == "":
        target = []
    else:
        target = [int(x) for x in re.findall(r'\d+', inside)]

    return buttons, target

def machine_min_presses(buttons_idx, target, solver_choice="CBC"):
    d = len(target)
    m = len(buttons_idx)

    # quick infeasibility check: any target dimension with no affecting button but target>0 -> impossible
    for j in range(d):
        ok = False
        for bi in buttons_idx:
            if j in bi:
                ok = True
                break
        if not ok and target[j] > 0:
            raise ValueError(f"Impossible to reach target at counter {j} (no button affects it)")

    # Build B matrix as list of sets for fast membership
    B = [set(lst) for lst in buttons_idx]

    # Create LP
    prob = pulp.LpProblem("machine_min_presses", pulp.LpMinimize)

    # Variables: x_i >= 0 integer
    x_vars = [pulp.LpVariable(f"x_{i}", lowBound=0, cat="Integer") for i in range(m)]

    # Objective: minimize sum x_i
    prob += pulp.lpSum(x_vars)

    # Constraints: for each counter j, sum_i B[j,i]*x_i == target[j]
    for j in range(d):
        if target[j] == 0:
            # Still add the constraint to force exact equality
            prob += pulp.lpSum( (x_vars[i] for i in range(m) if j in B[i]) ) == 0
        else:
            prob += pulp.lpSum( (x_vars[i] for i in range(m) if j in B[i]) ) == target[j]

    # Choose solver
    if solver_choice.upper() == "HIGHS":
        solver = pulp.PULP_CBC_CMD(msg=False)  # fallback if HiGHS not available
        try:
            # prefer highs if installed
            solver = pulp.HiGHS_CMD(msg=False)
        except Exception:
            # HiGHS not available; fall back to CBC quietly
            solver = pulp.PULP_CBC_CMD(msg=False)
    else:
        solver = pulp.PULP_CBC_CMD(msg=False)

    # Solve
    res = prob.solve(solver)

    status = pulp.LpStatus.get(prob.status, "Undefined")
    if status != "Optimal":
        # If solver returns Infeasible or something else
        raise ValueError(f"Solver status: {status}")

    # objective value should be integer
    obj = pulp.value(prob.objective)
    if obj is None:
        raise ValueError("Solver produced no objective value")

    return int(round(obj))

def main():
    res = 0
    solver_choice = "CBC"

    with open("input.txt") as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            buttons_idx, target = parse_line(line)
            if buttons_idx is None or target is None:
                continue
            best = machine_min_presses(buttons_idx, target, solver_choice)
            res += best

    print(res)

if __name__ == "__main__":
    main()
# my sol: 21696
