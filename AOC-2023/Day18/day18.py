from collections import deque
   
def point_inside(x, y, path_points) -> bool:    
    num = len(path_points)
    j = num - 1
    c = False
    for i in range(num):
        if (x == path_points[i][0]) and (y == path_points[i][1]):
            # point is a corner
            return True
        if (path_points[i][1] > y) != (path_points[j][1] > y):
            slope = (x - path_points[i][0]) * (path_points[j][1] - path_points[i][1]) - (
                path_points[j][0] - path_points[i][0]
            ) * (y - path_points[i][1])
            if slope == 0:
                # point is on boundary
                return True
            if (slope < 0) != (path_points[j][1] < path_points[i][1]):
                c = not c
        j = i
    return c
    
    
def construct_grid(path_points):
    path = deque()
    current_x, current_y = 0, 0
    
    while path_points:
        direction, steps = path_points.popleft()
        steps = int(steps)
        
        if direction == 'R':
            for _ in range(steps):
                current_y += 1
                path.append((current_x, current_y))
        elif direction == 'L':
            for _ in range(steps):
                current_y -= 1
                path.append((current_x, current_y))
        elif direction == 'U':
            for _ in range(steps):
                current_x -= 1
                path.append((current_x, current_y))
        elif direction == 'D':
            for _ in range(steps):
                current_x += 1
                path.append((current_x, current_y))
                
    # All the points cant be inserted into the matrix, so we need to find the max x and y
    # Calculate the offset and insert the points into the matrix
    
    # Get min and max x and y from the path
    min_x, min_y = min(path, key=lambda x: x[0])[0], min(path, key=lambda x: x[1])[1]
    max_x, max_y = max(path, key=lambda x: x[0])[0], max(path, key=lambda x: x[1])[1]
    
    # Calculate the offset
    if min_x < 0:
        offset_x = abs(min_x)
    else:
        offset_x = 0
        
    if min_y < 0:
        offset_y = abs(min_y)
    else:
        offset_y = 0
        
    # Initialize the grid to '.'s
    grid = [['.' for _ in range(max_y + offset_y+1)] for _ in range(max_x + offset_x+1)]
    # sum offsets to points in path
    path = [(x+offset_x, y+offset_y) for x, y in path]

    for row_idx in range(max_x + offset_x+1):
        for col_idx in range(max_y + offset_y+1):
            if (row_idx, col_idx) in path:
                grid[row_idx][col_idx] = '#'
            elif point_inside(row_idx, col_idx, path):
                grid[row_idx][col_idx] = '#'
   
    return grid


def main():
    data = open("input.txt").read().strip().split("\n")
    directions, steps = [], []
    path_points = deque()
    
    for row_idx, line in enumerate(data):
        directions.append(line[0]) 
        steps.append(line[2]) 
        path_points.insert(row_idx, (directions[-1], steps[-1]))
        
    grid = construct_grid(path_points)
    
    print('Part 1: ', sum([row.count('#') for row in grid]))
       
if __name__ == '__main__':
    main()