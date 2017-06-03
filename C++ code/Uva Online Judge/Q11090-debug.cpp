#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<bitset>
#include<vector>
#include<string>
#include<cstdio>
#include<cmath>
#include<stack>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define FF(i, a, b) for(int i=a; i<b; i++)
#define FD(i, a, b) for(int i=a; i>=b; i--)
#define REP(i, n) for(int i=0; i<n; i++)
#define CLR(a, b) memset(a, b, sizeof(a))
#define debug puts("**debug**")
#define LL long long
#define PB push_back
using namespace std;

const int maxn = 51;
const double INF = 1000000000;
struct Edge
{
    int from, to;
    double dist;
};
int n, m;
vector<Edge> edges;
vector<int> G[maxn];
bool inq[maxn];
double d[maxn];
int cnt[maxn];

inline void init()
{
    REP(i, n) G[i].clear(); edges.clear();
}

void add(int a, int b, double c)
{
    edges.PB((Edge){a, b, c});
    int nc = edges.size();
    G[a].PB(nc-1);
}

bool negacycle()
{
    queue<int> q;
    CLR(inq, 0); CLR(cnt, 0);
    REP(i, n)   d[i] = INF, q.push(i);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        inq[u] = false;
        int nc = G[u].size();
        REP(i, nc)
        {
            Edge e = edges[G[u][i]];
            if(d[e.to] > d[u] + e.dist)
            {
                d[e.to] = d[u] + e.dist;
                if(!inq[e.to])
                {
                    q.push(e.to);
                    inq[e.to] = 1;
                    if(++cnt[e.to] > n) return true;
                }
            }
        }
    }
    return false;
}

bool ok(double m)
{
    int nc = edges.size();
    REP(i, nc) edges[i].dist -= m;
    bool ret = negacycle();
    REP(i, nc) edges[i].dist += m;
    return ret;
}

int main()
{
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
    int T;
    scanf("%d", &T);
    FF(kase, 1, T+1)
    {
        scanf("%d%d", &n, &m);
        init();
        int a, b; double c;
        double L = 0, R = 0, M;
        while(m--)
        {
            scanf("%d%d%lf", &a, &b, &c); a--; b--;
            add(a, b, c);
            R = max(R, c);
        }
        printf("Case #%d: ", kase);
        if(!ok(R + 1))
        {
            puts("No cycle found.");
            continue;
        }
        while(R - L > 1e-3)
        {
            M = (L + R) / 2;
            if(ok(M)) R = M;
            else L = M;
        }
        printf("%.2lf\n", R);
    }
    return 0;
}
