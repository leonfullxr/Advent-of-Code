def parse_input():
    presents = []
    with open('input.txt', 'r') as f:
        for line in f:
            length, width, height = line.split('x')
            presents.append((int(length), int(width), int(height)))
    return presents

def calculate_wrapping_paper(presents):
    total = 0
    for present in presents:
        length, width, height = present
        sides = [length*width, width*height, height*length]
        total += 2*sum(sides) + min(sides)
    return total

def calculate_ribbon(presents):
    total = 0
    for present in presents:
        length, width, height = present
        sides = [length, width, height]
        total += 2*sum(sorted(sides)[:2]) + length*width*height
    return total

def main():
    presents = parse_input()
    print('The square feet of wrapping paper is', calculate_wrapping_paper(presents))
    print('The feet of ribbon is', calculate_ribbon(presents))
    
if __name__ == '__main__':
    main()