data = open("input.txt").read().strip().split("\n")

lines = []

for line in data:
    if "#" in line:
        lines.append(line)
    else:
        lines.extend([line, line])

doubled_cols = []

for col_index in range(len(lines[0])):
    column = [line[col_index] for line in lines]
    if "#" not in column:
        doubled_cols.append(col_index)

universe = []
for line in lines:
    row = []
    for col_index in range(len(line)):
        if col_index in doubled_cols:
            row.extend([line[col_index], line[col_index]])
        else:
            row.append(line[col_index])
    universe.append(row)

width = len(universe[0])
height = len(universe)

galaxies = []
for row_index in range(height):
    for col_index in range(width):
        if universe[row_index][col_index] == "#":
            galaxies.append((col_index, row_index))

length_sum = 0
for row_index in range(len(galaxies)):
    for col_index in range(row_index + 1, len(galaxies)):
        x1, y1 = galaxies[row_index]
        x2, y2 = galaxies[col_index]

        length_sum += abs(x1 - x2) + abs(y1 - y2)

print("Part 1:", length_sum)