#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

int sum_valid_muls(const std::string& filename) {
    std::ifstream infile(filename);
    int total_sum = 0;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return total_sum;
    }

    // Regex to match valid `mul(X,Y)` instructions
    std::regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");

    std::string line;
    while (std::getline(infile, line)) { // Read line by line
        std::istringstream iss(line);

        // Create a regex iterator to find all matches
        std::sregex_iterator it(line.begin(), line.end(), mul_regex);
        std::sregex_iterator end;
        while (it != end) {
            std::smatch match = *it;

            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());

            total_sum += x * y;

            ++it;
        }
    }

    return total_sum;
}

int sum_valid_muls2(const std::string& filename) {
    std::ifstream infile(filename);
    int total_sum = 0;
    bool mul_enabled = true; // Multiplications start as enabled

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return total_sum;
    }

    // Combined regex to match `do()`, `don't()`, and valid `mul(X,Y)` instructions
    std::regex instruction_regex(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

    std::string line;
    while (std::getline(infile, line)) { // Read line by line
        auto it = line.begin();

        while (it != line.end()) {
            std::smatch match;

            // Search for the next instruction
            std::string remaining(line.substr(std::distance(line.begin(), it)));
            if (std::regex_search(remaining, match, instruction_regex)) {
                // Determine the type of instruction
                if (match[0].str() == "do()") {
                    mul_enabled = true; // Enable mul instructions
                } else if (match[0].str() == "don't()") {
                    mul_enabled = false; // Disable mul instructions
                } else if (match[1].matched && match[2].matched) { // Valid `mul(X,Y)` instruction
                    if (mul_enabled) {
                        // Extract and process the valid `mul(X,Y)` instruction
                        int x = std::stoi(match[1].str());
                        int y = std::stoi(match[2].str());
                        total_sum += x * y;
                    }
                }

                // Advance iterator to the position after the current match
                it += match.position() + match.length();
            } else {
                break; // No more matches on this line
            }
        }
    }

    return total_sum;
}

int main() {
    std::string filename = "input.txt";

    int result = sum_valid_muls(filename);

    std::cout << "Day03 solution" << std::endl;
    std::cout << "Sum of valid mul instructions: " << result << std::endl;
    std::cout << "Sum of valid mul instructions part 2: " << sum_valid_muls2(filename) << std::endl;

    return 0;
}
