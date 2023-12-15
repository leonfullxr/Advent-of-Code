from typing import List

def hash(s: str) -> int:
    v = 0
    
    for ch in s:
        v += ord(ch)
        v *= 17
        v %= 256

    return v

def parse_part(part: str) -> tuple:
    label, operation, number = "", "", ""
    
    for ch in part:
        if ch == "-" or ch == "=":
            operation = ch
        elif ch.isdigit():
            number += ch
        else:
            label += ch
    
    return label, operation, number

def part2(part: str, boxes: List[List[tuple]]) -> None:
    label, operation, number = parse_part(part)
    box_index = hash(label)
    
    box = boxes[box_index]
    num_lens = 0

    for _label, _ in box:
        if label == _label:
            num_lens += 1
    
    if operation == "=":
        if num_lens > 0:
            for i in range(len(box)):
                if label == box[i][0]:
                    box[i] = (label, number)
        else:
            box.append((label, number))
    
    elif operation == "-":
        if len(box) == 0:
            return
        else:
            index = -1
            for i in range(len(box)):
                if label == box[i][0]:
                    index = i
                    break
            if index != -1:
                box.pop(index)
                    
    
def main() -> None:
    data = open("input.txt").read().strip().split(",")
    total = 0
    boxes = [[] for _ in range(256)]
    
    for part in data:
        total += hash(part)
        part2(part, boxes)
    
    print('Part 1:', total)
    
    total = 0
    for idx, box in enumerate(boxes):
        power = 0
        for box_idx, (_, lens) in enumerate(box):
            power += (1 + idx) * (box_idx + 1) * int(lens)

        total += power

    print('Part 2:', total)

if __name__ == "__main__":
    main()
