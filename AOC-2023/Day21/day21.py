from collections import deque

def is_valid_cell(row, col, grid, visited):
    if row < 0 or row >= len(grid) or col < 0 or col >= len(grid[0]):
        return False
    if grid[row][col] == "#":
        return False
    if (row, col) in visited:
        return False
    return True

def find_starting_point(grid):
    for row_index, row in enumerate(grid):
        for col_index, cell in enumerate(row):
            if cell == "S":
                return row_index, col_index

def explore_grid(grid, steps=64):
    start_row, start_col = find_starting_point(grid)
    visited = set([(start_row, start_col)])
    answer_points = set()
    queue = deque([(start_row, start_col, steps)])

    while queue:
        current_row, current_col, steps_remaining = queue.popleft()

        if steps_remaining % 2 == 0:
            answer_points.add((current_row, current_col))

        if steps_remaining == 0:
            continue

        adjacent_cells = [
            (current_row + 1, current_col),  # down
            (current_row - 1, current_col),  # up
            (current_row, current_col + 1),  # right
            (current_row, current_col - 1)   # left
        ]
        
        for next_row, next_col in adjacent_cells:
            if is_valid_cell(next_row, next_col, grid, visited):
                visited.add((next_row, next_col))
                queue.append((next_row, next_col, steps_remaining - 1))

    return len(answer_points)


def main():
    grid = open("input.txt").read().splitlines()
    number_of_answer_points = explore_grid(grid)
    print('Part 1',number_of_answer_points)

if __name__ == '__main__':
    main()
