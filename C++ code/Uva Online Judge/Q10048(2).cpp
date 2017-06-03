#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	int To(const int from)const{return from==a?b:a;}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
vector<int>ET[100];
int N,M,Q,DJ[100];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(int a,int b)
{
	if((a=Find(a))==(b=Find(b)))return false;
	DJ[a]=b;
	return true;
}
int ANS[100][100];
bool VIS[100];
void Dfs(const int u,const int epre,vector<int>&rec)
{
	assert(!VIS[u]);VIS[u]=true;
	for(const auto v:rec)ANS[u][v]=ANS[v][u]=max(EDGE[epre].cost,ANS[EDGE[epre].To(u)][v]);
	rec.push_back(u);
	for(const auto ei:ET[u])if(ei!=epre)Dfs(EDGE[ei].To(u),ei,rec);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&Q)==3&&(N||M||Q))
	{
		for(int i=0;i<N;i++)ET[i].clear(),DJ[i]=i;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
		}
		sort(EDGE.begin(),EDGE.end());
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			if(!Merge(e.a,e.b))continue;
			ET[e.a].push_back(i),ET[e.b].push_back(i);
		}
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)ANS[i][j]=INF;
		for(int i=0;i<N;i++)ANS[i][i]=0,VIS[i]=false;
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			vector<int>rec;
			VIS[i]=true;
			rec.push_back(i);
			for(const auto ei:ET[i])Dfs(EDGE[ei].To(i),ei,rec);
		}
		static int kase=0;
		if(kase++)puts("");
		printf("Case #%d\n",kase);
		while(Q--)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			if(ANS[a][b]==INF)puts("no path");
			else printf("%d\n",ANS[a][b]);
		}
	}
	return 0;
}
