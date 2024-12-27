#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>

const std::vector<std::pair<int, int>> movement_directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::vector<std::vector<char>> load_grid(const std::string& filename, int& guard_row, int& guard_col) {
    std::ifstream input_file(filename);
    std::vector<std::vector<char>> grid;
    std::string line;

    if (!input_file) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    while (std::getline(input_file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);

        for (int col = 0; col < static_cast<int>(row.size()); ++col) {
            if (row[col] == '^') {
                guard_row = static_cast<int>(grid.size()) - 1;
                guard_col = col;
                row[col] = '.';
            }
        }
    }

    return grid;
}

std::set<std::pair<int, int>> track_patrol_path(const std::vector<std::vector<char>>& grid, int guard_row, int guard_col) {
    std::set<std::pair<int, int>> visited_positions;
    int row = guard_row, col = guard_col;
    int direction = 0;

    while (true) {
        visited_positions.insert({row, col});

        int next_row = row + movement_directions[direction].first;
        int next_col = col + movement_directions[direction].second;

        if (next_row < 0 || next_row >= static_cast<int>(grid.size()) || next_col < 0 || next_col >= static_cast<int>(grid[0].size())) {
            break;
        }

        if (grid[next_row][next_col] == '#') {
            direction = (direction + 1) % 4;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return visited_positions;
}

bool check_loop(std::vector<std::vector<char>>& grid, int guard_row, int guard_col, int obstacle_row, int obstacle_col) {
    if (grid[obstacle_row][obstacle_col] == '#') {
        return false;
    }

    grid[obstacle_row][obstacle_col] = '#';

    int row = guard_row, col = guard_col;
    int direction = 0;
    std::set<std::tuple<int, int, int>> guard_states;

    while (true) {
        if (guard_states.count({row, col, direction})) {
            grid[obstacle_row][obstacle_col] = '.';
            return true;
        }
        guard_states.insert({row, col, direction});

        int next_row = row + movement_directions[direction].first;
        int next_col = col + movement_directions[direction].second;

        if (next_row < 0 || next_row >= static_cast<int>(grid.size()) || next_col < 0 || next_col >= static_cast<int>(grid[0].size())) {
            grid[obstacle_row][obstacle_col] = '.';
            return false;
        }

        if (grid[next_row][next_col] == '#') {
            direction = (direction + 1) % 4;
        } else {
            row = next_row;
            col = next_col;
        }
    }
}

int count_valid_obstruction_positions(std::vector<std::vector<char>>& grid, const std::set<std::pair<int, int>>& patrol_path, int guard_row, int guard_col) {
    int valid_obstructions = 0;

    for (const auto& [row, col] : patrol_path) {
        if (row == guard_row && col == guard_col) {
            continue;
        }

        if (check_loop(grid, guard_row, guard_col, row, col)) {
            valid_obstructions++;
        }
    }

    return valid_obstructions;
}

int main() {
    const std::string input_filename = "input.txt";

    int guard_row = 0, guard_col = 0;
    std::vector<std::vector<char>> grid = load_grid(input_filename, guard_row, guard_col);

    std::set<std::pair<int, int>> patrol_path = track_patrol_path(grid, guard_row, guard_col);

    int valid_obstructions = count_valid_obstruction_positions(grid, patrol_path, guard_row, guard_col);

    std::cout << "Day06 Part 2 solution: " << valid_obstructions << " valid obstruction positions" << std::endl;

    return 0;
}
