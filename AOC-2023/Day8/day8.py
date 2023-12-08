import re
import math

data = open("input.txt").read().strip().split("\n")

instructions = data[0]
elements = data[2:len(data)]
nodes = {}
starting_nodes = []

for node in elements:
    source, left, right = re.findall(r"([A-Z]{3})", node)
    nodes[source] = [left, right]
    if source[2] == "A":
        starting_nodes.append(source)

    
start_node = "AAA"
index = 0
steps = 0

while start_node != "ZZZ":
    start_node = nodes[start_node][0 if instructions[index] == "L" else 1]
    index = (index + 1) % len(instructions)
    steps += 1

print("Part 1:", steps)

index = 0
final_steps = []

for node in starting_nodes:
    steps = 0
    while node[2] != "Z":
        left, right = nodes[node]
        node = left if instructions[index] == "L" else right
        index = (index + 1) % len(instructions)
        steps += 1
    final_steps.append(steps)
    
print('Part 2', math.lcm(*final_steps))

