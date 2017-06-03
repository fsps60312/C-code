#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <queue>  
using namespace std;  
  
const int N = 21;  
const int d[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};  
  
int n, vis[N][N][11][11][11][11];  
  
char g[N][N];  
  
struct State {  
    int x, y, val;  
    int up, left, down, right;  
    State() {x = y = up = left = down = right = 0;}  
    State(int x, int y, int up, int left, int down, int right) {  
        this->x = x;  
        this->y = y;  
        this->up = up;  
        this->left = left;  
        this->down = down;  
        this->right = right;  
        val = max(max(max(up,left), down), right);  
    }  
    bool operator < (const State& c) const {  
        return val > c.val;  
    }  
} s;  
  
void init() {  
    for (int i = 0; i < n; i++) {  
        scanf("%s", g[i]);  
        for (int j = 0; j < n; j++)  
            if (g[i][j] == 'P')  
                s.x = i, s.y = j;  
    }  
}  
  
int bfs() {  
    memset(vis, 0, sizeof(vis));  
    priority_queue<State> Q;  
    Q.push(s);  
    vis[s.x][s.y][0][0][0][0] = 1;  
    while (!Q.empty()) {  
        State u = Q.top();  
        Q.pop();  
        if (u.x == 0 || u.x == n - 1 || u.y == 0 || u.y == n - 1) return u.val;  
        for (int i = 0; i < 4; i++) {  
            int xx = u.x + d[i][0];  
            int yy = u.y + d[i][1];  
            int up = u.up;  
            int left = u.left;  
            int down = u.down;  
            int right = u.right;  
            if (g[xx][yy] == 'R') up++;  
            if (g[n - 1 - yy][xx] == 'R') left++;  
            if (g[n - 1 - xx][n - 1 - yy] == 'R') down++;  
            if (g[yy][n - 1 - xx] == 'R') right++;  
            if (!vis[xx][yy][up][left][down][right]) {  
                vis[xx][yy][up][left][down][right] = 1;  
                Q.push(State(xx, yy, up, left, down, right));  
            }  
        }  
    }  
}  
  
int main() {  
    while (~scanf("%d", &n) && n) {  
        init();  
        printf("At most %d rose(s) trampled.\n", bfs());  
    }  
    return 0;  
} 

