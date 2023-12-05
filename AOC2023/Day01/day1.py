def convert_line_to_digits(line, digit_words):
    first = None
    last = None
    for i, char in enumerate(line):
        if char.isdigit():
            if first is None:
                first = char
            last = char
        else:
            for word, digit in digit_words.items():
                if line.startswith(word, i):
                    if first is None:
                        first = digit
                    last = digit
    return int(first + last) if first is not None else 0

with open('input.txt', 'r') as f:
    lines = [line.strip() for line in f.readlines()]

digit_words = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9",
}

part1_total = sum([convert_line_to_digits(line, digit_words) for line in lines])

print(f'Part 1 : {part1_total}')

part2_total = sum([convert_line_to_digits(line, digit_words) for line in lines])

print(f'Part 2 : {part2_total}')
