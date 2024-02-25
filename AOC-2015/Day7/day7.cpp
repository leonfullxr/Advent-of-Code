#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

bool is_number(const std::string &n) {
    return std::all_of(n.begin(), n.end(), ::isdigit);
}

std::vector<std::string> processInput(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> input;
    std::string line;

    while (std::getline(file, line)) {
        input.push_back(line);
    }
    return input;
}

void calculateValue(std::string part1, std::string part2, std::string final_part, std::string operation, std::map<std::string, uint16_t> &parts) {
    if (operation == "AND") {
        parts[final_part] = parts[part1] & parts[part2];
    } else if (operation == "OR") {
        parts[final_part] = parts[part1] | parts[part2];
    } else if (operation == "LSHIFT") {
        parts[final_part] = parts[part1] << parts[part2];
    } else if (operation == "RSHIFT") {
        parts[final_part] = parts[part1] >> parts[part2];
    } else if (operation == "NOT") {
        parts[final_part] = ~parts[part1];
    } else {
        parts[final_part] = parts[part1];
    }
}
    
std::map<std::string, uint16_t> connectParts(std::vector<std::string> input) {
    std::map<std::string, uint16_t> parts;

    for (std::string line : input) {
        std::string part1;
        std::string part2;
        std::string operation;
        std::string destination;
        int index = 0;

        while (index < line.size() and line[index] != ' ') {
            part1 += line[index];
            index++;
        }
        index++;

        if (is_number(part1)) {
            parts[part1] = std::stoi(part1);
        } else if (part1 == "NOT") {
            while (index < line.size() and line[index] != ' ') {
                part2 += line[index];
                index++;
            }
            index++;
            while (index < line.size() and (line[index] == ' ' or line[index] == '>' or line[index] == '-')) {
                index++;
            }
            while (index < line.size() and line[index] != ' ') {
                destination += line[index];
                index++;
            }
            parts[destination] = ~parts[part2];
            continue;
        }
        
        while (index < line.size() and line[index] != ' ') {
            operation += line[index];
            index++;
        }
        index++;

        if (operation == "->") {
            while (index < line.size() and line[index] != ' ') {
                destination += line[index];
                index++;
            }
            index++;
            parts[destination] = parts[part1];
            continue;
        }

        while (index < line.size() and line[index] != ' ') {
            part2 += line[index];
            index++;
        }
        index++;

        if (is_number(part2)) {
            parts[part2] = std::stoi(part2);
        }

        while (index < line.size() and (line[index] == ' ' or line[index] == '>' or line[index] == '-')) {
            index++;
        }  

        while (index < line.size() and line[index] != ' ') {
            destination += line[index];
            index++;
        }
        index++;

        calculateValue(part1, part2, destination, operation, parts);
    }
    return parts;
}

int main() {
    std::vector<std::string> input = processInput("input.txt");
    std::map<std::string, uint16_t> parts = connectParts(input);

    std::cout << "The value of wire a is: " <<  parts["a"] << std::endl;

    return 0;
}