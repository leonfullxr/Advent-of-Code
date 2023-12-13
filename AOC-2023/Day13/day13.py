def min(a, b):
    return a if a < b else b

def find_reflection(pattern):
    width = len(pattern[0])
    length = len(pattern)

    # Vertical reflection
    for i in range(width - 1):
        size_on_each_side = min(i + 1, width - i - 1)
        is_reflection = True
        for j in range(size_on_each_side):
            for k in range(length):
                if pattern[k][i - j] != pattern[k][i + j + 1]:
                    is_reflection = False
        if is_reflection:
            return i + 1

    # Horizontal reflection
    for i in range(length - 1):
        size_on_each_side = min(i + 1, length - i - 1)
        is_reflection = True
        for j in range(size_on_each_side):
            for k in range(width):
                if pattern[i - j][k] != pattern[i + j + 1][k]:
                    is_reflection = False
        if is_reflection:
            return (i + 1) * 100

    return 0

def main():
    data = open("input.txt").read().strip().split("\n")
    patterns = []
    current_pattern = []
    
    for line in data:
        if line.strip() == "":
            if current_pattern:
                patterns.append(current_pattern)
                current_pattern = []
        else:
            current_pattern.append(line)
    if current_pattern:
        patterns.append(current_pattern)
    
    result = 0
    for pattern in patterns:
        result += find_reflection(pattern)
        
    print('Part 1', result)
    
if __name__ == "__main__":
    main()