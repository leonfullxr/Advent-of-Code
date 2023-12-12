from itertools import product

data = open("input.txt").read().strip().split("\n")

springs_status = []
springs_damaged = []

for line in data:
    springs_status.append(line.split(" ")[0])
    springs_damaged.append(list(map(int, line.split(" ")[1].split(","))))
    
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

def calculate_different_orders(springs_status, springs_damaged):
    springs_status_int = []
    unknown_springs = []
    
    for index, value in enumerate(springs_status):
        if value == ".":
            springs_status_int.append(0)
        if value == "#":
            springs_status_int.append(1)
        if value == "?":
            springs_status_int.append(-1)
            unknown_springs.append(index)

    count = 0
    for combinations in product([0, 1], repeat=len(unknown_springs)):
        possible_combination = springs_status_int.copy()
        for i, bit in zip(unknown_springs, combinations):
            possible_combination[i] = bit

        if valid_order(possible_combination, springs_damaged):
            count += 1

    return count

total_combinations = 0
for index in range(len(springs_status)):
    total_combinations += calculate_different_orders(springs_status[index], springs_damaged[index])
    
print('Part 1:', total_combinations)
