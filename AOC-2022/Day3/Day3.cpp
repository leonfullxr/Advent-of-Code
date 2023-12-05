#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <tuple>

typedef std::pair<int, int> pair;

void charMapper (std::map<char, pair>& charMap, std::string& string, int iterCount) {
    for (int i = 0; i <= string.length();i++){
        char letter = string[i];
        if (charMap[letter].second == iterCount){
            charMap[letter].second++;
        }
    }
}

int scoreCalc (std::map<char, pair>& charMap, int scoreCount) {
    int score = 0;
    for (auto const& iter : charMap) {
        if (iter.second.second == scoreCount){
            score+=iter.second.first;
        }
    }
    return score;
}

int parseBackpackPt1 (std::string& readBackpack, std::map<char, pair> charMap) {

    std::string firstHalf = readBackpack.substr(0, (readBackpack.length()/2));
    std::string secondHalf = readBackpack.substr((readBackpack.length()/2), readBackpack.length());

   
    charMapper(charMap, firstHalf, 0);
    charMapper(charMap, secondHalf, 1);

    return scoreCalc(charMap, 2);
}

int parseBackpackPt2 (std::tuple<std::string,std::string,std::string>& currentGroup, std::map<char, pair> charMap) {

    std::string first = std::get<0>(currentGroup);
    std::string second = std::get<1>(currentGroup);
    std::string third = std::get<2>(currentGroup);

    charMapper(charMap, first, 0);
    charMapper(charMap, second, 1);
    charMapper(charMap, third, 2);

    return scoreCalc(charMap, 3);
}

int main () {

    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::map<char, pair> charMap;

    for (int i = 1 ; i <= chars.length() ; i++){
        charMap[chars[i-1]] = std::make_pair( i, 0 );
    }

    // Remove Null Terminating String
    charMap.erase('\x00');

    std::ifstream backpackList("input.txt");
    std::string readBackpack;
    int score1 = 0;
    int score2 = 0;
    std::tuple<std::string,std::string,std::string> currentGroup = std::make_tuple("","","");
    int currGroupSize = 0;

    while(getline(backpackList, readBackpack)) {
        score1 += parseBackpackPt1(readBackpack, charMap);

        switch (currGroupSize)
        {
        case 0:
            std::get<0>(currentGroup) = readBackpack;
            currGroupSize++;
            break;
        case 1:
            std::get<1>(currentGroup) = readBackpack;
            currGroupSize++;
            break;
        case 2:
            std::get<2>(currentGroup) = readBackpack;
            score2 += parseBackpackPt2(currentGroup, charMap);
            currGroupSize = 0;
            break;
        default:
            break;
        }
    }
    
    std::cout << score1 << std::endl;
    std::cout << score2 << std::endl;

}
