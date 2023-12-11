data = open("input.txt").read().strip().split("\n")

lines = []
for line in data:
    if "#" in line:
        lines.append(line)
    else:
        lines.extend([line, line])