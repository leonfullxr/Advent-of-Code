def tilt_forward(data):
    matrix = [row[:] for row in data]
    
    for row_idx, line in enumerate(matrix):
        for col_idx, value in enumerate(line):
            if value == "O":
                decreasing_row_idx = row_idx - 1
                while matrix[decreasing_row_idx][col_idx] == "." and decreasing_row_idx >= 0:
                    matrix[decreasing_row_idx][col_idx] = "O"
                    matrix[decreasing_row_idx+1][col_idx] = "."
                    decreasing_row_idx -= 1
    return matrix
                    
def get_score(matrix):
    length = len(matrix)
    mult = length
    sum = 0
    for line in matrix:
        for value in line:
            if value == "O":
                sum += mult
        mult -= 1
    return sum

# Numpy doesnt work, so i had to implement my own functions
def rotate_left(matrix):
    return [list(reversed(col)) for col in zip(*matrix)]

def cycle(matrix):
    for i in range(4):
        matrix = tilt_forward(matrix)
        matrix = rotate_left(matrix)    

    return matrix

def main():
    data = [list(line) for line in open("input.txt").read().strip().split("\n")]
    
    matrix = tilt_forward(data)
    print('Part 1', get_score(matrix)) 
    
    # Part 2
    matrix = data
    goal = 1000000000
    iterations = 0
    cache = {tuple(map(tuple, matrix))}
    combinations = [matrix]

    while True:
        iterations += 1
        matrix = cycle(matrix)
        matrix_tuple = tuple(map(tuple, matrix))
        if matrix_tuple in cache:
            break
        cache.add(matrix_tuple)
        combinations.append(matrix)
    
    initial_cycles = combinations.index(matrix)
    cycle_length = iterations - initial_cycles
    index = (goal - initial_cycles) % cycle_length + initial_cycles
    matrix = combinations[index]
        
    print('Part 2', get_score(matrix))
    
if __name__ == "__main__":
    main()
