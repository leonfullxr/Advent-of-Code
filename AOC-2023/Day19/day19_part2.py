from math import prod

def parse_input():
    with open("input.txt") as file:
        workflow_input = file.read().split("\n\n")[0].split("\n")

    workflows = {}
    for line in workflow_input:
        name, rules_str = line.split("{")
        name = name.strip()
        rules = rules_str.rstrip("}").split(',')
        workflows[name] = rules
    return workflows

def calculate_combinations(workflows):
    parts = []
    initial_part = {"x": (1, 4000), "m": (1, 4000), "a": (1, 4000), "s": (1, 4000)}
    nodes = [("in", initial_part)]

    while nodes:
        wf, part = nodes.pop()
        for rule in workflows[wf]:
            if ":" in rule:
                condition, cond_wf = rule.split(':')
                category = condition[0]
                operation = condition[1]
                threshold = int(condition[2:])
                cond_part = part.copy()

                if operation == '<':
                    cond_part[category] = (cond_part[category][0], threshold - 1)
                    part[category] = (threshold, part[category][1])
                elif operation == '>':
                    cond_part[category] = (threshold + 1, cond_part[category][1])
                    part[category] = (part[category][0], threshold)

                if cond_wf in ["A", "R"]:
                    if cond_wf == "A":
                        parts.append(cond_part)
                else:
                    nodes.append((cond_wf, cond_part))
            else:
                if rule in ["A", "R"]:
                    if rule == "A":
                        parts.append(part.copy())
                else:
                    nodes.append((rule, part.copy()))

    total_combinations = sum(prod(v[1] - v[0] + 1 for v in part.values()) for part in parts)
    return total_combinations

def main():
    workflows = parse_input()
    total_accepted_combinations = calculate_combinations(workflows)
    print("Part 2:", total_accepted_combinations)

if __name__ == '__main__':
    main()
