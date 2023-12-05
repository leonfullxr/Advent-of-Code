bag = {
    'red': 12,
    'green': 13,
    'blue': 14
}

with open('input.txt', 'r') as f:
    games = [line.strip() for line in f.readlines()]

games = [game.split(': ')[1] for game in games] # Erase Game XX:
games = [game.split('; ') for game in games] # Split a handful for each game 
games = [[handful.split(', ') for handful in game] for game in games] # Split cubes for each color

def is_game_possible(game) -> bool:
    for handful in game:
        for value in handful:
             parts = value.split()
             quantity, color = parts[0], parts[1]
             if color in bag and int(quantity) > bag[color]:
                return False
    return True


def min_number_of_cubes_for_game(game) -> int:
    max_blue, max_red, max_green = 0, 0, 0
    for handful in game:
        for value in handful:
            parts = value.split()
            quantity, color = parts[0], parts[1]
            if color =='red':
                if int(quantity) > max_red:
                    max_red = int(quantity)
            elif color == 'green':
                if int(quantity) > max_green:
                    max_green = int(quantity)
            elif color == 'blue':
                if int(quantity) > max_blue:
                    max_blue = int(quantity)
    return max_red * max_blue * max_green

def sum_possible_game_ids(games) -> {int, int}:
     total_sum_part1, total_sum_part2 = 0, 0
     game_id = 1
     for game in games:
        if is_game_possible(game):
            total_sum_part1 += game_id
        total_sum_part2 += min_number_of_cubes_for_game(game)
        game_id += 1
     return {total_sum_part1, total_sum_part2}

part2, part1 = sum_possible_game_ids(games)
print('Part 1: ' + str(part1))
print('Part 2: ' + str(part2))