import re

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

# Part 2
index = 0
steps = 0
//TODO: optimize this
while not all(node[2] == "Z" for node in starting_nodes):
    current_nodes_index = 0
    current_nodes = []
    for node in starting_nodes:
        left, right = nodes[node]
        current_nodes.append(left if instructions[index] == "L" else right)
    index = (index + 1) % len(instructions)
    starting_nodes = current_nodes
    print(steps > 20685524831999)
    steps += 1

print("Part 2:", steps)
