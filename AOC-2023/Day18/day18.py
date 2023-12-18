from collections import deque
# https://en.wikipedia.org/wiki/Pick%27s_theorem
# https://en.wikipedia.org/wiki/Shoelace_formula

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
        current_x, current_y = current_x + dx * steps, current_y + dy * steps
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

def parse_input():
    path_points = deque()
    color, steps, direction = [], None, None
    data = [line.strip().split() for line in open("input.txt").readlines()]
    num_boundary_points = 0
    
    for line in data:
        color = line[2]
        if color[-2] == '0':
            direction = 'R'
        elif color[-2] == '2':
            direction = 'L'
        elif color[-2] == '3':
            direction = 'U'
        elif color[-2] == '1':
            direction = 'D'
        steps = int(color[2:-2],16)
        path_points.append((direction, steps))
        num_boundary_points += steps
    return path_points, num_boundary_points

def get_inner_points(path_points, num_boundary_points):
    boundary_points = get_boundary_points(path_points)
    area = calculate_area(boundary_points)
    num_points = num_boundary_points
    number_inner_points = area - num_points // 2 + 1
    return number_inner_points + num_points

def main():
    data = [line.strip().split() for line in open("input.txt").readlines()]
    path_points = deque([(d[0], d[1]) for d in data])
    num_boundary_points = sum([int(d[1]) for d in data])

    print('Part 1', get_inner_points(path_points, num_boundary_points))
    
    path_points, num_boundary_points = parse_input()
    
    print('Part 2', get_inner_points(path_points, num_boundary_points))

if __name__ == '__main__':
    main()
