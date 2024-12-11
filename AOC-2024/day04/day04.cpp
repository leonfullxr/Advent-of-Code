#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
    return row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size();
}

bool search_word(const std::vector<std::vector<char>>& matrix, int start_row, int start_col, int delta_row, int delta_col, const std::string& word) {
    for (size_t i = 0; i < word.size(); ++i) {
        int new_row = start_row + i * delta_row;
        int new_col = start_col + i * delta_col;

        if (!is_in_bounds(matrix, new_row, new_col) || matrix[new_row][new_col] != word[i]) {
            return false;
        }
    }
    return true;
}

bool is_xmas_pattern(const std::vector<std::vector<char>>& matrix, int row, int col) {
    // Check bounds for the X-MAS pattern
    if (!is_in_bounds(matrix, row - 1, col - 1) || // Top-left
        !is_in_bounds(matrix, row - 1, col + 1) || // Top-right
        !is_in_bounds(matrix, row, col) ||        // Center
        !is_in_bounds(matrix, row + 1, col - 1) || // Bottom-left
        !is_in_bounds(matrix, row + 1, col + 1)) { // Bottom-right
        return false;
    }

    // Check for the X-MAS structure
    char top_left = matrix[row - 1][col - 1];
    char top_right = matrix[row - 1][col + 1];
    char center = matrix[row][col];
    char bottom_left = matrix[row + 1][col - 1];
    char bottom_right = matrix[row + 1][col + 1];

    // Check if it matches the X-MAS pattern
    return ((top_left == 'M' && top_right == 'S' && center == 'A' && bottom_left == 'M' && bottom_right == 'S') ||
            (top_left == 'S' && top_right == 'M' && center == 'A' && bottom_left == 'S' && bottom_right == 'M') ||
            (top_left == 'M' && top_right == 'M' && center == 'A' && bottom_left == 'S' && bottom_right == 'S') ||
            (top_left == 'S' && top_right == 'S' && center == 'A' && bottom_left == 'M' && bottom_right == 'M'));
}

int count_xmas(const std::vector<std::vector<char>>& matrix) {
    const std::string word = "XMAS";
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Right
        {1, 0},   // Down
        {1, 1},   // Diagonal Down-Right
        {1, -1},  // Diagonal Down-Left
        {0, -1},  // Left
        {-1, 0},  // Up
        {-1, -1}, // Diagonal Up-Left
        {-1, 1}   // Diagonal Up-Right
    };

    int count = 0;

    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix[row].size(); ++col) {
            for (const auto& [delta_row, delta_col] : directions) {
                if (search_word(matrix, row, col, delta_row, delta_col, word)) {
                    ++count;
                }
            }
        }
    }

    return count;
}

int count_xmas_part2(const std::vector<std::vector<char>>& matrix) {
    int count = 0;

    for (size_t row = 1; row < matrix.size() - 1; ++row) {
        for (size_t col = 1; col < matrix[row].size() - 1; ++col) {
            if (is_xmas_pattern(matrix, row, col)) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    const std::string filename = "input.txt";

    std::vector<std::vector<char>> data = parse_input(filename);

    // std::cout << "Parsed 2D array:" << std::endl;
    // for (const auto& row : data) {
    //     for (const auto& value : row) {
    //         std::cout << value << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Output dimensions
    std::cout << "Number of rows: " << data.size() << std::endl;
    if (!data.empty()) {
        std::cout << "Number of columns (in first row): " << data[0].size() << std::endl;
    }

    int total_xmas = count_xmas(data);
    std::cout << "Total occurrences of 'XMAS': " << total_xmas << std::endl;
    std::cout << "Total occurrences of 'XMAS' part 2: " << count_xmas_part2(data) << std::endl;

    return 0;
}
