#include<cstdio>
#include<cstdlib>
#include<stack>
#include<vector>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int T,N,M,HEAD[1001],NEXT[50000],PRE[1001],BCC[1001],LOW[1001],PRE_CNT,BCC_CNT,TO[1001],SUM[1001],VIS[1001];
stack<int> SIDE;
vector<int> DAG[1001];
void dfs(int u)
{
	SIDE.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int ti=HEAD[u];ti!=-1;ti=NEXT[ti])
	{
		int i=TO[ti];
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
			HEAD[i]=-1;
			PRE[i]=BCC[i]=SUM[i]=VIS[i]=0;
		}
		for(int i=0;i<M;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			NEXT[i]=HEAD[a];
			HEAD[a]=i;
			TO[i]=b;
		}
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])dfs(i);
			SUM[BCC[i]]++;
		}
		for(int i=1;i<=BCC_CNT;i++)DAG[i].clear();
		for(int i=1;i<=N;i++)
		{
			for(int tj=HEAD[i];tj!=-1;tj=NEXT[tj])
			{
				int j=TO[tj];
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
