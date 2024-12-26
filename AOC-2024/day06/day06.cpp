#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

std::vector<std::vector<char>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);

    if (!infile) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    std::vector<std::vector<char>> data;
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string token = iss.str();
        std::vector<char> row;
        int num;
        int pos = 0;

        while (token[pos]) {
            row.push_back(token[pos]);
            pos++;
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    return data;
}

bool is_in_bounds(const std::vector<std::vector<char>>& matrix, int row, int col) {
    return row > 0 && row < matrix.size()-1 && col > 0 && col < matrix[0].size()-1;
}

void update_position(std::pair<int, int>& position, const Direction direction) {
    switch (direction) {
        case Direction::UP:
            position.first--;
            break;
        case Direction::RIGHT:
            position.second++;
            break;
        case Direction::DOWN:
            position.first++;
            break;
        case Direction::LEFT:
            position.second--;
            break;
    }
}

int count_visited_area(std::vector<std::vector<char>>& matrix) {
    int count = 1;
    std::pair<int, int> position = {0, 0};
    Direction direction = Direction::UP;
    bool has_moved = true;

    // Update the position based on the matrix
    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix[row].size(); ++col) {
            if (matrix[row][col] == '^') {
                position.first = row;
                position.second = col;
                matrix[row][col] = '.';
            }
        }
    }

    while (is_in_bounds(matrix, position.first, position.second)) {
        //std::cout << "Current position: " << position.first << ", " << position.second << " count " << count << " max rows " << matrix.size() << " max cols " << matrix[0].size() << std::endl;
        has_moved = false;
        if (matrix[position.first][position.second] == '.') {
            matrix[position.first][position.second] = 'X';
            count++;
        }

        // Move to the next position
        switch (direction) {
            case Direction::UP:
                if (matrix[position.first - 1][position.second] != '#') {
                    update_position(position, direction);
                    has_moved = true;
                    break;
                }
                break;
            case Direction::RIGHT:
                if (matrix[position.first][position.second + 1] != '#') {
                    update_position(position, direction);
                    has_moved = true;
                    break;
                }
                break;
            case Direction::DOWN:
                if (matrix[position.first + 1][position.second] != '#') {
                    update_position(position, direction);
                    has_moved = true;
                    break;
                }
                break;
            case Direction::LEFT:
                if (matrix[position.first][position.second - 1] != '#') {
                    update_position(position, direction);
                    has_moved = true;
                    break;
                }
                break;
            default:
                has_moved = false;
                break;
        }
        if (!has_moved){ // If no movement is possible, rotate 90 degrees
            switch (direction) {
                case Direction::UP:
                    direction = Direction::RIGHT;
                    break;
                case Direction::RIGHT:
                    direction = Direction::DOWN;
                    break;
                case Direction::DOWN:
                    direction = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    direction = Direction::UP;
                    break;
            }
        }
    }

    return count;
}

int main() {
    const std::string filename = "input.txt";

    std::vector<std::vector<char>> data = parse_input(filename);

    // std::cout << "Parsed 2D array:" << std::endl;
    // std::cout << "Number of rows: " << data.size() << std::endl;
    // if (!data.empty()) {
    //     std::cout << "Number of columns: " << data[0].size() << std::endl;
    // }
    // for (const auto& row : data) {
    //    for (const auto& value : row) {
    //       std::cout << value << " ";
    //   }
    //  std::cout << std::endl;
    // }
    int visited_area = count_visited_area(data);

    std::cout << "Day06 solution: " << visited_area << std::endl;
    return 0;
}
