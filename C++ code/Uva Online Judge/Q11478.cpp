#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int V,E;
struct Edge
{
	int to,d;
};
vector<Edge> VER[501];
//vector<Edge> CMP[501];
bool INQ[501];
int CNT[501];
int BEST[501];
bool negacycle(int d)
{
	queue<int> q;
	for(int i=1;i<=V;i++)
	{
		q.push(i);
		INQ[i]=true;
		BEST[i]=0;
		CNT[i]=0;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<VER[u].size();i++)
		{
			Edge &e=VER[u][i];
			if(BEST[u]+e.d-d>=BEST[e.to])continue;
			BEST[e.to]=BEST[u]+e.d-d;
			if(++CNT[e.to]>V)return true;
			if(INQ[e.to])continue;
			q.push(e.to);
			INQ[e.to]=true;
		}
	}
	return false;
}
int solve(int up)
{
	int down=1;
	while(down<up)
	{
		int mid=(down+up)/2;
		if(!negacycle(mid))down=mid+1;
		else up=mid;
	}
	return up-1;
}
int main()
{
	while(scanf("%d%d",&V,&E)==2)
	{
		for(int i=1;i<=V;i++)
		{
			VER[i].clear();
			//CMP[i].clear();
		}
		int up=0;
		for(int i=0;i<E;i++)
		{
			int u,v,d;scanf("%d%d%d",&u,&v,&d);
			VER[u].push_back((Edge){v,d});
			//CMP[v].push_back((Edge){u,-d});
			if(d>up)up=d;
		}
		if(!negacycle(up+1))printf("Infinite\n");
		else if(negacycle(1))printf("No Solution\n");
		else printf("%d\n",solve(up));
	}
	return 0;
}
