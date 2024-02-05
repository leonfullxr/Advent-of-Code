def parse_input():
    strings = []
    with open('input.txt', 'r') as f:
        for line in f:
            strings.append(line.strip())
    return strings

def find_nice_strings(strings):
    nice_strings = 0

    vowels = ['a', 'e', 'i', 'o', 'u']
    bad_strings = ['ab', 'cd', 'pq', 'xy']
    
    for string in strings:
        vowel_count = 0
        double_letter = False
        bad_string = False
        for i in range(len(string)):
            if string[i] in vowels:
                vowel_count += 1
            if i < len(string) - 1 and string[i] == string[i+1]:
                double_letter = True
            if i < len(string) - 1 and string[i:i+2] in bad_strings:
                bad_string = True
        if vowel_count >= 3 and double_letter and not bad_string:
            nice_strings += 1
            
    return nice_strings

def find_nice_strings_v2(strings):
    nice_strings = 0
    
    for string in strings:
        double_pair = False
        repeat_with_middle = False
        for i in range(len(string) - 1):
            if string[i:i+2] in string[i+2:]:
                double_pair = True
            if i < len(string) - 2 and string[i] == string[i+2]:
                repeat_with_middle = True
        if double_pair and repeat_with_middle:
            nice_strings += 1
            
    return nice_strings

def main():
    strings = parse_input()
    print('The number of nice strings is', find_nice_strings(strings))
    print('Part 2: ', find_nice_strings_v2(strings))
    
if __name__ == '__main__':
    main()