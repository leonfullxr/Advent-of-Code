import re

data = open('input.txt', 'r').read().strip()

lines = data.split("\n")

times = [int(num) for num in re.findall(r"(\d+)", lines[0])]
distances = [int(num) for num in re.findall(r"(\d+)", lines[1])]

out = 1

for time, dist in zip(times, distances):
    count = 0
    for speed in range(1, time):
        total = (time - speed) * speed

        if total > dist:
            count += 1

    out *= count

print(out)
