#include<bits/stdc++.h>

using namespace std;
#define mp make_pair

bool isPossible(int row, int col, int n, int m){
  return !(row >= n || col >= m || row < 0 || col < 0);
}

int main(){
  string line;
  vector<string> grid;
  ifstream input("input.txt");
  while(getline(input, line)){
    grid.push_back(line);
  }

  int n = grid.size(), m = grid[0].size();
  pair<int, int> end;
  for(int i = 0; i < n; i++){	//rows
    for(int j = 0; j < m; j++){	//col
      if(grid[i][j] == 'E') {	//End
        end = mp(i,j);		//Pos entrance
        grid[i][j] = 'z';	//The max letter, start pos
      }
    }
  }
  
  queue<pair<int, pair<int, int>>> q;	//Distance, rows, col
  vector<vector<bool>> visited(n, vector<bool>(m,false));
  visited[end.first][end.second] = true;

  q.push(mp(0, end));	//start
  while(!q.empty()){
    int dist = q.front().first;
    int row = q.front().second.first;
    int col = q.front().second.second;
    q.pop();
    
    if(grid[row][col] == 'a') {		//End found, print distance
      cout << dist;
      return 0;
    }
	//you can only move 1 pos at a time
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    for(int i = 0; i < 4; i++){
      if(isPossible(row + dx[i], col + dy[i], n, m) && !visited[row + dx[i]][col + dy[i]]){
        char prev = grid[row + dx[i]][col + dy[i]] == 'S' ? 'a' : grid[row + dx[i]][col + dy[i]];
        if(grid[row][col] - prev <=1){
          visited[row + dx[i]][col + dy[i]] = true;
          q.push(mp(dist + 1, mp(row + dx[i], col + dy[i])));
        }
      }
    }
  }
}
