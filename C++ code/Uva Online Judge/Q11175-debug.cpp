#include <stdio.h>
#include <algorithm>
#include<vector>
using namespace std;
vector<int>g[305],invg[305];
int to[305];
int check(int n)
{
    int i, j, k;
    for(i = n-1; i >= 0; i--)
	{
        for(j = 0; j < n; j++)  to[j] = 0;
        for(j = invg[i].size()-1; j >= 0; j--)
		{
			int &u=invg[i][j];
            for(k = g[u].size()-1; k >= 0; k--)
			{
                to[g[u][k]]++;
            }
        }
        for(j = 0; j < n; j++)
		{
            if(to[j]&&to[j]!=invg[i].size())
                return 0;
        }
    }
    return 1;
}
int main()
{
	freopen("in.txt","r",stdin);
    int t, cases = 0;
    int n, m, i, x, y;
    scanf("%d", &t);
    while(t--)
	{
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            g[i].clear(), invg[i].clear();
        while(m--)
		{
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
            invg[y].push_back(x);
        }
        int flag = check(n);
        printf("Case #%d: %s\n", ++cases, flag ? "Yes" : "No");
    }
    return 0;
}

