#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _to,const int _cost):to(_to),cost(_cost){}
};
int N,M1,M2;
vector<Edge>ET[600];
bool BellmonFord(int *dists)
{
	static int cnt[600];
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
bool Solve(int *dists)
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
	if(!BellmonFord(dists))return false;
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M1,&M2);
	static int dists[600];
	if(!Solve(dists))puts("NIE");
	else
	{
		int mn=INF,mx=-INF;
		for(int i=0;i<N;i++)
		{
			if(dists[i]<mn)mn=dists[i];
			if(dists[i]>mx)mx=dists[i];
		}
		for(int i=0;i<N;i++)printf("%d ",dists[i]);puts("");
		printf("%d\n",mx-mn+1);
	}
	return 0;
}
