#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct E {
    int x, y, v;
    bool operator<(const E &a) const {
        return v > a.v;
    }
};
E D[1250000];
vector<int> g[5005];
int p[5005], rank[5005];//disjoint set.
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)  return 0;
    if(rank[x] > rank[y])
        rank[x] += rank[y], p[y] = x;
    else
        rank[y] += rank[x], p[x] = y;
    return 1;
}
int check(int x, int n) {//divide s-t set
    int smn = 0xfffff, tmx = 0;
    int i, j, y, pp, e;
    E edge;
    x = findp(x);
    for(i = 1; i <= n; i++) {
        pp = findp(i);
        if(pp != x) continue;
        // find a set {s}
        for(j = 0; j < g[i].size(); j++) {
            e = g[i][j];
            edge = D[e];
            if(edge.x != i)
                pp = findp(edge.x);
            else
                pp = findp(edge.y);
            if(pp == x) //same {s}
                smn = min(smn, edge.v);
            else
                tmx = max(tmx, edge.v);
        }
        if(smn < tmx)   return false;
    }
    return smn > tmx;
}
void MST(int n, int m) {//max spanning tree
    int ret = 0, i, j;
    for(i = 1; i <= n; i++)
        p[i] = i, rank[i] = 1;
    sort(D, D+m);
    for(i = 0; i < m; i++) {
        g[D[i].x].push_back(i);
        g[D[i].y].push_back(i);
    }
    for(i = 0; i < m; i++) {
        if(joint(D[i].x, D[i].y)) {
            if(check(D[i].x, n))
                ret += rank[findp(D[i].x)];
        }
    }
    printf("%d\n", ret);
}
int main() {
    int testcase, n, m, i;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++)
            g[i].clear();
        for(i = 0; i < m; i++)
            scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);
        MST(n, m);
    }
    return 0;
}

