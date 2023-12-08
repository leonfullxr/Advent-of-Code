import re

data = open("input.txt").read().strip().split("\n")

instructions = data[0]
elements = data[2:-1]
nodes = {}

for node in elements:
    source, left, right = re.findall(r"([A-Z]{3})", node)
    nodes[source] = [left, right]
    
start_node = "AAA"
index = 0
steps = 0

while start_node != "ZZZ":
    start_node = nodes[start_node][0 if instructions[index] == "L" else 1]
    index = (index + 1) % len(instructions)
    steps += 1

print("Part 1:", steps)