#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <map>

using namespace std;

string joinPath(list<string>& path) {
    string joined = "";
    for (string dir : path) {
        joined += "/" + dir;
    }
    return joined;
}

int main()
{
    string s;
    string delim;

    list<string> path;
    map<string, unsigned> sizes;

    ifstream inFile("input.txt", ifstream::in);
    while (getline(inFile, s)) {
        if (!s.empty()) {
            stringstream ss(s);
            
            if (ss.peek() == '$') {
                string command;
                ss >> delim >> command;
                if (command == "cd") {
                    string param;
                    ss >> param;

                    if (param == "/") {
                        path.clear();
                    }
                    else if (param == "..") {
                        path.pop_back();
                    }
                    else {
                        path.push_back(param);
                    }
                }
            }
            else if (ss.peek() == 'd') {
                //dir, not needed
            }
            else {
                unsigned size;
                ss >> size >> delim;

                list<string> pathCopy(path);

                while (!pathCopy.empty()) {
                    string dir = joinPath(pathCopy);
                    auto itr = sizes.find(dir);
                    if (itr != sizes.end()) {
                        sizes.insert_or_assign(dir, itr->second + size);
                    }
                    else {
                        sizes.insert({ dir, size });
                    }
                    pathCopy.pop_back();
                }

                auto itr = sizes.find("/");
                if (itr != sizes.end()) {
                    sizes.insert_or_assign("/", itr->second + size);
                }
                else {
                    sizes.insert({ "/", size });
                }
            }
        }
    }
      
    unsigned sum = 0;
    
    unsigned smallest = 70000000;
    unsigned check = (sizes.find("/")->second) - 40000000;	//Const 3k

    list<unsigned> sizeList;

    for (auto itr : sizes) {
        cout << itr.first << " " << itr.second << endl;
        if (itr.second <= 100000 && itr.first != "/") {
            sum += itr.second;
        }

        if (itr.second >= check && itr.second < smallest) {
            smallest = itr.second;
        }
        sizeList.push_back(itr.second);
    }
    sizeList.sort();

    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << smallest << endl;
}
