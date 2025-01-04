#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

std::unordered_map<long int, std::vector<int>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::unordered_map<long int, std::vector<int>> data;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        long int num, key;

        iss >> key;
        iss.ignore(1);

        while (iss >> num) {
            row.push_back(num);
        }
        if (!row.empty()) {
            if (data.find(key) != data.end()) {
                std::cerr << "Error: Duplicate key " << key << std::endl;
                return data;
            }
            data[key] = row;
        }
    }

    return data;
}

bool evaluate_combination(const std::vector<char>& combination, const std::vector<int>& numbers, long int target) {
    long int result = numbers[0];
    for (size_t i = 0; i < combination.size(); ++i) {
        if (combination[i] == '+') {
            result += numbers[i + 1];
        } else if (combination[i] == '*') {
            result *= numbers[i + 1];
        } else if (combination[i] == '|') {
            std::string concatenated = std::to_string(result) + std::to_string(numbers[i + 1]);
            result = std::stol(concatenated);
        }
    }
    return result == target;
}

long int possible_combinations(const std::vector<int>& numbers, long int target, bool include_concatenation) {
    int num_operators = numbers.size() - 1;
    long int total_combinations = pow(include_concatenation ? 3 : 2, num_operators);

    for (long int i = 0; i < total_combinations; ++i) {
        std::vector<char> operators;
        long int temp = i;
        for (int j = 0; j < num_operators; ++j) {
            int op = temp % (include_concatenation ? 3 : 2);
            temp /= (include_concatenation ? 3 : 2);
            if (op == 0) {
                operators.push_back('+');
            } else if (op == 1) {
                operators.push_back('*');
            } else if (op == 2) {
                operators.push_back('|');
            }
        }

        if (evaluate_combination(operators, numbers, target)) {
            return target;
        }
    }

    return 0;
}

long long int total_calibrations(const std::unordered_map<long int, std::vector<int>>& data, bool include_concatenation) {
    long long int total = 0;

    for (const auto& [key, value] : data) {
        total += possible_combinations(value, key, include_concatenation);
    }

    return total;
}

int main() {
    std::unordered_map<long int, std::vector<int>> data = parse_input("input.txt");

    long long int total_part1 = total_calibrations(data, false);
    long long int total_part2 = total_calibrations(data, true);

    std::cout << "Day07 solution part 1: " << total_part1 << std::endl;
    std::cout << "Day07 solution part 2: " << total_part2 << std::endl;

    return 0;
}
