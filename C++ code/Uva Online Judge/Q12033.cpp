//don't know why
#include<cstdio>
#include<vector>
using namespace std;
int T,N;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	int To(const int from)const{return from==a?b:a;}
};
vector<Edge>EDGE;
vector<int>ET[1000];
int DIST[1000][1000];
vector<int>REC;
int Dfs(const int u,const int epre)
{
	int sg=0;
	REC.push_back(u);
	for(const auto i:ET[u])if(i!=epre)
	{
		const Edge &e=EDGE[i];
		const int nxt=e.To(u);
		const int nxtsg=Dfs(nxt,i);
		if(e.cost==1)sg^=nxtsg+1;
		else if(e.cost&1)sg^=(nxtsg&1?nxtsg-1:nxtsg+1);
		else sg^=nxtsg;
	}
	REC.pop_back();
	return sg;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear(),DIST[i][i]=0;
		EDGE.clear();
		for(int i=0,a,b,c;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		REC.clear();
		static int kase=1;
		printf("Case %d: %s\n",kase++,Dfs(0,-1)==0?"Jolly":"Emily");
	}
	return 0;
}
