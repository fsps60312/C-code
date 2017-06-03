#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _to,const int _cost):to(_to),cost(_cost){}
};
int N,M1,M2;
vector<Edge>ET[600];
bool BellmonFord()
{
	static int cnt[600],dists[600];
	static bool inq[600];
	for(int i=0;i<N;i++)dists[i]=0,cnt[i]=0,inq[i]=false;
	queue<int>q;
	for(int i=0;i<N;i++)q.push(i),inq[i]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();inq[u]=false;
		if(++cnt[u]>N)return false;
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i].to;
			const int dist=dists[u]+ET[u][i].cost;
			if(dist>dists[nxt])
			{
				dists[nxt]=dist;
				if(!inq[nxt])q.push(nxt),inq[nxt]=true;
			}
		}
	}
	return true;
}
bool Solve()
{
	for(int i=0,a,b;i<M1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(Edge(b,1)),ET[b].push_back(Edge(a,-1));
	}
	for(int i=0,a,b;i<M2;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(Edge(b,0));
	}
	if(!BellmonFord())return false;
	return true;
}
int PRE[600],PRE_CNT,BCC_CNT;
int BCC_IDX[600];
vector<int>BCC[600];
vector<int>STK;
int Dfs(const int u)
{
	STK.push_back(u);
	int low=PRE[u]=++PRE_CNT;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i].to;
		if(!PRE[nxt])getmin(low,Dfs(nxt));
		else if(BCC_IDX[nxt]==-1)getmin(low,PRE[nxt]);
	}
	if(low==PRE[u])
	{
		BCC[BCC_CNT].clear();
		for(;;)
		{
			const int v=STK.back();STK.pop_back();
			BCC[BCC_CNT].push_back(v);
			BCC_IDX[v]=BCC_CNT;
			if(v==u)break;
		}
		BCC_CNT++;
	}
	return low;
}
int Solve(const vector<int>&s)
{
	const int n=s.size();
	static int dist[600][600],id[600];
	for(int i=0;i<n;i++)id[s[i]]=i;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)dist[i][j]=-INF;
	for(int i=0;i<n;i++)dist[i][i]=0;
	for(int i=0;i<(int)s.size();i++)
	{
		for(int j=0;j<(int)ET[s[i]].size();j++)
		{
			const Edge &e=ET[s[i]][j];
			if(BCC_IDX[s[i]]==BCC_IDX[e.to])dist[i][id[e.to]]=e.cost;
		}
	}
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)if(dist[i][k]!=-INF)
		{
			for(int j=0;j<n;j++)if(dist[k][j]!=-INF)
			{
				getmax(dist[i][j],dist[i][k]+dist[k][j]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)assert(dist[i][j]!=-INF),getmax(ans,-dist[i][j]);
//	for(int i=0;i<n;i++)printf("%d ",s[i]);
//	printf("ans=%d\n",ans);
	return ans+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M1,&M2);
	if(!Solve())puts("NIE");
	else
	{
		for(int i=0;i<N;i++)PRE[i]=0,BCC_IDX[i]=-1;
		PRE_CNT=BCC_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
		int ans=0;
		for(int i=0;i<BCC_CNT;i++)ans+=Solve(BCC[i]);
		printf("%d\n",ans);
	}
	return 0;
}
