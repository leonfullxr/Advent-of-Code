data = open("input.txt").read().strip().split("\n")

# Part 1
total_sum = 0

for line in data:
    initial_numbers = line.split(" ")
    
    for i in range(len(initial_numbers)):
        initial_numbers[i] = int(initial_numbers[i])
        
    additional_numbers = [initial_numbers]

    while additional_numbers[-1].count(0) != len(additional_numbers[-1]):
        new_numbers = []
        
        for index in range(len(additional_numbers[-1])-1):
            new_numbers.append(int(additional_numbers[-1][index+1]) - int(additional_numbers[-1][index]))
        additional_numbers.append(new_numbers)
    
    additional_numbers[-1].append(0)
    
    for index in range(len(additional_numbers)-2, -1, -1):
        additional_numbers[index].append(int(additional_numbers[index][-1]) + int(additional_numbers[index+1][-1]))
        
    total_sum += int(additional_numbers[0][-1])
    
print('Part 1:', total_sum)
        
# Part 2
# Now, instead of adding an element to the end of the list, insert it at the start
# This means that the last element of the list will be the first element of the list
# And the first element of the list will be the last element of the list
# This is a lot easier to work with
total_sum = 0

for line in data:
    initial_numbers = line.split(" ")
    
    for i in range(len(initial_numbers)):
        initial_numbers[i] = int(initial_numbers[i])
        
    additional_numbers = [initial_numbers]

    while additional_numbers[-1].count(0) != len(additional_numbers[-1]):
        new_numbers = []
        
        for index in range(len(additional_numbers[-1])-1):
            new_numbers.append(int(additional_numbers[-1][index+1]) - int(additional_numbers[-1][index]))
        additional_numbers.append(new_numbers)
    
    additional_numbers[-1].insert(0, 0)
    
    for index in range(len(additional_numbers)-2, -1, -1):
        additional_numbers[index].insert(0, int(additional_numbers[index][0]) - int(additional_numbers[index+1][0]))
        
    total_sum += int(additional_numbers[0][0])

print('Part 2:', total_sum)
    