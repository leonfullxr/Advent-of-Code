#include <iostream>
#include <fstream>
#include <string>

int calculateStringDifference(const std::string& line) {
    int codeLength = line.length();
    int memoryLength = 0;

    for (size_t i = 1; i < line.length() - 1; ++i) {
        char ch = line[i];
        if (ch == '\\') {
            if (line[i + 1] == '\\' || line[i + 1] == '\"') {
                memoryLength++;
                i++;
            } else if (line[i + 1] == 'x') {
                memoryLength++;
                i += 3;
            } else {
                memoryLength++;
                i++;
            }
        } else {
            memoryLength++;
        }
    }

    return codeLength - memoryLength;
}

std::string encodeString(const std::string& line) {
    std::string encodedLine = "\"";

    for (char ch : line) {
        if (ch == '\\' || ch == '\"') {
            encodedLine += '\\';
        }
        encodedLine += ch;
    }

    encodedLine += '\"';
    return encodedLine;
}

int calculateEncodedDifference(const std::string& line) {
    std::string encodedLine = encodeString(line);
    return encodedLine.length() - line.length();
}

int main() {
    int totalDifference = 0;
    std::ifstream file("input.txt");
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            totalDifference += calculateStringDifference(line);
        }
        file.close();
    }

    std::cout << "Total difference: " << totalDifference << std::endl;

    int totalEncodedDifference = 0;
    file.open("input.txt");

    if (file.is_open()) {
        while (std::getline(file, line)) {
            totalEncodedDifference += calculateEncodedDifference(line);
        }
        file.close();
    }

    std::cout << "Total encoded difference: " << totalEncodedDifference << std::endl;

    return 0;
}
