def calculate_string_difference(line):
    line = line.strip()

    code_length = len(line)

    memory_length = 0
    index = 1 
    while index < len(line) - 1:
        char = line[index]
        if char == "\\":
            # Handle escape sequences
            if line[index + 1] == "\\" or line[index + 1] == "\"":
                # \\ or \"
                memory_length += 1
                index += 2
            elif line[index + 1] == "x":
                # \x followed by two hexadecimal characters
                memory_length += 1
                index += 4
            else:
                # Single backslash or other escape sequence
                memory_length += 1
                index += 2
        else: # Regular character
            memory_length += 1
            index += 1

    return code_length - memory_length

def encode_string(line):
    encoded_line = "\""

    for char in line:
        if char == "\\" or char == "\"":
            # Escape backslash and double quote
            encoded_line += "\\" + char
        elif char == "\n":
            # Skip newline characters
            continue
        else: # Regular character
            encoded_line += char

    # Add closing double quote
    encoded_line += "\""

    return encoded_line

def calculate_encoded_difference(line):
    line = line.strip()
    encoded_length = len(encode_string(line))

    return encoded_length - len(line)

def main():
    total_difference = 0
    with open("input.txt", "r") as file:
        for line in file:
            total_difference += calculate_string_difference(line)

    print("Total difference:", total_difference)

    total_encoded_difference = 0
    with open("input.txt", "r") as file:
        for line in file:
            total_encoded_difference += calculate_encoded_difference(line)

    print("Total encoded difference:", total_encoded_difference)

if __name__ == "__main__":
    main()
