#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm> 
using namespace std;
struct edge {
    int to, cnt;
    edge(int a=0, int b=0):
        to(a) , cnt(b) {}
};
vector<edge> g[10005];
int vfind[10005], findIdx;
int stk[10005], stkIdx;
int in_stk[10005], visited[10005];
//
int parent[10005];
edge *parentUsed[10005];
int checkflag;
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd], i;
    for(i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i].to]) {
            parent[g[nd][i].to] = nd;
            parentUsed[nd] = &g[nd][i];
            mn = min(mn, scc(g[nd][i].to));
        }
        if(in_stk[g[nd][i].to])
		{
            mn = min(mn, vfind[g[nd][i].to]);
            if(vfind[g[nd][i].to] <= vfind[nd])
			{
                // cycly find.
                if(checkflag)continue;
                g[nd][i].cnt++;
                if(g[nd][i].cnt > 1)checkflag = 1;
                int next = nd;
                while(checkflag == 0)
				{
                    parentUsed[parent[next]]->cnt++;
                    if(parentUsed[parent[next]]->cnt > 1)checkflag = 1;
                    next = parent[next];
                    if(next == g[nd][i].to)break;
                }
            }
        }
    }
    if(mn == vfind[nd])
	{
        do
		{
            in_stk[stk[stkIdx]] = 0;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int main() {
    int testcase;
    int n, m;
    int i, j, k, x, y;
    scanf("%d", &testcase);
    while(testcase--)
	{
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)g[i].clear();
        for(i = 0; i < m; i++)
		{
            scanf("%d %d", &x, &y);
            g[x].push_back(edge(y, 0));
        }
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        int component = 0;
        checkflag = 0;
        for(i = 0; i < n; i++) {
            if(visited[i] == 0) {
                findIdx = stkIdx = 0;
                if(++component > 1)    break;
                scc(i);
            }
        }
        for(i = 0; i < n; i++)
            for(j = 0; j < g[i].size(); j++)
                if(g[i][j].cnt != 1)
                    checkflag = 1;
        if(component > 1)    checkflag = 1;
        puts(checkflag == 0 ? "YES" : "NO");
#define debug 0
#if debug == 1
        for(i = 0; i < n; i++)
            for(j = 0; j < g[i].size(); j++)
                printf("%d -> %d %d\n", i, g[i][j].to, g[i][j].cnt);
        printf("%d %d\n", checkflag, component);
#endif
    }
    return 0;
}
