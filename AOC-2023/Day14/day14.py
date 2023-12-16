def tilt_forward(matrix):
    for row_idx, line in enumerate(matrix):
        for col_idx, value in enumerate(line):
            if value == "O":
                decreasing_row_idx = row_idx - 1
                while matrix[decreasing_row_idx][col_idx] == "." and decreasing_row_idx >= 0:
                    matrix[decreasing_row_idx][col_idx] = "O"
                    matrix[decreasing_row_idx+1][col_idx] = "."
                    decreasing_row_idx -= 1
                    
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

def main():
    data = [list(line) for line in open("input.txt").read().strip().split("\n")]
    
    tilt_forward(data)
            
    print('Part 1', get_score(data)) 

if __name__ == "__main__":
    main()