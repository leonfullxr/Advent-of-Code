#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace  std;
#define  SIZE 8
#define  int long long

struct Monkey{
    vector<int> items;
    char opr;
    string opr2;
    int divby;
    char iftrue, iffalse;
    int inspected;
};

void input(vector<Monkey>& m){
    for(int i = 0; i < SIZE; i++){
	ifstream cin("input.txt");
        string str;
        getline(cin, str); 
        if(i != 0) cin >> str >> str;
        cin >> str >> str; 

        while(cin >> str){
            if(str == "Operation:") break;
            if(str[str.size()-1] == ',') str.pop_back();
            m[i].items.push_back(stoi(str));  
        }
	cout << endl;

        cin >> str >> str >> str;
        cin >> m[i].opr;  
        cin >> m[i].opr2;

        cin >> str >> str >> str;
        cin >> m[i].divby;

        cin >> str >> str >> str >> str >> str;
        cin >> m[i].iftrue;
        cin >> str >> str >> str >> str >> str;
        cin >> m[i].iffalse;

        m[i].inspected = 0;
    }
}

int operation(int worry, char op, string op2){
    int dowith;
    if(op2 == "old") dowith = worry;
    else dowith = stoi(op2);
    switch(op){
        case '+': return worry + dowith;
        case '-': return worry - dowith;
        case '*': return worry * dowith;
        case '/': return worry / dowith;
    }
    return 0;
}

signed main() {
    
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);
    
    vector<Monkey> monkey(SIZE);
    input(monkey);

    int supermod = 1;
    for(auto m: monkey) supermod *= m.divby;
  
    for(int i = 1; i <= 10000; i++){
        for(int j = 0; j < SIZE; j++){
            monkey[j].inspected += monkey[j].items.size();
            for(auto worry: monkey[j].items){
                int newworry = operation(worry, monkey[j].opr, monkey[j].opr2) % supermod;
                int val;
                if(newworry % monkey[j].divby == 0) val = monkey[j].iftrue;
                else val = monkey[j].iffalse;
                monkey[val-'0'].items.push_back(newworry);
            }
            monkey[j].items.clear();
        }
    }
    vector<int> activity;
    for(auto m: monkey) activity.push_back(m.inspected);
    sort(activity.rbegin(), activity.rend());
    cout << activity[0] * activity[1];
	return 0;
}
