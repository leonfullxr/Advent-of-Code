from collections import deque
# https://en.wikipedia.org/wiki/Pick%27s_theorem

def get_boundary_points(path_points):
    current_x, current_y = 0, 0
    path = [(current_x, current_y)]
    
    for direction, steps in path_points:
        steps = int(steps)
        dx, dy = 0, 0
        if direction == 'R':
            dy = 1
        elif direction == 'L':
            dy = -1
        elif direction == 'U':
            dx = -1
        elif direction == 'D':
            dx = 1
        for _ in range(steps):
            current_x += dx
            current_y += dy
            path.append((current_x, current_y))
    return path

def calculate_area(path_points):
    area = 0
    n = len(path_points)
    for i in range(n):
        x1, y1 = path_points[i]
        x2, y2 = path_points[(i + 1) % n]
        area += (x1 * y2) - (x2 * y1)
    return abs(area) // 2

def main():
    data = [line.strip().split() for line in open("input.txt").readlines()]
    path_points = deque([(d[0], d[1]) for d in data])

    boundary_points = get_boundary_points(path_points)
    area = calculate_area(boundary_points)
    num_points = len(boundary_points)
    number_inner_points = area - num_points // 2 + 1
    print(number_inner_points + num_points)

if __name__ == '__main__':
    main()
