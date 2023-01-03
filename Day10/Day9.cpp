#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    string instruction;
    vector<int> program;
    
    while(!input.eof()) {
        input >> instruction;

        if(instruction == "addx") {
            input >> instruction;
            program.push_back(0);
            program.push_back(atoi(instruction.c_str()));
        }
        else {
            program.push_back(0);
        }
    }

    int xRegister = 1;
    int strengthSum = 0;
    string line(40, ' ');

    for(int i = 0; i < program.size(); i++) {
        int cycle = i + 1;
        int pixel = i % 40;

        if(pixel >= xRegister - 1 && pixel <= xRegister + 1) {
            line[pixel] = '#';
        }
	
	if(cycle % 40 == 20) {
            strengthSum += xRegister * cycle;
        }
        
        if(cycle % 40 == 0) {
            cout << line << endl;
            line = string(40, ' ');
        }

        xRegister += program[i];
        
    }
    cout << "Part 1: " << strengthSum << endl;

    return 0;
}
