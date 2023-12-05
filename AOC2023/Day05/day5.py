file_content = open("input.txt", "r").read().strip().split('\n\n')

seeds, *maps = [chunks.split('\n') for chunks in file_content]

seeds = [int(s) for s in seeds[0].split()[1:] if s]

for map in maps:
    rows = sorted([[int(num) for num in line.split()] for line in map[1:]], key=lambda x: x[1])

    for i, s in enumerate(seeds):
        for start, offset, length in rows:
            if offset <= s < offset + length:
                seeds[i] += start - offset
                break

print(min(seeds))
