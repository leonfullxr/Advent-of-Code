from collections import Counter

def get_score(item: tuple[str, int], use_modified_rule: bool = False) -> tuple[int, list[int]]:
    hand, bid = item

    if use_modified_rule:
        counts = sorted(list(Counter(hand.replace("J", "")).values()))

        if len(counts) > 0:
            counts[-1] += hand.count("J")
        else:
            counts.append(5)

        values = list(map("J23456789TJQKA".index, hand))
    else:
        #For example, if hand is the string "AAJJQK", the Counter(hand) would produce a Counter object like this: Counter({'A': 2, 'J': 2, 'Q': 1, 'K': 1}). The .values() part would extract the counts: dict_values([2, 2, 1, 1]). Finally, list(...) converts this view to a list, resulting in counts = [2, 2, 1, 1].
        counts = list(Counter(hand).values())
        if 5 in counts:
            type = 10
        elif 4 in counts:
            type = 9
        elif 3 in counts:
            type = 8 if 2 in counts else 7
        elif 2 in counts:
            type = 6 if counts.count(2) == 2 else 5
        else:
            type = 4
        #For example, if hand is the string "AJT987", the result would be values = [12, 10, 11, 7, 8, 9], which corresponds to the ranks of the cards "A J T 9 8 7" in the given order.
        values = list(map("23456789TJQKA".index, hand))

    return (type, values)

def get_total_score(hands: list(tuple[str, int])) -> int:
    total = 0
    
    for rank, (hand, bid) in enumerate(hands):
        total += bid * (rank + 1)

    return total


hands = []
data = open('input.txt', 'r').read().strip()
for line in data.split("\n"):
    hand, bid = line.split(" ")
    hands.append((hand, int(bid)))

hands = sorted(hands, key=get_score , reverse=False)
hands_part2 = sorted(hands, key=get_score, reverse=True)

print('Part 1:', get_total_score(hands))
print('Part 2:', get_total_score(hands_part2))

