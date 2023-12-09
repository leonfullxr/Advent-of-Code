import re

with open("input.txt") as fin:
    lines = fin.read().strip().split("\n")

raw_seeds = list(map(int, lines[0].split(" ")[1:]))
seeds = [
    (raw_seeds[i], raw_seeds[i+1])
    for i in range(0, len(raw_seeds), 2)
]

maps = []

index = 2
while index < len(lines):
    catA, _, catB = lines[index].split(" ")[0].split("-")
    maps.append([])

    index += 1
    while index < len(lines) and not lines[index] == "":
        dstStart, srcStart, rangeLen = map(int, lines[index].split())
        maps[-1].append((dstStart, srcStart, rangeLen))
        index += 1

    maps[-1].sort(key=lambda x: x[1])

    index += 1


# Ensure that all mappings are disjoint
for m in maps:
    for i in range(len(m)-1):
        if not m[i][1] + m[i][2] <= m[i+1][1]:
            print(m[i], m[i+1])


def remap(lo, hi, m):
    # Remap an interval (low,high) to a set of intervals m
    ans = []
    for dst, src, R in m:
        end = src + R - 1
        D = dst - src  # How much is this range shifted

        if not (end < lo or src > hi):
            ans.append((max(src, lo), min(end, hi), D))

    for i, interval in enumerate(ans):
        l, r, D = interval
        yield (l + D, r + D)

        if i < len(ans) - 1 and ans[i+1][0] > r + 1:
            yield (r + 1, ans[i+1][0] - 1)

    if len(ans) == 0:
        yield (lo, hi)
        return

    if ans[0][0] != lo:
        yield (lo, ans[0][0] - 1)
    if ans[-1][1] != hi:
        yield (ans[-1][1] + 1, hi)


locs = []

ans = 1 << 60

for start, R in seeds:
    cur_intervals = [(start, start + R - 1)]
    new_intervals = []

    for m in maps:
        for lo, hi in cur_intervals:
            for new_interval in remap(lo, hi, m):
                new_intervals.append(new_interval)

        cur_intervals, new_intervals = new_intervals, []

    for lo, hi in cur_intervals:
        ans = min(ans, lo)


print(ans)