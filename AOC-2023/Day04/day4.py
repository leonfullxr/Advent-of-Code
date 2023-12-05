engine_schematic = open("input.txt", "r").read().split("\n")

total_score = 0
card_index = -1
cards = [1] * len(engine_schematic)

for card in engine_schematic:
    card_index += 1
    wins = 0

    winning_elements = card.replace("  "," ").split("|")[0].split(":")[1].strip().split(" ")

    player_elements = card.split("|")[1].strip().split(" ")

    for number in player_elements:
        if number in winning_elements:
            wins += 1
            
    for _ in range(cards[card_index]):
        for i in range(1, wins + 1):
            if card_index + i < len(cards):
                cards[card_index + i] += 1

    points = 2**(wins-1)

    if points < 1:
        points = 0

    total_score += points

total_cards = sum(cards)
print('Part 1 :', total_score)
print('Part 2 :', total_cards)