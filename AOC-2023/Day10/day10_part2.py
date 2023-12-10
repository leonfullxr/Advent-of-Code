from collections import deque

data = open('input.txt', 'r').read().strip().split('\n')

width = len(data[0])
height = len(data)
connections_dict = {}
grid_lines = data

# Create a dictionary with all the coordinates and their connections
for row_idx in range(height):
    for col_idx in range(width):
        coord = (col_idx, row_idx)

        if data[row_idx][col_idx] == "S":
            start_point = coord
        elif data[row_idx][col_idx] == "|":
            connections_dict.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx, row_idx + 1)])
        elif data[row_idx][col_idx] == "-":
            connections_dict.setdefault(coord, []).extend([(col_idx - 1, row_idx), (col_idx + 1, row_idx)])
        elif data[row_idx][col_idx] == "L":
            connections_dict.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx + 1, row_idx)])
        elif data[row_idx][col_idx] == "J":
            connections_dict.setdefault(coord, []).extend([(col_idx, row_idx - 1), (col_idx - 1, row_idx)])
        elif data[row_idx][col_idx] == "7":
            connections_dict.setdefault(coord, []).extend([(col_idx, row_idx + 1), (col_idx - 1, row_idx)])
        elif data[row_idx][col_idx] == "F":
            connections_dict.setdefault(coord, []).extend([(col_idx, row_idx + 1), (col_idx + 1, row_idx)])

# Add the reverse connections
for coord in list(connections_dict.keys()):
    if start_point in connections_dict[coord]:
        connections_dict.setdefault(start_point, []).extend([coord])

distances = {start_point: 0}
states_queue = deque([(start_point, 0)])

while states_queue:
    state = states_queue.popleft()
    for neighbor in connections_dict[state[0]]:
        if state[0] not in connections_dict[neighbor]:
            continue
        if neighbor in distances:
            continue
        new_state = (neighbor, state[1] + 1)
        distances[neighbor] = new_state[1]
        states_queue.append(new_state)

    states_queue = deque(sorted(states_queue, key=lambda s: s[1]))

# Make a 3x3 tile for each source tile, representing the shape of the pipes
pipes = set()
all_points = set()
for y, line in enumerate(grid_lines):
    for x, cell in enumerate(line):
        xx = x * 3 + 1
        yy = y * 3 + 1
        for dy in [-1, 0, 1]:
            for dx in [-1, 0, 1]:
                all_points.add((xx + dx, yy + dy))
        if (x, y) in distances and len(connections_dict[(x, y)]) > 0:
            pipes.add((xx, yy))
            for cx, cy in connections_dict[(x, y)]:
                cxx = (cx - x) + xx
                cyy = (cy - y) + yy
                pipes.add((cxx, cyy))

unreached_points = all_points - pipes
zones = []

while unreached_points:
    zone = set()
    active_points = {unreached_points.pop()}
    while active_points:
        x, y = active_points.pop()
        zone.add((x, y))
        if (x-1, y) in unreached_points:
            active_points.add((x-1, y))
            unreached_points.remove((x-1, y))
        if (x+1, y) in unreached_points:
            active_points.add((x+1, y))
            unreached_points.remove((x+1, y))
        if (x, y-1) in unreached_points:
            active_points.add((x, y-1))
            unreached_points.remove((x, y-1))
        if (x, y+1) in unreached_points:
            active_points.add((x, y+1))
            unreached_points.remove((x, y+1))

    zones.append(zone)

# Pipes that are not part of the loop count as being inside the loop.
zone_id = {}
zone_size = {}
for i, zone in enumerate(zones):
    zone_size[i] = 0
    for x, y in zone:
        zone_id[(x, y)] = i
        if (x - 1) % 3 == 0 and (y - 1) % 3 == 0:
            zone_size[i] += 1

print(zone_size)
