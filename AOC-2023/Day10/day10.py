from collections import deque

data = open('input.txt', 'r').read().strip().split('\n')

width = len(data[0])
height = len(data)
connections = {}
grid = data

# Create a dictionary with all the coordinates and their connections
for row_idx in range(height):
    for col_idx in range(width):
        coord = (col_idx, row_idx)

        if data[row_idx][col_idx] == "S":
            source = coord
        elif data[row_idx][col_idx] == "|":
            connections.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx, row_idx + 1)])
        elif data[row_idx][col_idx] == "-":
            connections.setdefault(coord, []).extend([(col_idx - 1, row_idx), (col_idx + 1, row_idx)])
        elif data[row_idx][col_idx] == "L":
            connections.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx + 1, row_idx)])
        elif data[row_idx][col_idx] == "J":
            connections.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx - 1, row_idx)])
        elif data[row_idx][col_idx] == "7":
            connections.setdefault(coord, []).extend([(col_idx, row_idx + 1), (col_idx - 1, row_idx)])
        elif data[row_idx][col_idx] == "F":
            connections.setdefault(coord, []).extend([(col_idx, row_idx + 1), (col_idx + 1, row_idx)])
            
# Add the reverse connections
for coord in list(connections.keys()):
    if source in connections[coord]:
        connections.setdefault(source, []).extend([coord])

# Find the largest number of steps to get to a coordinate
max_steps = 0
visited = set()
queue = deque()
queue.append((source, 0))

while len(queue) > 0:
    coord, steps = queue.popleft()
    x, y = coord
    
    if coord in visited or (x < 0 or x >= width or y < 0 or y >= height):
        continue
    
    visited.add(coord)
    max_steps = max(max_steps, steps)

    for connection in connections[coord]:
        #if connection not in visited:
        queue.append((connection, steps + 1))


print('Part 1:', max_steps)
    

        