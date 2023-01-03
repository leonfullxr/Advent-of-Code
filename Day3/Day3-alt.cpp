#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
void part1();
void part2();
vector<char> getcommon(vector<string> strings);

int main() {
  part1();
  part2();

  return 0;
}

//
// finds characters common to all strings passed in
//
vector<char> getcommon(vector<string> strings) {
  vector<map<char, int>> all = {};
  map<char, int> seen = {};

  for (const string &s : strings) {
    for (char c : s) {
      seen[c] = 1;
    }
    all.push_back(seen);
    seen.clear();
  }

  map<char, int> final = {};
  for (const auto &seen2 : all) {
    for (const auto &[key, value] : seen2) {
      if (final.find(key) == final.end()) {
        final[key] = 1;
      } else {
        final[key] += 1;
      }
    }
  }

  int count = strings.size();
  vector<char> common = {};
  for (const auto &[key, value] : final) {
    if (value == count) {
      common.push_back(key);
    }
  }

  return common;
}

//
// returns value of character
//
int getpriority(char c) {
  if ((int(c) >= 97) && (int(c) <= 122)) {
    return (int(c) - int('`'));
  } else {
    return (int(c) - int('@') + 26);
  }
  return 0;
}

//
// part 1 solution
//
void part1() {
  ifstream inputfile;
  inputfile.open("input", ios::in);

  if (!inputfile) {
    cout << "Can't read input";
    exit(1);
  }

  vector<tuple<string, string>> data;

  string line;
  while (getline(inputfile, line)) {
    string c1 = line.substr(0, line.length() / 2);
    string c2 = line.substr(line.length() / 2);
    data.push_back(tuple<string, string>{c1, c2});
  }

  int sum = 0;
  for (auto [c1, c2] : data) {
    vector<char> common = getcommon(vector<string>{c1, c2});
    int value = getpriority(common[0]);
    sum = sum + value;
  }
  cout << "part1 sum of priorities: " << sum << endl;
}

//
// part 2 solution
//
void part2() {
  ifstream inputfile;
  inputfile.open("input", ios::in);

  if (!inputfile) {
    cout << "Can't read input";
    exit(1);
  }

  vector<char> badges;
  vector<string> group;

  string line;
  while (getline(inputfile, line)) {
    group.push_back(line);
    if (group.size() == 3) {
      vector<char> badge = getcommon(group);
      badges.push_back(badge[0]);
      group.clear();
    }
  }

  int sum = 0;
  for (const auto &b : badges) {
    sum += getpriority(b);
  }
  cout << "part2 sum of badges: " << sum << endl;
}
