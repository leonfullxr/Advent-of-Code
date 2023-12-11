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

length_sum = 0
for row_index in range(len(galaxies)):
    for col_index in range(row_index + 1, len(galaxies)):

        length_sum += (abs(galaxies[row_index][0] - galaxies[col_index][0]) 
                       + 
                       abs(galaxies[row_index][1] - galaxies[col_index][1]))


print("Part 2:", length_sum)