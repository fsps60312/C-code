#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
vector<int> TO[1001];
int T,N,S,K,DP[1001][2000];
int getmin(int &a,int b){if(b<a)a=b;}
int max(int a,int b){return a>b?a:b;}
int dfs(int u,int fa,int k)
{
	int &ans=DP[u][k+K];
	if(ans!=-1)return ans;
	if(!TO[u].size()||(TO[u].size()==1&&TO[u][0]==fa))return ans=k>=0?0:1;
	if(k==-K)return ans=dfs(u,fa,K)+1;
	ans=0;
	for(int i=0;i<TO[u].size();i++)
	{
		if(TO[u][i]==fa)continue;
		ans+=dfs(TO[u][i],u,k-1);
	}
	for(int i=0;i<TO[u].size();i++)
	{
		int &a=TO[u][i];
		if(a==fa)continue;
		int c=0;
		for(int j=0;j<TO[u].size();j++)
		{
			int &b=TO[u][j];
			if(b==fa||b==a)continue;
			c+=dfs(b,u,max(k,K-2));
		}
		c+=dfs(a,u,K);
		getmin(ans,c+1);
	}
	if(k<K)getmin(ans,dfs(u,fa,K)+1);
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&S,&K);
		if(K>=N)K=N-1;
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
			for(int j=0;j<=K*2;j++)DP[i][j]=-1;
		}
		for(int i=1;i<N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
			TO[b].push_back(a);
		}
		printf("%d\n",dfs(S,-1,K));
	}
	return 0;
}
