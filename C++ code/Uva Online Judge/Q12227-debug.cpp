#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include<cassert>
using namespace std;
struct Point3D
{
    long long x, y, z;
    Point3D(long long a = 0, long long b = 0, long long c = 0):
    x(a), y(b), z(c) {}
    void read(){scanf("%lld %lld %lld", &x, &y, &z);}
    long long dist(const Point3D &a)const{return ceil(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y)+(a.z-z)*(a.z-z)));}
};
struct Edge {
    int to;
    long long creation, shift;
    Edge(int to = 0, long long creation = 0, long long shift = 0):
    to(to), creation(creation), shift(shift) {}
//    bool operator<(const Edge &a) const {return d < a.d;}
};
#define MAXN 128
#define INF (1LL<<60)
int N;
vector<Edge> G[MAXN];
long long DIST[MAXN], preTime[MAXN];
int INQ[MAXN], CNT[MAXN], PRE[MAXN], USED[MAXN], CASES = 0;
void goToNegCycle()
{
    for (int i = 0; i < N; i++)CNT[i]=0,DIST[i]=INF,PRE[i]=-1,INQ[i]=0;
    DIST[0] = 0;
    deque<int> Q;
    Q.push_front(0);
    while (!Q.empty())
	{
        int u = Q.front();Q.pop_front();
        INQ[u] = 0;
        for (int i = 0; i < G[u].size(); i++)
		{
            long long cost = G[u][i].shift;
            if (G[u][i].creation > DIST[u])cost = G[u][i].shift + G[u][i].creation - DIST[u];
            if (DIST[G[u][i].to] <= DIST[u] + cost)continue;
            DIST[G[u][i].to] = DIST[u] + cost;
            PRE[G[u][i].to] = u, preTime[G[u][i].to] = G[u][i].creation;
            if (INQ[G[u][i].to])continue;
            if (++CNT[G[u][i].to] > N + 1)
			{
                CASES++;
                CNT[G[u][i].to] = 1;
                int st=-1;
                for (int j = PRE[G[u][i].to]; j != -1; j = PRE[j])
				{
                    if (USED[j] == CASES){st = j;break;}
                    USED[j] = CASES;
                }
                assert(st==-1);
                long long mx = preTime[st];
				int disappear = st;
                for (int j = PRE[st]; j != -1; j = PRE[j])
				{
                    if (j == st)break;
                    if (preTime[j] > mx)mx = preTime[j], disappear = j;
                }
                if (DIST[disappear]>mx)
				{
                    DIST[disappear] = mx;
                    if (Q.size() && DIST[Q.front()] > DIST[disappear])Q.push_front(disappear);
                    else Q.push_back(disappear);
                }
            }
            if (!INQ[G[u][i].to])
			{
                INQ[G[u][i].to] = 1;
                if (Q.size() && DIST[Q.front()] > DIST[G[u][i].to])Q.push_front(G[u][i].to);
                else Q.push_back(G[u][i].to);
            }
        }
    }
}
void spfa()
{
    goToNegCycle();
    printf("%lld\n", DIST[1]);
}
int main() {
	freopen("in.txt","r",stdin);
    int testcase;
    long long t, d;
    Point3D D[MAXN];
    scanf("%d", &testcase);
    while (testcase--)
	{
        for (int i = 0; i < MAXN; i++)G[i].clear();
        D[0].read();
        D[1].read();
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
		{
            D[(1 + i) * 2].read();
            D[(1 + i) * 2 + 1].read();
            scanf("%lld %lld", &t, &d);
            G[(1 + i) * 2].push_back(Edge((1 + i) * 2 + 1, t, d));
        }
        N = (N + 1) * 2;
        for (int i = 0; i < N; i++)
		{
            for (int j = 0; j < N; j++)
			{
                if (i == j) continue;
                G[i].push_back(Edge(j, -INF, D[i].dist(D[j])));
            }
        }
        spfa();
    }
    return 0;
}

