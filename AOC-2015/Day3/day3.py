def parse_inpput():
    directions = []
    with open('input.txt', 'r') as f:
        for line in f:
            for direction in line:
                directions.append(direction)
    return directions

def update_position(x, y, direction):
    if direction == "^":
        y += 1
    elif direction == 'v':
        y -= 1
    elif direction == '>':
        x += 1
    elif direction == "<":
        x -= 1
    return x, y

def calculate_houses(directions):
    x, y = 0, 0
    houses = {(x, y)}
    
    for direction in directions:
        x, y = update_position(x, y, direction)
        houses.add((x, y))
        
    return len(houses)

def calculate_houses_robo_santa(directions):
    x, y = 0, 0
    houses = {(x, y)}
    robot_x, robot_y = 0, 0
    
    for i, direction in enumerate(directions):
        if i % 2 == 0:
            x, y = update_position(x, y, direction)
            houses.add((x, y))
        else:
            robot_x, robot_y = update_position(robot_x, robot_y, direction)
            houses.add((robot_x, robot_y))
            
    return len(houses)

def main():
    directions = parse_inpput()

    print('The number of houses that receive at least one present is', calculate_houses(directions))
    
    print('Part 2: ', calculate_houses_robo_santa(directions))
    
if __name__ == '__main__':
    main()