#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void invert_stack(vector<stack<char>> &v){
	vector<stack<char>> aux(9);
	
	for(vector<stack<char>>::iterator it=v.begin(); it!=v.end(); it++){
		
		for(int i = 0; i < (*it).size(); i++){
			aux[i].push((*it).top());
			(*it).pop();
		}
	}
	v.swap(aux);
	aux.clear();
}


void input(){
	fstream input;
	vector<stack<char>> v(9);
	input.open("input.txt", ios::in);
	string line;
	
	while(getline(input, line)){ 
		if(isdigit(line[1]))
			break;

		for(int pos = 1, i = 0; pos < line.length(); ++i, pos += 4) 
	   		 if(isalpha(line[pos]))
	       	 		v[i].push(line[pos]);
	}

	while(getline(input, line)) {

		if(line.length() == 0) continue;

		int num, from, to;
		sscanf(line.c_str(), "move %d from %d to %d", &num, &from, &to);

		--from;
		--to;

		for(int i = 0; i < num; i++){
			v[to].push(v[from].top());
			v[from].pop();
		}
	}
	
	cout << "\nPart 1 : ";
	for(auto& s: v)
		cout << s.top();
}

void p2(){
fstream fin;
    fin.open("input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    string stack[10];
    while(getline(fin, line)){ 
        if(isdigit(line[1])) break;

        for(int pos = 1, i = 0; pos < line.length(); ++i, pos += 4) 
            if(isalpha(line[pos]))
                stack[i] += line[pos];
    }

    for(auto& s: stack)
        reverse(s.begin(), s.end());

    while(getline(fin, line)) {

        if(line.length() == 0) continue;

        int howMany, from, to;
        sscanf(line.c_str(), "move %d from %d to %d", &howMany, &from, &to);

        --from;
        --to;

        stack[to] += stack[from].substr(stack[from].length() - howMany);
        stack[from].erase(stack[from].length() - howMany);
    }

    string sol = "";
    for(auto& s: stack)
        if(s.length() > 0)
            sol += s.back();

    cout << sol << endl;
}

int main(int argc, const char *argv[]){
	input();
	
	return 0;
}
