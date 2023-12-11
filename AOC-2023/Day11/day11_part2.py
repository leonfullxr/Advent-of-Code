data = open("input.txt").read().strip().split("\n")

lines = []
for line in data:
    if "#" in line:
        lines.append((line,False))
    else:
        lines.append((line,True))
        
extended_cols = set()
for col_index in range(len(lines[0][0])):
    column = [line[0][col_index] for line in lines]
    if "#" not in column:
        extended_cols.add(col_index)
        
galaxies = []
ry_offset = 0
EXPANSION_FACTOR = 1000000

for row_index, (row_content, row_expanded) in enumerate(lines):
    rx_offset = 0
    for col_index in range(len(row_content)):
        if row_content[col_index] == "#":
            galaxies.append((rx_offset, ry_offset))

        rx_offset += EXPANSION_FACTOR if col_index in extended_cols else 1

    ry_offset += EXPANSION_FACTOR if row_expanded else 1


def calculate_length_sum(galaxies):
    length_sum = 0
    for i in range(len(galaxies)):
        for j in range(i + 1, len(galaxies)):
            x1, y1 = galaxies[i]
            x2, y2 = galaxies[j]
            length_sum += abs(x1 - x2) + abs(y1 - y2)
    return length_sum


print("Part 2:", calculate_length_sum(galaxies))