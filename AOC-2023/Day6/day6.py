import re

data = open('input.txt', 'r').read().strip()

lines = data.split("\n")

times = [int(num) for num in re.findall(r"(\d+)", lines[0])]
distances = [int(num) for num in re.findall(r"(\d+)", lines[1])]

time_part2 = int(''.join(re.findall(r"(\d+)", lines[0])))
distance_part2 = int(''.join(re.findall(r"(\d+)", lines[1])))

def beat_record(time: int, distance: int) -> int:
    count = 0
    for speed in range(1, time):
        total = (time - speed) * speed

        if total > distance:
            count += 1

    return count

part1 = 1

for time, dist in zip(times, distances):
    count = beat_record(time, dist)
    part1 *= count

print('Part 1:', part1)
print('Part 2:', beat_record(time_part2, distance_part2))
