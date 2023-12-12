def calculate_possible_combinations(springs_status, springs_damaged):
    # 3D dp on (idx in string, idx in set, length of current run)
    springs_damaged.append(0)
    max_run = max(springs_damaged)
    springs_status += "."
    
    n = len(springs_status)
    m = len(springs_damaged)
    dp = [[[None for _ in range(max_run+1)]
          for _ in range(m)] for _ in range(n)]

    for i in range(n):
        x = springs_status[i]
        for j in range(m):
            for current_run_length in range(springs_damaged[j]+1):
                # Base case
                if i == 0:
                    if j != 0:
                        dp[i][j][current_run_length] = 0
                        continue

                    if x == "#":
                        if current_run_length != 1:
                            dp[i][j][current_run_length] = 0
                            continue
                        dp[i][j][current_run_length] = 1
                        continue

                    if x == ".":
                        if current_run_length != 0:
                            dp[i][j][current_run_length] = 0
                            continue
                        dp[i][j][current_run_length] = 1
                        continue

                    if x == "?":
                        if current_run_length not in [0, 1]:
                            dp[i][j][current_run_length] = 0
                            continue
                        dp[i][j][current_run_length] = 1
                        continue

                # Process answer if current char is .
                if current_run_length != 0:
                    ans_dot = 0
                elif j > 0:
                    assert current_run_length == 0
                    ans_dot = dp[i-1][j-1][springs_damaged[j-1]]
                    ans_dot += dp[i-1][j][0]
                else:
                    # i>0, j=0, k=0.
                    # Only way to do this is if every ? is a .
                    ans_dot = 1 if springs_status[:i].count("#") == 0 else 0

                # Process answer if current char is #
                if current_run_length == 0:
                    ans_pound = 0
                else:
                    # Newest set
                    ans_pound = dp[i-1][j][current_run_length-1]

                if x == ".":
                    dp[i][j][current_run_length] = ans_dot
                elif x == "#":
                    dp[i][j][current_run_length] = ans_pound
                else:
                    dp[i][j][current_run_length] = ans_dot + ans_pound

    return dp[n-1][-1][0]

def main():
    data = open("input.txt").read().strip().split("\n")

    springs_status = []
    springs_damaged = []

    for line in data:
        whole_line = line.split(" ")
        springs_status.append("?".join([line.split(" ")[0]] * 5))
        springs_damaged.append(list(map(int, ",".join([line.split(" ")[1]]*5).split(","))))

    total_combinations = 0
    for index in range(len(springs_status)):
        total_combinations += calculate_possible_combinations(springs_status[index], springs_damaged[index])

    print('Part 2:', total_combinations)

if __name__ == "__main__":
    main()
