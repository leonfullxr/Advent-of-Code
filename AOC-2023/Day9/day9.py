def process_numbers(initial_numbers, is_part_1):
    additional_numbers = [initial_numbers]

    while additional_numbers[-1].count(0) != len(additional_numbers[-1]):
        new_numbers = [int(additional_numbers[-1][i + 1]) - int(additional_numbers[-1][i]) for i in range(len(additional_numbers[-1]) - 1)]
        additional_numbers.append(new_numbers)

    if is_part_1:
        additional_numbers[-1].append(0)
        for index in range(len(additional_numbers) - 2, -1, -1):
            additional_numbers[index].append(int(additional_numbers[index][-1]) + int(additional_numbers[index + 1][-1]))
        return int(additional_numbers[0][-1])
    else:
        additional_numbers[-1].insert(0, 0)
        for index in range(len(additional_numbers) - 2, -1, -1):
            additional_numbers[index].insert(0, int(additional_numbers[index][0]) - int(additional_numbers[index + 1][0]))
        return int(additional_numbers[0][0])


def main():
    data = open("input.txt").read().strip().split("\n")

    # Part 1
    total_sum_part_1 = 0

    for line in data:
        initial_numbers = [int(num) for num in line.split(" ")]
        total_sum_part_1 += process_numbers(initial_numbers, True)

    print('Part 1:', total_sum_part_1)

    # Part 2
    total_sum_part_2 = 0

    for line in data:
        initial_numbers = [int(num) for num in line.split(" ")]
        total_sum_part_2 += process_numbers(initial_numbers, False)

    print('Part 2:', total_sum_part_2)


if __name__ == "__main__":
    main()
