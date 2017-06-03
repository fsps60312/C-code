// by eopXD
#include <cstdio>
#include <cstring>
#include <algorithm>
#define SZ(x)(int)((x).size())
using namespace std;
typedef long long LL;
#include <vector>
int n,m;
vector<int>G[80004],rG[80004];
int used[80004],cnt[80004];
void init()
{
	for(int i=0;i<=n;i++)
	{
		G[i].clear();
		rG[i].clear();	  
	}
	memset(used,0,sizeof(used));
	memset(cnt,0,sizeof(cnt));	 
}
void add_edge(int a,int b,int c)
{
	if(c)
	{
		G[a].push_back(b);
		G[b].push_back(a);	 
	}	  
	else
	{
		rG[a].push_back(b);
		rG[b].push_back(a);
	}
}
int A,B;
void dfs(int now, int mom, int type)
{
	used[now]=1;
	if(type)A++;
	else B++;
	for(int i=0;i<SZ(G[now]);i++)
	{
		int to=G[now][i];
		if(!used[to] && to!=mom)dfs(to,now,!type);	 
	}	  
	for(int i=0;i<SZ(rG[now]);i++)
	{
		int to=rG[now][i];
		if(!used[to] && to!=mom)dfs(to,now,type);	  
	}
}
int now,nxt;// Rolling in the deep~~hee hee
int dp[2][2*80004];
void go(int x)
{
	for(int i=0;i<=2*n;i++)
	{
		if(dp[now][i])
		{
			if(i-x>=0)dp[nxt][i-x]=1;
			if(i+x<=2*n)dp[nxt][i+x]=1;
		}
	}
	now=!now;nxt=!nxt;
	for(int i=0;i<=2*n;i++)dp[nxt][i]=0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		int suc=0;
		init();
		for(int i=0;i<m;i++)
		{
			int a,b,c;scanf("%d%d%d",&a,&b,&c);
			add_edge(a,b,c);
			if(c)suc++;
		}
		for(int i=0;i<n;i++)
		{
			if(!used[i])
			{
				A=B=0;
				dfs(i,-1,0);
				cnt[abs(A-B)]++;
			}
		}
		memset(dp,0,sizeof(dp));
		now=0,nxt=1;
		dp[now][n]=1;
		for(int i=1;i<=n;i++)
		{
			if(cnt[i])
			{
				for(int j=0;(1<<j)<=cnt[i];j++)
				{
					go((1<<j)*i);
					cnt[i]-=(1<<j);
				}
				if(cnt[i])go(cnt[i]*i);
			}
		}
		int ans=0;
		for(int i=0;i<=n;i++)
		{
			if(dp[now][n-i]||dp[now][n+i])
			{
				int a=(n+i)/2;
				int b=n-a;
				ans=a*b;
				break;
			}
		}
		printf("%d\n",ans-suc);
	}
	return 0;
}
