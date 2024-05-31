#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <fstream>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

struct Position {
    int x, y, bot, turns, time;

    Position() = default;
};

int BFS(const  vector< vector<int>>& grid, int n, int m, int k, int startX, int startY, int endX, int endY) {
     queue<Position> q;
     vector< vector< vector< vector<bool>>>> visited(n, vector<vector<vector<bool>>>(m,vector<vector<bool>>(4,vector<bool>(k + 1, false))));

    for (int dir = 0; dir < 4; ++dir) {q.push({ startX, startY, dir, 0, 0 });visited[startX][startY][dir][0] = true; }

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        int x = current.x, y = current.y, dir = current.bot, turns = current.turns, time = current.time;

        if (x == endX && y == endY) {return time;}

        for (int newDir = 0; newDir < 4; ++newDir) {
            int newX = x + dx[newDir];
            int newY = y + dy[newDir];
            int newTurns = turns + (newDir != dir);

            if (newX >= 0 && newX < n && newY >= 0 && newY < m && grid[newX][newY] != 1 && newTurns <= k && !visited[newX][newY][newDir][newTurns]) {
                visited[newX][newY][newDir][newTurns] = true;
                q.push({ newX, newY, newDir, newTurns, time + 1 });
            }
        }
    }

    return -1;
}

int main() {
     ifstream inputFile("INPUT.TXT");
     ofstream outputFile("OUTPUT.TXT");

    int n, m, resultat;
    inputFile >> n >> m;

    vector< vector<int>> grid(n, vector<int>(m));
    int startX, startY, endX, endY;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inputFile >> grid[i][j];
            if (grid[i][j] == 2) {startX = i;startY = j;}
            else if (grid[i][j] == 3) {endX = i;endY = j;}
        }
    }

    inputFile >> resultat;

    int result = BFS(grid, n, m, resultat, startX, startY, endX, endY);
    outputFile << result;

    return 0;
}
