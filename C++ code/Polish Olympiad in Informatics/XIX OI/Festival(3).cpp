#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _to,const int _cost):to(_to),cost(_cost){}
};
int N,M1,M2,DISTS[600];
vector<Edge>ET[600];
bool BellmonFord()
{
	static int cnt[600];
	static bool inq[600];
	for(int i=0;i<N;i++)DISTS[i]=0,cnt[i]=0,inq[i]=false;
	queue<int>q;
	for(int i=0;i<N;i++)q.push(i),inq[i]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();inq[u]=false;
		if(++cnt[u]>N)return false;
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i].to;
			const int dist=DISTS[u]+ET[u][i].cost;
			if(dist>DISTS[nxt])
			{
				DISTS[nxt]=dist;
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
bool CATAGORIZED[600];
vector<int>BCC[600];
vector<int>STK;
int Dfs(const int u,const int parent)
{
	STK.push_back(u);
	int low=PRE[u]=++PRE_CNT;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i].to;
		if(nxt==parent)continue;
		if(!PRE[nxt])getmin(low,Dfs(nxt,u));
		else if(!CATAGORIZED[nxt])getmin(low,PRE[nxt]);
	}
	if(low==PRE[u])
	{
		BCC[BCC_CNT].clear();
		for(;;)
		{
			const int v=STK.back();STK.pop_back();
			BCC[BCC_CNT].push_back(v);
			CATAGORIZED[v]=true;
			if(v==u)break;
		}
		BCC_CNT++;
	}
	return low;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M1,&M2);
	if(!Solve())puts("NIE");
	else
	{
		for(int i=0;i<N;i++)PRE[i]=0,CATAGORIZED[i]=false;
		PRE_CNT=BCC_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),assert(STK.empty());
		int ans=0;
		for(int i=0;i<BCC_CNT;i++)
		{
			int mn=INF,mx=-INF;
			for(int j=0;j<(int)BCC[i].size();j++)
			{
				const int h=DISTS[BCC[i][j]];
				if(h<mn)mn=h;
				if(h>mx)mx=h;
			}
			ans+=mx-mn+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
