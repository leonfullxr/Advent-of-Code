def parse_input():
    data = open("input.txt").read().split("\n\n")    
    workflow_input, parts_input  = data[0].split("\n"), data[1].split("\n")
    
    parts = []
    rules = []
    workflow = {}
    parts_cleaned = []
    
    for line in parts_input:
        parts_cleaned.append(line[1:-1])
    for line in parts_cleaned:
        x, m, a, s = line.split(",")
        parts.append([int(x[2:]), int(m[2:]), int(a[2:]), int(s[2:])])
   
    for line in workflow_input:
        line = line[:-1]
        name, rules = line.split("{")
        rules = rules.split(",")
        workflow[name] = ([], rules.pop())
        for rule in rules:
            comparison, target = rule.split(":")
            key = comparison[0]
            comparator = comparison[1]
            number = int(comparison[2:])
            workflow[name][0].append((key, comparator, number, target))
    return workflow, parts

def accept_item(item, name = "in", workflow = {}):
    if name == "R":
        return False
    if name == "A":
        return True
    
    rules, rec = workflow[name]
    
    for key, comparator, number, target in rules:
        value = None
        if key == "x":
            value = item[0]
        elif key == "m":
            value = item[1]
        elif key == "a":
            value = item[2]
        elif key == "s":
            value = item[3]
        if comparator == "<":
            if value < number:
                return accept_item(item, target, workflow)
        elif comparator == ">":
            if value > number:
                return accept_item(item, target, workflow)
    
    return accept_item(item, rec, workflow)

def main():
    workflow, parts = parse_input()
    
    total = 0
    for item in parts:
        if accept_item(item, "in", workflow):
            total += sum(item)
            
    print(total)
    
if __name__ == '__main__':
    main()