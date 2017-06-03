#include<cstdio>
#include<vector>
using namespace std;
int N,MOD;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int DIST[100000];
void Dfs(const int u,const int fa,const int cnow)
{
	DIST[u]=cnow;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==fa)continue;
		Dfs(nxt,u,(cnow+e.c)%MOD);
	}
}
int Dist(int d1,int d2){d1=(d1%MOD+MOD)%MOD,d2=(d2%MOD+MOD)%MOD;if(d1<d2)return d2-d1;return d2+MOD-d1;}
void getmin(int &a,const int b){if(b<a)a=b;}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&MOD);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i+1<N;i++)
		{
			scanf("5d%d%d",&a,&b,&c);
			c%=MOD;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		Dfs(0,-1,0);
		sort(DIST,DIST+N);
		int mn=Dist(DIST[N-1],DIST[0]);
		for(int i=1;i<N;i++)getmin(mn,Dist(DIST[i-1],DIST[i]));
		printf("%d\n");
	}
	return 0;
}
