def valid_order(springs_status, springs_damaged):
    size = len(springs_status)
    damaged = []
    
    i = 0
    while i < size:
        while i < size and not springs_status[i]:
            i += 1
        if i == size:
            break
        j = i
        c = 0
        while j < size and springs_status[j]:
            j += 1
            c += 1
        damaged.append(c)
        i = j
    return damaged == springs_damaged

def generate_combinations(springs_status, springs_damaged, index, current_combination, count):
    if index == len(springs_status):
        if valid_order(current_combination, springs_damaged):
            return count + 1
        return count

    if springs_status[index] == "?":
        # Try placing an operational spring
        count = generate_combinations(springs_status, springs_damaged, index + 1, current_combination + [0], count)
        # Try placing a broken spring
        count = generate_combinations(springs_status, springs_damaged, index + 1, current_combination + [1], count)
    else:
        # If the current position is known, keep it as it is
        count = generate_combinations(springs_status, springs_damaged, index + 1, current_combination + [int(springs_status[index] == "#")], count)

    return count

def calculate_different_orders(springs_status, springs_damaged):
    return generate_combinations(springs_status, springs_damaged, 0, [], 0)

def main():
    data = open("input.txt").read().strip().split("\n")
    springs_status = []
    springs_damaged = []

    for line in data:
        springs_status.append(line.split(" ")[0])
        springs_damaged.append(list(map(int, line.split(" ")[1].split(","))))

    total_combinations = 0
    for index in range(len(springs_status)):
        total_combinations += calculate_different_orders(springs_status[index], springs_damaged[index])

    print('Part 1:', total_combinations)

if __name__ == "__main__":
    main()
