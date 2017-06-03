#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<stack>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M;
int PRE[100000],PRE_CNT,LOW[100000],BCC[100000],BCC_CNT;
vector<int>TO[100000];
stack<int>STK;
void dfs(int u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!PRE[j])
		{
			dfs(j);
			getmin(LOW[u],LOW[j]);
		}
		else if(BCC[j]<0)
		{
			getmin(LOW[u],PRE[j]);
		}
	}
	if(LOW[u]==PRE[u])
	{
		while(STK.top()!=u)
		{
			BCC[STK.top()]=BCC_CNT;
			STK.pop();
		}
		BCC[STK.top()]=BCC_CNT;
		STK.pop();
		BCC_CNT++;
	}
}
int solve()
{
	for(int i=0;i<N;i++)if(!PRE[i])dfs(i);
	for(int i=0;i<BCC_CNT;i++)PRE[i]=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<TO[i].size();j++)
		{
			int &k=TO[i][j];
			if(BCC[i]==BCC[k])continue;
			PRE[BCC[k]]++;
		}
	}
	int ans=0;
	for(int i=0;i<BCC_CNT;i++)if(!PRE[i])ans++;
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			PRE[i]=0;
			BCC[i]=-1;
		}
		PRE_CNT=BCC_CNT=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			TO[a].push_back(b);
		}
		int ans=solve();
		printf("%d\n",ans);
	}
	return 0;
}
