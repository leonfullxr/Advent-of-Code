#include <fstream>
#include <iostream>

std::string processInput(std::string) {
    std::ifstream file("input.txt");
    std::string line;
    std::string input;
    while (std::getline(file, line)) {
        input += line;
    }
    return input; 
}

std::string extendSequence(std::string input) {
    
}


int main() {
    std::string input = processInput("input.txt");
    

}