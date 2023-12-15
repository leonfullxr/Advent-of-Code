from typing import List, Tuple

def calculate_hash(s: str) -> int:
    v = 0
    for ch in s:
        v = (v + ord(ch)) * 17 % 256
    return v

def parse_part(part: str) -> Tuple[str, str, str]:
    label, operation, number = "", "", ""
    for ch in part:
        if ch in "-=":
            operation = ch
        elif ch.isdigit():
            number += ch
        else:
            label += ch
    return label, operation, number

def update_boxes(part: str, boxes: List[List[Tuple[str, str]]]) -> None:
    label, operation, number = parse_part(part)
    box_index = calculate_hash(label)
    box = boxes[box_index]

    if operation == "=":
        for i, (box_label, _) in enumerate(box):
            if label == box_label:
                box[i] = (label, number)
                break
        else:
            box.append((label, number))

    elif operation == "-" and box:
        box[:] = [(box_label, lens) for box_label, lens in box if box_label != label]

def calculate_total(boxes: List[List[Tuple[str, str]]]) -> int:
    total = 0
    for idx, box in enumerate(boxes):
        power = sum((1 + idx) * (box_idx + 1) * int(lens) for box_idx, (_, lens) in enumerate(box))
        total += power
    return total

def main() -> None:
    data = open("input.txt").read().strip().split(",")
    boxes = [[] for _ in range(256)]
    
    for part in data:
        update_boxes(part, boxes)
    
    print('Part 1:', sum(calculate_hash(part) for part in data))
    print('Part 2:', calculate_total(boxes))

if __name__ == "__main__":
    main()
