#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int N,M;
vector<int>ET[1000],UNP[1000];
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(int _a,int _b,int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
void RemoveUnnecessaryEdge()
{
	static int color[1000];
	for(int i=0;i<N;i++)color[i]=-1;
	queue<int>q;
	color[0]=0;q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(color[nxt]!=-1)continue;
			color[nxt]=color[u]^1;
			q.push(nxt);
		}
	}
	for(int i=0;i<N;i++)UNP[i].clear();
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(color[e.a]!=color[e.b])continue;
		UNP[e.a].push_back(i),UNP[e.b].push_back(i);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			if(c==0)ET[a].push_back(b),ET[b].push_back(a);
			else EDGE.push_back(Edge(a,b,c));
		}
		RemoveUnnecessaryEdge();
	}
	return 0;
}
