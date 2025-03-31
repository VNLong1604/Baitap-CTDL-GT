#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

typedef pair<int, int> pii;

void bfs(vector<vector<int>>& maze, int N, int M, int x0, int y0, int x1, int y1) {
    vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pair<int, int>> q;
    vector<vector<pii>> parent(N, vector<pii>(M, {-1, -1}));
    set<pii> visited;
    
    q.push({x0, y0});
    visited.insert({x0, y0});
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if (x == x1 && y == y1) {
            vector<pii> path;
            while (x != -1 && y != -1) {
                path.push_back({x, y});
                tie(x, y) = parent[x][y];
            }
            reverse(path.begin(), path.end());
            cout << path.size() << "\n";
            for (auto& p : path) cout << p.first << " " << p.second << "\n";
            return;
        }
        
        for (auto& d : directions) {
            int nx = x + d.first, ny = y + d.second;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx][ny] == 0 && visited.find({nx, ny}) == visited.end()) {
                visited.insert({nx, ny});
                q.push({nx, ny});
                parent[nx][ny] = {x, y};
            }
        }
    }
    cout << "0\n";
}

void dfs(vector<vector<int>>& maze, int N, int M, int x0, int y0, int x1, int y1) {
    vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    stack<pair<int, int>> s;
    vector<vector<pii>> parent(N, vector<pii>(M, {-1, -1}));
    set<pii> visited;
    
    s.push({x0, y0});
    visited.insert({x0, y0});
    
    while (!s.empty()) {
        int x = s.top().first;
        int y = s.top().second;
        s.pop();
        
        if (x == x1 && y == y1) {
            vector<pii> path;
            while (x != -1 && y != -1) {
                path.push_back({x, y});
                tie(x, y) = parent[x][y];
            }
            reverse(path.begin(), path.end());
            cout << path.size() << "\n";
            for (auto& p : path) cout << p.first << " " << p.second << "\n";
            return;
        }
        
        for (auto& d : directions) {
            int nx = x + d.first, ny = y + d.second;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx][ny] == 0 && visited.find({nx, ny}) == visited.end()) {
                visited.insert({nx, ny});
                s.push({nx, ny});
                parent[nx][ny] = {x, y};
            }
        }
    }
    cout << "0\n";
}

int main() {
    int N, M, x0, y0, x1, y1;
    cin >> N >> M >> x0 >> y0 >> x1 >> y1;
    vector<vector<int>> maze(N, vector<int>(M));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> maze[i][j];
        }
    }
    
    string type_search;
    cin >> type_search;
    
    if (type_search == "BFS") {
        bfs(maze, N, M, x0, y0, x1, y1);
    } else if (type_search == "DFS") {
        dfs(maze, N, M, x0, y0, x1, y1);
    }
    
    return 0;
}
