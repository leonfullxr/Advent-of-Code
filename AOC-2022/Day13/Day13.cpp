#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

bool isNumeric(char letter){
  return (letter >= '0' && letter <= '9');
}

int main(){
  ifstream input("input.txt");
  string line1, line2;
  vector<int> right;
  int index = 0;
  while(getline(input,line1)){
    if(line1.length() == 0) continue;
    index++;
    getline(input, line2);
    int i = 0, j = 0;
    while(i < line1.length() && j < line2.length()){
      if(isNumeric(line1[i]) && isNumeric(line2[j])){
        string x1 = "", x2 = "";
        while(i < line1.length() && isNumeric(line1[i])){
          x1 += line1[i];					//list 1
          i++;							//numbers in list1
        }
        while(j < line2.length() && isNumeric(line2[j])){
          x2 += line2[j];					//list 2
          j++;							//numbers in list2
        }
        if(stoi(x1) == stoi(x2)) continue;
        if(stoi(x1) < stoi(x2))
          right.push_back(index);
        break;
      }
      if(line1[i] == line2[j]){
        i++;
        j++;
        continue;
      }else{
        if(line1[i] == ']'){
          right.push_back(index);
          break;
      }else if(line2[j] == ']') break;
       else if(line1[i] == '[' || line1[i] == ','){ 
            i++;
            continue;
       }else if(line2[j] == '[' || line2[j] == ','){
            j++;
            continue;
       }
      }
    }
    if(i == line1.length()) right.push_back(index);	//list 1 has reached its end
  }
  int answer = 0;
  cout << accumulate(right.begin(), right.end(), answer) << endl;
}
