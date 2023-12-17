from collections import deque

def calculate_beams(row, col, dir_row, dir_col, grid):
    a = [(row, col, dir_row, dir_col)]
    seen = set()
    q = deque(a)

    while q:
        row, col, dir_row, dir_col = q.popleft()

        row += dir_row
        col += dir_col

        if row < 0 or row >= len(grid) or col < 0 or col >= len(grid[0]):
            continue

        value = grid[row][col]
        
        if value == "." or (value == "-" and dir_col != 0) or (value == "|" and dir_row != 0):
            if (row, col, dir_row, dir_col) not in seen:
                seen.add((row, col, dir_row, dir_col))
                q.append((row, col, dir_row, dir_col))
        elif value == "/":
            # (0, 1) -> (-1, 0)
            # (1, 0) -> (0, -1)
            # (-1,0) -> (0, 1)
            # (0, -1) -> (1, 0)
            dir_row, dir_col = -dir_col, -dir_row
            if (row, col, dir_row, dir_col) not in seen:
                seen.add((row, col, dir_row, dir_col))
                q.append((row, col, dir_row, dir_col))
        elif value == "\\":
            # (0, 1) -> (1, 0)
            # (1, 0) -> (0, 1)
            dir_row, dir_col = dir_col, dir_row
            if (row, col, dir_row, dir_col) not in seen:
                seen.add((row, col, dir_row, dir_col))
                q.append((row, col, dir_row, dir_col))
        else:
            if value == "|":
                new_directions = [(1, 0), (-1, 0)]
            else:  # value is "-"
                new_directions = [(0, 1), (0, -1)]

            for new_dir_row, new_dir_col in new_directions:
                if (row, col, new_dir_row, new_dir_col) not in seen:
                    seen.add((row, col, new_dir_row, new_dir_col))
                    q.append((row, col, new_dir_row, new_dir_col))
                    
    coordenates = {(row, col) for (row, col, _, _) in seen}
    
    return len(coordenates)

def main():
    grid = open("input.txt").read().strip().split("\n")
    
    print('Part 1', max(0, calculate_beams(0, -1, 0, 1, grid)))

    max_val = 0

    for row in range(len(grid)):
        max_val = max(max_val, calculate_beams(row, -1, 0, 1, grid))
        max_val = max(max_val, calculate_beams(row, len(grid[0]), 0, -1, grid))
        
    for col in range(len(grid)):
        max_val = max(max_val, calculate_beams(-1, col, 1, 0, grid))
        max_val = max(max_val, calculate_beams(len(grid), col, -1, 0, grid))

    print('Part 2', max_val)

if __name__ == '__main__':
    main()