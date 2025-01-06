#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>

std::unordered_map<long long, long long> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::unordered_map<long long, long long> stone_counts;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return stone_counts;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        long long stone;
        while (iss >> stone) {
            stone_counts[stone]++;
        }
    }

    return stone_counts;
}

std::pair<long long, long long> split_number(long long number) {
    std::string num_str = std::to_string(number);
    int mid = num_str.size() / 2;

    long long left = std::stoll(num_str.substr(0, mid));
    long long right = std::stoll(num_str.substr(mid));

    return {left, right};
}

long long count_stones(const std::unordered_map<long long, long long>& initial_stones, int blinks) {
    std::unordered_map<long long, long long> current_stones = initial_stones;

    for (int blink = 0; blink < blinks; ++blink) {
        std::unordered_map<long long, long long> next_stones;

        for (const auto& [stone, count] : current_stones) {
            if (stone == 0) {
                next_stones[1] += count;
            } else if (std::to_string(stone).size() % 2 == 0) {
                auto [left_half, right_half] = split_number(stone);
                next_stones[left_half] += count;
                next_stones[right_half] += count;
            } else {
                next_stones[stone * 2024LL] += count;
            }
        }

        current_stones = next_stones;
    }

    long long total_stones = 0;
    for (const auto& [stone, count] : current_stones) {
        total_stones += count;
    }

    return total_stones;
}

int main() {
    std::unordered_map<long long, long long> stone_counts = parse_input("input.txt");

    long long total_stones_25 = count_stones(stone_counts, 25);
    long long total_stones_75 = count_stones(stone_counts, 75);

    std::cout << "Day11 solution for 25 blinks: " << total_stones_25 << std::endl;
    std::cout << "Day11 solution for 40 blinks: " << total_stones_75 << std::endl;

    return 0;
}
