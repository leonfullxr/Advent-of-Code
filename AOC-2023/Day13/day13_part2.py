def count_differences(pattern1, pattern2):
    sum = 0
    for i in range(min((len(pattern1)), len(pattern2))):
         if pattern1[i] != pattern2[i]:
            sum += 1
    return sum

def find_reflection(pattern):
    width = len(pattern[0])
    length = len(pattern)

    # Vertical reflection
    for i in range(width - 1):
        size_on_each_side = min(i + 1, width - i - 1)
        differences = 0
        for j in range(size_on_each_side):
            matching_u_i = i - j
            real_lower_i = (i + 1) + j
            
            if matching_u_i < 0:
                break
            
            pattern1 = [pattern[k][matching_u_i] for k in range(length)]
            pattern2 = [pattern[k][real_lower_i] for k in range(length)]
            
            differences += count_differences(pattern1, pattern2)
            if differences > 1:
                break

        if differences == 1:
            return i + 1

    # Horizontal reflection
    for i in range(length - 1):
        size_on_each_side = min(i + 1, length - i - 1)
        differences = 0
        for j in range(size_on_each_side):
            matching_u_i = i - j
            real_lower_i = (i + 1) + j
            
            if matching_u_i < 0:
                break
            
            differences += count_differences(pattern[matching_u_i], pattern[real_lower_i])
            if differences > 1:
                break

        if differences == 1:
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

    # Process each pattern
    result = 0
    for pattern in patterns:
        result += find_reflection(pattern)
        print(pattern)
    print('Part 2', result)
    
if __name__ == "__main__":
    main()
    # 34889