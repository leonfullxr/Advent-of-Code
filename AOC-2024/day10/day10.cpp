#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::vector<char>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::vector<char>> data;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<char> row;
        char c;

        while (iss >> c) {
            row.push_back(c);
        }
        if (!row.empty()) {
            data.push_back(row);
        }
    }

    return data;
}

bool is_in_bounds(int row, int col, const std::vector<std::vector<char>>& data) {
    return row >= 0 && row < data.size() && col >= 0 && col < data[row].size();
}

int find_trails(const std::vector<std::vector<char>>& data, const int& row, const int& col) {
    int trails = 0;
    std::set<std::pair<int,int>> seen_peak;
    std::stack<std::pair<char, std::pair<int, int>>> path;
    std::set<std::pair<int,int>> seen_pos;
    std::vector<std::pair<int, int>> positions = {{-1,0},{0,1},{1,0},{0,-1}};

    path.push(std::make_pair(data[row][col],std::make_pair(row,col)));

    while(!path.empty()) {
        std::pair<char, std::pair<int, int>> actual_pos = path.top();
        seen_pos.insert(std::make_pair(actual_pos.second.first, actual_pos.second.second));
        //std::cout << "Posx: " << actual_pos.second.first << " Posy: " << actual_pos.second.second << std::endl;
        path.pop();

        if (actual_pos.first == '9') {
            if (auto search = seen_peak.find(std::make_pair(actual_pos.second.first, actual_pos.second.second)); search==seen_peak.end()) {
                seen_peak.insert(std::make_pair(actual_pos.second.first, actual_pos.second.second));
                trails++;
            }
        }

        for (const std::pair<int,int>& dir : positions) {
            int newx = actual_pos.second.first + dir.first;
            int newy = actual_pos.second.second + dir.second;
            if (is_in_bounds(newx, newy, data) and (data[newx][newy] - actual_pos.first == 1)) {
                if (auto start = seen_pos.find(std::make_pair(newx,newy)); start == seen_pos.end()) {
                    path.push(std::make_pair(data[newx][newy], std::make_pair(newx,newy)));
                }
            } else {
            }
        }
    }


    return trails;
}

int find_trails_distinct(const std::vector<std::vector<char>>& data, const int& row, const int& col) {
    int trails = 0;
    std::stack<std::pair<char, std::pair<int, int>>> path;
    std::set<std::pair<int,int>> seen_pos;
    std::vector<std::pair<int, int>> positions = {{-1,0},{0,1},{1,0},{0,-1}};

    path.push(std::make_pair(data[row][col],std::make_pair(row,col)));

    while(!path.empty()) {
        std::pair<char, std::pair<int, int>> actual_pos = path.top();
        //std::cout << "Posx: " << actual_pos.second.first << " Posy: " << actual_pos.second.second << std::endl;
        path.pop();

        if (actual_pos.first == '9') {
            trails++;
        } else {
            seen_pos.insert(std::make_pair(actual_pos.second.first, actual_pos.second.second));
        }

        for (const std::pair<int,int>& dir : positions) {
            int newx = actual_pos.second.first + dir.first;
            int newy = actual_pos.second.second + dir.second;
            if (is_in_bounds(newx, newy, data) and (data[newx][newy] - actual_pos.first == 1)) {
                if (auto start = seen_pos.find(std::make_pair(newx,newy)); start == seen_pos.end()) {
                    //path.push(std::make_pair(data[newx][newy], std::make_pair(newx,newy)));
                    trails += find_trails_distinct(data, newx, newy);
                }
            } else {
            }
        }
    }

    return trails;
}

int sum_trailheads(const std::vector<std::vector<char>>& data, bool part2) {
    int sum = 0;

    for (int row = 0; row < data.size(); row++) {
        for (int col = 0; col < data[row].size(); col++) {
            if (data[row][col] == '0') {
                if (!part2)
                    sum += find_trails(data, row, col);
                else
                    sum += find_trails_distinct(data, row, col);
            }
        }
    }

    return sum;
}

int main() {
    std::vector<std::vector<char>> data = parse_input("input.txt");

    int trailheads = sum_trailheads(data,false);
    int trailheads_distinct = sum_trailheads(data,true);

    std::cout << "Day10 solution part1: " << trailheads << std::endl;
    std::cout << "Day10 solution part2: " << trailheads_distinct << std::endl;

    return 0;
}
