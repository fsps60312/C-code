#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <queue>  
using namespace std;  
  
const int MAXNODE = 100005;  
const int MAXEDGE = 1000005;  
  
typedef int Type;  
const Type INF = 0x3f3f3f3f;  
  
struct Edge {  
    int u, v;  
    Type dist;  
    Edge() {}  
    Edge(int u, int v, Type dist) {  
        this->u = u;  
        this->v = v;  
        this->dist = dist;  
    }  
};  
  
struct HeapNode {  
    Type d;  
    int u;  
    HeapNode() {}  
    HeapNode(Type d, int u) {  
        this->d = d;  
        this->u = u;  
    }  
    bool operator < (const HeapNode& c) const {  
        return d > c.d;  
    }  
};  
  
struct Dijkstra {  
    int n, m;  
    Edge edges[MAXEDGE];  
    int first[MAXNODE];  
    int next[MAXEDGE];  
    bool done[MAXNODE];  
    Type d[MAXNODE];  
    int p[MAXNODE];  
  
    void init(int n) {  
        this->n = n;  
        memset(first, -1, sizeof(first));  
        m = 0;  
    }  
  
    void add_Edge(int u, int v, Type dist) {  
        edges[m] = Edge(u, v, dist);  
        next[m] = first[u];  
        first[u] = m++;  
    }  
  
    void dijkstra(int s) {  
        priority_queue<HeapNode> Q;  
        for (int i = 0; i < n; i++) d[i] = INF;  
        d[s] = 0;  
        p[s] = -1;  
        memset(done, false, sizeof(done));  
        Q.push(HeapNode(0, s));  
        while (!Q.empty()) {  
            HeapNode x = Q.top(); Q.pop();  
            int u = x.u;  
            if (done[u]) continue;  
            done[u] = true;  
            for (int i = first[u]; i != -1; i = next[i]) {  
                Edge& e = edges[i];  
                if (d[e.v] > d[u] + e.dist) {  
                    d[e.v] = d[u] + e.dist;  
                    p[e.v] = i;  
                    Q.push(HeapNode(d[e.v], e.v));  
                }  
            }  
        }  
    }  
} gao;  
  
// 0 up, 1 left, 2 right, 3 down  
const int D[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};  
  
int read_init() {  
    int x; scanf("%d", &x);  
    return x;  
}  
  
const int N = 105;  
int R, C, r1, c1, r2, c2;  
int grid[N][N][4], id[N][N][4][2];  
  
int get(int r, int c, int d, int flag) {  
    if (id[r][c][d][flag] == -1) id[r][c][d][flag] = gao.n++;  
    return id[r][c][d][flag];  
}  
  
bool can(int r, int c, int d) {  
    if (r < 0 || r >= R || c < 0 || c >= C) return false;  
    return grid[r][c][d] > 0;  
}  
  
int main() {  
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout); 
    int cas = 0;  
    while (~scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) && R) {  
        r1--; c1--; r2--; c2--;  
        memset(id, -1, sizeof(id));  
        memset(grid, 0, sizeof(grid));  
        gao.init(1);  
        for (int i = 0; i < R; i++) {  
            for (int j = 0; j < C - 1; j++)  
                grid[i][j + 1][1] = grid[i][j][2] = read_init();  
            if (i == R - 1) continue;  
            for (int j = 0; j < C; j++)  
                grid[i][j][3] = grid[i + 1][j][0] = read_init();  
        }  
        for (int i = 0; i < 4; i++) {  
            if (!can(r1, c1, i)) continue;  
            gao.add_Edge(0, get(r1 + D[i][0], c1 + D[i][1], i, 1), grid[r1][c1][i] * 2);  
        }  
        for (int i = 0; i < R; i++) {  
            for (int j = 0; j < C; j++) {  
                for (int d1 = 0; d1 < 4; d1++) {  
                    if (!can(i, j, 3 - d1)) continue;  
                    for (int d2 = 0; d2 < 4; d2++) {  
                        if (!can(i, j, d2)) continue;  
                        for (int flag = 0; flag < 2; flag++) {  
                            int x = i + D[d2][0];  
                            int y = j + D[d2][1];  
                            int v = grid[i][j][d2];  
                            int ff = 0;  
                            if (d1 != d2) {  
                                if (!flag) v += grid[i][j][3 - d1];  
                                ff = 1; v += grid[i][j][d2];  
                            }  
                            gao.add_Edge(get(i, j, d1, flag), get(x, y, d2, ff), v);  
                        }  
                    }  
                }  
            }  
        }  
        gao.dijkstra(0);  
        int ans = INF;  
        for (int i = 0; i < 4; i++) {  
            if (!can(r2, c2, 3 - i)) continue;  
            for (int j = 0; j < 2; j++) {  
                int v = gao.d[get(r2, c2, i ,j)];  
                if (!j) v += grid[r2][c2][3 - i];  
                ans = min(v, ans);  
            }  
        }  
        printf("Case %d: ", ++cas);  
        if (ans == INF) printf("Impossible\n");  
        else printf("%d\n", ans);  
    }  
    return 0;  
}
