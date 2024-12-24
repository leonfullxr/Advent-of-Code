#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

void parse_input(const std::string& filename, std::unordered_map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& updates) {
    std::ifstream infile(filename);
    std::string line;
    bool parsing_rules = true;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            parsing_rules = false;
            continue;
        }

        if (parsing_rules) {
            size_t pipe_pos = line.find('|');
            int x = std::stoi(line.substr(0, pipe_pos));
            int y = std::stoi(line.substr(pipe_pos + 1));
            rules[x].push_back(y);
        } else {
            std::istringstream iss(line);
            std::vector<int> update;
            std::string token;
            while (std::getline(iss, token, ',')) {
                update.push_back(std::stoi(token));
            }
            updates.push_back(update);
        }
    }
}

bool validate_update(const std::vector<int>& update, const std::unordered_map<int, std::vector<int>>& rules) {
    std::unordered_map<int, int> page_positions;
    for (size_t i = 0; i < update.size(); ++i) {
        page_positions[update[i]] = i;
    }

    for (const auto& [x, dependents] : rules) {
        if (page_positions.count(x)) { // Only check rules involving pages in the update
            for (int y : dependents) {
                if (page_positions.count(y)) {
                    if (page_positions[x] >= page_positions[y]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int get_middle_page(const std::vector<int>& update) {
    return update[update.size() / 2];
}

int main() {
    const std::string filename = "input.txt";

    std::unordered_map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> updates;

    parse_input(filename, rules, updates);

    int total_middle_sum = 0;

    for (const auto& update : updates) {
        if (validate_update(update, rules)) {
            total_middle_sum += get_middle_page(update);
        }
    }

    std::cout << "Total sum of middle pages: " << total_middle_sum << std::endl;

    return 0;
}
