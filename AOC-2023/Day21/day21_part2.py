# https://www.youtube.com/watch?v=xHIQ2zHVSjM
from copy import deepcopy
from math import ceil
from typing import List, Tuple

def read_grid(file_path: str) -> (List[str], Tuple[int, int]):
    """ Read the grid from the file and return the grid and the starting position. """
    lines = []
    start = None
    with open(file_path, "r", encoding="utf-8") as f:
        for line_count, line in enumerate(f):
            line = line.strip()
            lines.append(list(line))
            if "S" in line:
                start = (line_count, line.index("S"))
    return lines, start

def calculate_next_states(lines: List[str], start: Tuple[int, int], run: int) -> int:
    """ Calculate the next states based on the given run. """
    height = len(lines)
    width = len(lines[0])
    next_queue = [start]
    for _ in range(run):
        curr_queue = deepcopy(next_queue)
        visited = set(deepcopy(next_queue))
        next_queue = []
        for curr in curr_queue:
            for dir in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                new_y, new_x = curr[0] + dir[0], curr[1] + dir[1]
                if lines[new_y % height][new_x % width] != "#" and (new_y, new_x) not in visited:
                    visited.add((new_y, new_x))
                    next_queue.append((new_y, new_x))
    return len(next_queue)

def calculate_answer(lines: List[str], start: Tuple[int, int], steps: int) -> int:
    """ Calculate the final answer for part two. """
    height = len(lines)
    mod = steps % height
    seen_states = [calculate_next_states(lines, start, run) for run in [mod, mod + height, mod + height * 2]]
    m = seen_states[1] - seen_states[0]
    n = seen_states[2] - seen_states[1]
    a = (n - m) // 2
    b = m - 3 * a
    c = seen_states[0] - b - a
    ceiling = ceil(steps / height)
    return a * ceiling**2 + b * ceiling + c

def main():
    lines, start = read_grid("input.txt")
    answer = calculate_answer(lines, start, 26501365)
    print(f"Part 2: {answer}")

if __name__ == "__main__":
    main()

