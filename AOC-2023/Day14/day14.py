data = [list(line) for line in open("input.txt").read().strip().split("\n")]
length = len(data)
width = len(data[0])

for row_idx, line in enumerate(data):
    for col_idx, value in enumerate(line):
        if value == "O":
            decreasing_row_idx = row_idx - 1
            while data[decreasing_row_idx][col_idx] == "." and decreasing_row_idx >= 0:
                data[decreasing_row_idx][col_idx] = "O"
                data[decreasing_row_idx+1][col_idx] = "."
                decreasing_row_idx -= 1
mult = length
sum = 0
for row_idx, line in enumerate(data):
    print(line)
    for col_idx, value in enumerate(line):
       if value == "O":
           sum += mult
    mult -= 1
           
print('Part 1', sum) 