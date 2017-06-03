#include<cstdio>
#include<cstdlib>
#include<stack>
#include<vector>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int T,N,M,PRE[1001],BCC[1001],LOW[1001],PRE_CNT,BCC_CNT,SUM[1001],VIS[1001];
stack<int> SIDE;
vector<int> DAG[1001],TO[1001];
void dfs(int u)
{
	SIDE.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int ti=0;ti<TO[u].size();ti++)
	{
		int i=TO[u][ti];
		if(!PRE[i])
		{
			dfs(i);
			LOW[u]=min(LOW[u],LOW[i]);
		}
		else if(!BCC[i])LOW[u]=min(LOW[u],PRE[i]);
	}
	if(LOW[u]==PRE[u])
	{
		BCC_CNT++;
		for(;;)
		{
			int v=SIDE.top();SIDE.pop();
			BCC[v]=BCC_CNT;
			if(v==u)break;
		}
	}
}
int dfsans(int u)
{
	if(VIS[u])return SUM[u];
	VIS[u]=true;
	int ans=0;
	for(int i=0;i<DAG[u].size();i++)
	{
		ans=max(ans,dfsans(DAG[u][i]));
	}
	return SUM[u]=SUM[u]+ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(!SIDE.empty())SIDE.pop();
	while(T--)
	{
		PRE_CNT=BCC_CNT=0;
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
		{
			PRE[i]=BCC[i]=SUM[i]=VIS[i]=0;
			TO[i].clear();
		}
		for(int i=0;i<M;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
		}
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])dfs(i);
			SUM[BCC[i]]++;
		}
		for(int i=1;i<=BCC_CNT;i++)DAG[i].clear();
		for(int i=1;i<=N;i++)
		{
			for(int tj=0;tj<TO[i].size();tj++)
			{
				int j=TO[i][tj];
				if(BCC[i]!=BCC[j])DAG[BCC[i]].push_back(BCC[j]);
			}
		}
		int ans=0;
		for(int i=1;i<=BCC_CNT;i++)
		{
			ans=max(ans,dfsans(i));
		}
		printf("%d\n",ans);
	}
	return 0;
}
