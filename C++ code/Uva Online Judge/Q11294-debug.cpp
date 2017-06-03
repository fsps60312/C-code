#include <iostream>
#include <sstream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <string>
#include <stack>
#include <map>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#define esp 1e-6
#define pi acos(-1.0)
#define pb push_back
#define mp(a, b) make_pair((a), (b))
#define in  freopen("in.txt", "r", stdin);
#define out freopen("out.txt", "w", stdout);
#define print(a) printf("%d\n",(a));
#define bug puts("********))))))");
#define stop  system("pause");
#define Rep(i, c) for(__typeof(c.end()) i = c.begin(); i != c.end(); i++)

#define inf 0x0f0f0f0f

using namespace std;
typedef long long  LL;
typedef vector<int> VI;
typedef pair<int, int> pii;
typedef vector<pii,int> VII;
typedef vector<int>:: iterator IT;
const int maxn = 100000;
struct TwoSAT
{
    int n, mark[maxn*2], S[maxn*2], c;
    VI g[maxn*2];
    bool dfs(int x)
    {
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[x] = 1;
        S[c++] = x;
        for(int i = 0; i < g[x].size(); i++)
        {
            if(!dfs(g[x][i])) return false;
        }
        return true;
    }
    void init(int n)
    {
        this->n = n;
        for(int i = 0; i  < maxn; i++)
            g[i].clear();
        memset(mark, 0, sizeof(mark));
        mark[1] = 1;
    }
    void add(int x, int xval, int y, int yval)
    {
        x = 2*x+xval;
        y = 2*y+yval;
        g[x^1].pb(y);
        g[y^1].pb(x);
    }
    bool solve(int n)
    {
        for(int i = 0; i < 2*n; i += 2)
        {
            if(!mark[i] && !mark[i+1])
            {
                c = 0;
                if(!dfs(i))
                {
                    while(c) mark[S[--c]] = false;
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
} sat;
int main(void)
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    int n, m;
    while(scanf("%d%d", &n, &m), n||m)
    {
        char ch1, ch2;
        sat.init(n);
        int u, v, xval, yval;
        while(m--)
        {
            scanf("%d%c%d%c", &u, &ch1, &v, &ch2);
            xval = (ch1 == 'w') ? 1 : 0;
            yval = (ch2 == 'w') ? 1 : 0;
            sat.add(u, xval, v, yval);
        }
        if(sat.solve(n))
        {
            for(int i = 1; i < n; i++)
            {
            	if(i>1)printf(" ");
                printf("%d%c", i, sat.mark[2*i] ? 'h' : 'w');
			}
			puts("");
        }
        else puts("bad luck");
    }
    return 0;
}
