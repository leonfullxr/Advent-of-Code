#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

std::unordered_map<long int, std::vector<int>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::unordered_map<long int, std::vector<int>> data;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) { // Read line by line
        std::istringstream iss(line);
        std::vector<int> row;
        long int num, key;

        // Find the key
        iss >> key;
        iss.ignore(1);

        while (iss >> num) { // Extract integers from the line
            row.push_back(num);
        }
        if (!row.empty()) { // Add non-empty rows to the data
            if (data.find(key) != data.end()) {
                std::cerr << "Error: Duplicate key " << key << std::endl;
                return data;
            }
            data[key] = row;
        }
    }

    return data;
}

bool evaluate_combination(const std::vector<char>& combination, const std::vector<int>& data, long int key) {
    long int sum = data[0];
    for (long int index = 0; index < combination.size(); index++) {
        if (combination[index] == '+') {
            sum += data[index+1];
        } else if (combination[index] == '*'){
            sum *= data[index+1];
        } else if (combination[index] == '|'){
            std::string number1 = std::to_string(sum);
            std::string number2 = std::to_string(data[index+1]);
            sum = std::stol(number1 + number2);
        } else {
            std::cerr << "Error: Invalid combination" << std::endl;
            return -1;
        }
    }
    return key == sum;
}

long int possible_combinations(std::vector<int> data, long int key) {
    long int total = 0;
    long int total_combinations = pow(3, data.size()-1);
    std::vector<std::vector<char>> combinations;

    for (long int combination_index = 0; combination_index < total_combinations; combination_index++) {
        std::vector<char> combination;
        long int temp = combination_index;
        for (int index = 0; index < data.size()-1; index++) {
            int op = temp % 3;
            temp /= 3;
            if (op % 3 == 0) {
                combination.push_back('+');
            } else if (op % 3 == 1){
                combination.push_back('*');
            } else if (op % 3 == 2){
                combination.push_back('|');
            }
        }
        if (evaluate_combination(combination, data, key)) return key;
    }

    return total;
}

long long int total_calibrations(std::unordered_map<long int, std::vector<int>> data) {
    long long int total = 0;

    for (const auto& [key, value] : data) {
        total += possible_combinations(value, key);
    }

    return total;
}

int main() {
    std::unordered_map<long int, std::vector<int>> data = parse_input("input.txt");

    long long int total = total_calibrations(data);
    std::cout << "Day07 solution part 1 " << total << std::endl;
    return 0;
}
