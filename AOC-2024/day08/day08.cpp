#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::vector<std::pair<char,bool>>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::vector<std::pair<char,bool>>> data;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::pair<char,bool>> row;
        char c;

        while (iss >> c) {
            row.push_back(std::make_pair(c, false));
        }
        if (!row.empty()) {
            data.push_back(row);
        }
    }

    return data;
}

void print_matrix(const std::vector<std::vector<std::pair<char,bool>>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& [c,c1] : row) {
            if (c != '.') {
                std::cout << c;
            } else {
                if (c1) {
                    std::cout << 'X';
                } else {
                    std::cout << '.';
                }
            }
        }
        std::cout << std::endl;
    }
}

bool is_in_bounds(int row, int col, const std::vector<std::vector<std::pair<char,bool>>>& data) {
    return row >= 0 && row < data.size() && col >= 0 && col < data[row].size();
}

int check_antinodes(std::vector<std::vector<std::pair<char,bool>>>& data, int row, int col, bool part2) {
    int count = 0;
    char word = data[row][col].first;

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j].first == word and (i != row or j != col)) {
                int row_diff = (row - i);
                int col_diff = (col - j);
                if (is_in_bounds(i-row_diff, j-col_diff, data) and !part2) {
                    if (!data[i-row_diff][j-col_diff].second) {
                        count++;
                        data[i-row_diff][j-col_diff].second = true;
                    }
                } else if (part2) {
                    int new_row = i+row_diff;
                    int new_col = j+col_diff;
                    while(is_in_bounds(new_row, new_col, data)) {
                        if (!data[new_row][new_col].second) {
                            count++;
                            data[new_row][new_col].second = true;
                        }
                        new_row += row_diff;
                        new_col += col_diff;
                    }
                }
            }
        }
    }

    return count;
}

int count_antinodes(std::vector<std::vector<std::pair<char,bool>>>& data, bool part2) {
   int count = 0;

   for (int row = 0; row < data.size(); row++) {
       for (int col = 0; col < data[row].size(); col++) {
           if (data[row][col].first != '.')
            count += check_antinodes(data, row, col, part2);
       }
   }

   return count;
}

int main() {
    std::vector<std::vector<std::pair<char,bool>>> data = parse_input("input.txt");

    int total_antinodes = count_antinodes(data, false);

    data = parse_input("input.txt");
    int total_antinodes_part2 = count_antinodes(data, true);

    //print_matrix(data);

    std::cout << "Day08 solution " << total_antinodes << std::endl;
    std::cout << "Day08 solution part2 " << total_antinodes_part2 << std::endl;

    return 0;
}
