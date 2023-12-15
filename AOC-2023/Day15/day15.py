def hash(s):
    v = 0
    
    for ch in s:
        v += ord(ch)
        v *= 17
        v %= 256

    return v

def main():
    data = open("input.txt").read().strip().split(",")
    total = 0
    for part in data:
        total += hash(part)
    print(total)

if __name__ == "__main__":
    main()