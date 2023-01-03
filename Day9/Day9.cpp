#include <set>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Coord{
	int x;
	int y;
};

bool operator<(const Coord& c1, const Coord& c2)
{
	return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
}

int solve(string file){
	fstream input;
	input.open(file,ios::in);
	char direction;
	int num;
	set<Coord> visited;			//To check if the Coord is unique
	Coord posH = {0,0}, posT = {0,0};	//Start
	visited.insert(posH);
	
	while(input >> direction >> num){
		for(int i = 0; i < num; i++){
			switch(direction){
				case 'U':{
					posH.y++;
				}break;
				case 'D':{
					posH.y--;
				}break;
				case 'L':{
					posH.x--;
				}break;
				case 'R':{
					posH.x++;
				}break;
			}
			if(posT.x + 1 < posH.x){
				posT.x++;
				if(posT.y < posH.y){
					posT.y++;
				}else if(posT.y > posH.y){
					posT.y--;
				}
				
			}else if(posT.x - 1 > posH.x){
				posT.x--;
				if(posT.y < posH.y){
					posT.y++;
				}else if(posT.y > posH.y){
					posT.y--;
				}
			}else if(posT.y + 1 < posH.y){
				posT.y++;
				if(posT.x < posH.x){
					posT.x++;
				}else if(posT.x > posH.x){
					posT.x--;
				}
			}else if(posT.y - 1 > posH.y){
				posT.y--;
				if(posT.x < posH.x){
					posT.x++;
				}else if(posT.x > posH.x){
					posT.x--;
				}
			}
			
			visited.insert(posT);
		}
	}
	return visited.size();
}


int main(){
	cout << "Part 1: " << solve("input.txt") << endl;
}
