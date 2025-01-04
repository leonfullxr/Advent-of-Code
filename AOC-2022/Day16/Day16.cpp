#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

struct Valve {
    int id;
    int flowRate;
    std::vector<std::string> connectedValves;
};

std::map<std::string, Valve> parse_input(const std::string& input) {
    std::map<std::string, Valve> valves;
    std::regex lineRegex(R"(Valve ([A-Z]+) has flow rate=(\d+); tunnels lead to valves ([A-Z]+(?:, [A-Z]+)*))");
    std::regex nameRegex(R"([A-Z]+)");
    std::istringstream inputStream(input);
    std::string line;
    int nextId = 0;

    while (std::getline(inputStream, line)) {
        std::smatch match;
        if (std::regex_match(line, match, lineRegex)) {
            std::string name = match[1];
            int flowRate = std::stoi(match[2]);
            Valve v;
            v.id = nextId++;
            v.flowRate = flowRate;

            std::string links = match[3];
            std::smatch subMatch;
            while (std::regex_search(links, subMatch, nameRegex)) {
                v.connectedValves.push_back(subMatch.str());
                links = subMatch.suffix();
            }

            valves[name] = v;
        }
    }

    return valves;
}

int main() {
    std::map<std::string, Valve> valveMap;
    valveMap = parse_input("input.txt");

    // Output for testing
    for (const auto& pair : valveMap) {
        std::cout << "Valve " << pair.first << " has flow rate " << pair.second.flowRate << "; connected to: ";
        for (const auto& connectedValve : pair.second.connectedValves) {
            std::cout << connectedValve << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Done!";

    return 0;
}
