#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int solve(const string file, const int window_length){
	ifstream input(file);
	string data; 
	getline(input, data);
	int dp[123] = {};
	
	for(int i =0;i < window_length; ++i)
		++dp[data[i]];    

	int val = 0;
	for(int i =0; i < 123; ++i)
		val = val | dp[i]; 
		
	if (!(val ^ 1)) return window_length;

	int N = static_cast<int>(data.size());
	for(int i = window_length; i < N; ++i){
	    --dp[data[i-window_length]];
	    ++dp[data[i]];
	    val = 0; 
	    
	    for(int i =0; i < 123; ++i)
	    	val = val | dp[i]; 
	    
	    if (!(val ^ 1)) 
	    	return i +1;
	}
	return -1;
}

int main(int argc, const char *argv[]){
	cout << solve("input.txt",4) << endl;
	cout << solve("input.txt",14) << endl;
	
	return 0;
}
