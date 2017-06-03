#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 40010;
struct Edge
{
    int u,v,cost;
};
Edge EDGE[MAXM];
int PRE[MAXN],ID[MAXN],VISIT[MAXN],IN[MAXN];
int zhuliu(int root,int n,int m)
{
    int res = 0,u,v;
    while(1)
    {
        for(int i = 0; i < n; i++)IN[i] = INF;
        for(int i = 0; i < m; i++)
            if(EDGE[i].u != EDGE[i].v && EDGE[i].cost < IN[EDGE[i].v])
            {
                PRE[EDGE[i].v] = EDGE[i].u;
                IN[EDGE[i].v] = EDGE[i].cost;
            }
        for(int i = 0; i < n; i++)
            if(i != root && IN[i] == INF)
                return -1; //不存在最小?形?
        memset(ID,-1,sizeof(ID));
        memset(VISIT,-1,sizeof(VISIT));
        IN[root] = 0;
        int tn = 0;
        for(int i = 0; i < n; i++)
        {
            res += IN[i];
            v = i;
            while( VISIT[v] != i && ID[v] == -1 && v != root)
            {
                VISIT[v] = i;
                v = PRE[v];
            }
            if( v != root && ID[v] == -1 )
            {
                for(int u = PRE[v]; u != v ; u = PRE[u])
                    ID[u] = tn;
                ID[v] = tn++;
            }
        }
        if(tn == 0)break;
        //?有有向?
        for(int i = 0; i < n; i++)
            if(ID[i] == -1)
                ID[i] = tn++;
        for(int i = 0; i < m;)
        {
            v = EDGE[i].v;
            EDGE[i].u = ID[EDGE[i].u];
            EDGE[i].v = ID[EDGE[i].v];
            if(EDGE[i].u != EDGE[i].v)
                EDGE[i++].cost -= IN[v];
            else
              swap(EDGE[i],EDGE[--m]);
        }
        n = tn;
        root = ID[root];
    }
    return res;
}
int g[MAXN][MAXN];
int main()
{
	freopen("in.txt","r",stdin);
    int n,m;
    int kase = 0;
    int T;
    scanf("%d", &T);
    while( T-- )
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                g[i][j] = INF;
        while(m--)
        {
        	static int u,v,cost;
            scanf("%d%d%d", &u, &v, &cost);
            if(u == v)continue;
            g[u][v] = min(g[u][v],cost);
        }
        int L = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(g[i][j] < INF)
                {
                    EDGE[L].u = i;
                    EDGE[L].v = j;
                    EDGE[L++].cost = g[i][j];
                }
        int ans = zhuliu(0, n, L);
        printf("Case #%d: ", ++kase);
        if(ans == -1)printf("Possums!\n");
        else printf("%d\n", ans);
    }
    return 0;
}


