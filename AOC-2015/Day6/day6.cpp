#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void turn_lights(std::map<std::pair<int, int>, int> &lights, std::pair<int, int> initial_coords, 
              std::pair<int, int> final_coords, int light_status, bool brightness = false) {
    int range_x = final_coords.first - initial_coords.first;
    int range_y = final_coords.second - initial_coords.second;

    for (int i = 0; i <= range_x; i++) {
       for  (int j = 0; j <= range_y; j++) {
            if (!brightness)
                lights[std::make_pair(initial_coords.first + i, initial_coords.second + j)] = light_status;
            else 
                lights[std::make_pair(initial_coords.first + i, initial_coords.second + j)] += light_status;
       }
    }
}

void turn_lights_off(std::map<std::pair<int, int>, int> &lights, std::pair<int, int> initial_coords, 
              std::pair<int, int> final_coords, int light_status, bool brightness = false) {
    turn_lights(lights, initial_coords, final_coords, light_status);
}

void turn_lights_on(std::map<std::pair<int, int>, int> &lights, std::pair<int, int> initial_coords, 
              std::pair<int, int> final_coords, int light_status, bool brightness = false) {
    turn_lights(lights, initial_coords, final_coords, light_status);
}

void toggle_lights(std::map<std::pair<int, int>, int> &lights, std::pair<int, int> initial_coords, 
              std::pair<int, int> final_coords, int light_status, bool brightness = false) {
    int range_x = final_coords.first - initial_coords.first;
    int range_y = final_coords.second - initial_coords.second;

    for (int i = 0; i <= range_x; i++) {
       for  (int j = 0; j <= range_y; j++) {
            if (!brightness)
                lights[std::make_pair(initial_coords.first + i, initial_coords.second + j)] = !lights[std::make_pair(initial_coords.first + i, initial_coords.second + j)];
            else
                lights[std::make_pair(initial_coords.first + i, initial_coords.second + j)] += light_status;
       }
    }
}

int count_lights_on(std::map<std::pair<int, int>, int> &lights) {
    int count = 0;
    for (auto it = lights.begin(); it != lights.end(); it++) {
        if (it->second)
            count++;
    }
    return count;
}

long int count_lights_brightness(std::map<std::pair<int, int>, int> &lights) {
    long int count = 0;
    for (auto it = lights.begin(); it != lights.end(); it++) {
        count += it->second;
    }
    return count;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::pair<int, int> initial_coords, final_coords;
    std::pair<std::string, std::string> instruction;
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::pair<int, int>,std::pair<int, int>>>> instructions;

    std::map<std::pair<int, int>, int> lights;
    std::map<std::pair<int, int>, int> lights_brightness;

    while (std::getline(file, line)) {
        int index = 0;
        std::string word;
        std::string action;
        std::string x, y;

        while(line[index] != ',' and line[index]!=' ' and index < line.size()) {
            word += line[index];
            index++;
        }
        index++;

        instruction.first = word;
        instruction.second = "";

        if (word == "turn") {
            while (line[index] != ' ' and index < line.size()) {
                action += line[index];
                index++;
            }
            index++;
            instruction.second = action;
            

        } else if (word != "toggle") {
            std::cout << "Input error" << std::endl;
            return 1;
        }

        while(line[index] != ',' and line[index]!=' ' and index < line.size()) {
            x += line[index];
            index++;
        }
        index++;
        while(line[index] != ',' and line[index]!=' ' and index < line.size()) {
            y += line[index];
            index++;
        }
        index++;

        initial_coords.first = std::stoi(x);
        initial_coords.second = std::stoi(y);
        x = "";
        y = "";

        for (int i = 0; i < 8; i++) { // Skip "through"
            index++;
        }

        while(line[index] != ',' and line[index]!=' ' and index < line.size()) {
            x += line[index];
            index++;
        }
        index++;
        while(line[index] != ',' and line[index]!=' ' and index < line.size()) {
            y += line[index];
            index++;
        }
        index++;
        final_coords.first = std::stoi(x);
        final_coords.second = std::stoi(y);
        
        instructions.push_back(std::make_pair(instruction, std::make_pair(initial_coords, final_coords)));
    }

    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i].first.first == "turn") {
            if (instructions[i].first.second == "on") {
                turn_lights_on(lights, instructions[i].second.first, instructions[i].second.second, 1);
                turn_lights_on(lights_brightness, instructions[i].second.first, instructions[i].second.second, 1, true);
            } else {
                turn_lights_off(lights, instructions[i].second.first, instructions[i].second.second, 0);
                turn_lights_off(lights_brightness, instructions[i].second.first, instructions[i].second.second, -1, true);
            }
        } else {
            toggle_lights(lights, instructions[i].second.first, instructions[i].second.second, 0);
            toggle_lights(lights_brightness, instructions[i].second.first, instructions[i].second.second, 2, true);
        }
    }

    std::cout << "Lights on: " << count_lights_on(lights) << std::endl;
    std::cout << "Lights brightness: " << count_lights_brightness(lights_brightness) << std::endl;
}