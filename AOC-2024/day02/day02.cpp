#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// Parse the input file
std::vector<std::vector<int>> parse_input(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::vector<int>> data;

    if (!infile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) { // Read line by line
        std::istringstream iss(line);
        std::vector<int> row;
        int num;
        while (iss >> num) { // Extract integers from the line
            row.push_back(num);
        }
        if (!row.empty()) { // Add non-empty rows to the data
            data.push_back(row);
        }
    }

    return data;
}

// Check if a report is safe without tolerance
bool is_safe(const std::vector<int>& report) {
    bool increasing = true, decreasing = true;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];

        // Check if the difference is within the range [1, 3]
        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }

        // Check if the sequence is consistently increasing or decreasing
        if (diff > 0) {
            decreasing = false;
        } else if (diff < 0) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

// Check if a report is safe with tolerance
bool is_safe_with_tolerance(const std::vector<int>& report) {
    if (is_safe(report)) {
        return true; // Already safe without tolerance
    }

    // Check each possible removal
    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modified_report = report;
        modified_report.erase(modified_report.begin() + i); // Remove one level
        if (is_safe(modified_report)) {
            return true; // Safe after removing one level
        }
    }

    return false; // Not safe even with tolerance
}

// Count the number of safe reports
int count_safe_reports(const std::vector<std::vector<int>>& reports, bool tolerance = false) {
    int safe_count = 0;

    for (const auto& report : reports) {
        if (tolerance) {
            if (is_safe_with_tolerance(report)) {
                ++safe_count;
            }
        } else {
            if (is_safe(report)) {
                ++safe_count;
            }
        }
    }

    return safe_count;
}

int main() {
    std::string filename = "input.txt";
    std::vector<std::vector<int>> data = parse_input(filename);

    if (data.empty()) {
        std::cerr << "No valid data to process." << std::endl;
        return 1;
    }

    std::cout << "Day02 solution" << std::endl;
    std::cout << "Number of safe reports: " << count_safe_reports(data) << std::endl;
    std::cout << "Number of safe reports with tolerance: " << count_safe_reports(data, true) << std::endl;

    return 0;
}
