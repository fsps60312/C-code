#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <queue>
#define maxn 1005
#define MAXN 1000005
#define mod 100000000
#define INF 0x3f3f3f3f
#define pi acos(-1.0)
#define eps 1e-6
typedef long long ll;
using namespace std;

int n,m,ans,tot,flag;
char s[150][15];
int dp[1<<11][1<<11],mp[150];

int dfs(int s1,int s2)
{
    if(dp[s1][s2]<INF) return dp[s1][s2];
    int i,j,t=0;
    for(i=1;i<=n;i++)
    {
        if((mp[i]&s1)==s2) t++;
    }
    if(t<=1)
    {
        dp[s1][s2]=0;
        return 0;
    }
    int best=INF;
    for(i=0;i<m;i++)
    {
        if(s1&(1<<i)) continue ;
        best=min(best,max(dfs(s1|(1<<i),s2),dfs(s1|(1<<i),s2|(1<<i))));
    }
    dp[s1][s2]=best+1;
    return best+1;
}
int main()
{
    int i,j,t;
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0&&n==0) break ;
        for(i=1;i<=n;i++)
        {
            scanf("%s",s[i]);
            mp[i]=0;
            for(j=0;j<m;j++)
            {
                if(s[i][j]=='1') mp[i]|=(1<<j);
            }
        }
        memset(dp,0x3f,sizeof(dp));
        ans=dfs(0,0);
        printf("%d\n",ans);
    }
    return 0;
}

