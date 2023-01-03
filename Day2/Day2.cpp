#include <iostream>
#include <fstream>
#include <string>

//using namespace std;

enum RESULT{
WIN = 6,
DRAW = 3,
LOSS = 0
};

enum RPC{
ROCK = 1,
PAPER = 2,
SCISSORS = 3
};

#define FIRSTROCK "A"
#define FIRSTPAPER "B"
#define SECONDLOSS "X"
#define SECONDDRAW "Y"


int move[8][3] = {
    {ROCK, PAPER, SCISSORS},
    {SCISSORS, ROCK, PAPER},
    {},
    {},
    {ROCK, PAPER, SCISSORS},
    {},
    {},
    {PAPER, SCISSORS, ROCK},
};

int main(){ 
    std::ifstream file("Day2.txt");
    std::string text; 

    int counter = 0;

    while (std::getline(file, text)) {
        if (text.empty()) {
        } else {
            std::string substring = text.substr(0, text.find(' '));
            std::string secondSubstring = text.substr(text.find(' ') + 1);
            int first = (substring == FIRSTROCK) ? ROCK : (substring == FIRSTPAPER) ? PAPER : SCISSORS;
            RESULT second = (secondSubstring == SECONDLOSS) ? LOSS : (secondSubstring == SECONDDRAW) ? DRAW : WIN;
            counter += second;

            counter += move[second + 1][first - 1];
         } 
    }
    std::cout << counter << std::endl;

    return 0;
}
