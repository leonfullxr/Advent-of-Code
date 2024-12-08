#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <climits>
#include <cmath>
#include <algorithm>

std::vector<std::pair<int, int>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::pair<int, int>> data;
    
    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    int col1, col2;
    while (infile >> col1 >> col2) {
        data.emplace_back(col1, col2);
    }
    return data;
}

long long int calculate_distances(const std::vector<std::pair<int, int>>& data) {
    long long int distance_sum = 0;
    
    for (const auto& number : data) {
        distance_sum += std::abs(number.first - number.second);
    }
    
    return distance_sum;
}

std::vector<std::pair<int, int>> order_numbers(std::vector<std::pair<int, int>> data) {
    std::vector<std::pair<int, int>> ordered_numbers;
    
    while (!data.empty()) {
        int min1 = INT_MAX, min2 = INT_MAX;
        int index1 = -1, index2 = -1;

        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first < min1 && data[i].first > 0) {
                min1 = data[i].first;
                index1 = i;
            }
            if (data[i].second < min2 && data[i].second > 0) {
                min2 = data[i].second;
                index2 = i;
            }
        }

        if (index1 != -1 && index2 != -1) {
            ordered_numbers.emplace_back(data[index1].first, data[index2].second);
            data[index1].first = 0;
            data[index2].second = 0;
        }

        // Remove used pairs where both elements are zero
        data.erase(std::remove_if(data.begin(), data.end(), [](const std::pair<int, int>& p) {
            return p.first == 0 && p.second == 0;
        }), data.end());
    }

    return ordered_numbers;
}

long long int similarity_score(std::vector<std::pair<int, int>> data) {
    long long int similarity_score = 0;
    
    for (const auto& it : data) {
        int counter = 0;

        for (const auto& pair : data) {
            if (it.first == pair.second) {
                counter++;
            }
        }
        
        similarity_score += counter * it.first;
    }
    
    return similarity_score;
}


int main() {
    std::string filename = "input.txt";
    std::vector<std::pair<int, int>> data = parse_input(filename);
    
    if (data.empty()) {
        std::cerr << "No valid data to process." << std::endl;
        return 1;
    }

    data = order_numbers(data);
    
    long long int distance_sum = calculate_distances(data);
    
    printf("Total sum of distances: %lld\n", distance_sum);
    printf("Total similarity score: %lld\n", similarity_score(data));
    
    return 0;
}
