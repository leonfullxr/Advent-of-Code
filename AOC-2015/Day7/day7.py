data = {}

for line in open("input.txt").readlines():
    cmd, key = line.split(" -> ")
    data[key.strip()] = cmd

memo = {}

def get_value(key):
    if key in memo:
        return memo[key]

    try:
        value = int(key)
    except ValueError:
        cmd = data[key].split(" ")

        if "NOT" in cmd:
            value = ~get_value(cmd[1])
        elif "AND" in cmd:
            value = get_value(cmd[0]) & get_value(cmd[2])
        elif "OR" in cmd:
            value = get_value(cmd[0]) | get_value(cmd[2])
        elif "LSHIFT" in cmd:
            value = get_value(cmd[0]) << get_value(cmd[2])
        elif "RSHIFT" in cmd:
            value = get_value(cmd[0]) >> get_value(cmd[2])
        else:
            value = get_value(cmd[0])

    memo[key] = value
    return value

print("The value of a is:", get_value("a"))
data["b"] = str(get_value("a"))

memo.clear()

print("The value of a in part 2 is:", get_value("a"))
