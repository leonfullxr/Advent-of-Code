def process_input():
    with open('input.txt', 'r') as f:
        parentheses = f.read()
    return parentheses

def calculate_floor(parentheses):
    floor = 0
    for paren in parentheses:
        if paren == '(':
            floor += 1
        elif paren == ')':
            floor -= 1
    return floor

def calculate_basement(parentheses):
    floor = 0
    for i, paren in enumerate(parentheses):
        if paren == '(':
            floor += 1
        elif paren == ')':
            floor -= 1
        if floor == -1:
            return i + 1

def main():
    parentheses = process_input()
    
    print('The floor is: {}'.format(calculate_floor(parentheses)))
    print('The basement is at: {}'.format(calculate_basement(parentheses)))

if __name__ == '__main__':
    main()