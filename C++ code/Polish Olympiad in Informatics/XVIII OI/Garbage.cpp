#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
struct Edge
{
	int a,b;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b),vis(false){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
void AddEdge(const int a,const int b)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b));
	ET[a].push_back(sz),ET[b].push_back(sz);
}
void Dfs(const int u,vector<int>&path)
{
	for(int i=0;i<(int)ET[u].size();i++)if(!EDGE[ET[u][i]].vis)
	{
		EDGE[ET[u][i]].vis=true;
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		Dfs(nxt,path);
	}
	ET[u].clear();
	path.push_back(u);
}
vector<vector<int> >ANS;
bool Solve()
{
	for(int i=0;i<N;i++)if(ET[i].size()&1)return false;
	ANS.clear();
	for(int i=0;i<N;i++)if(!ET[i].empty())
	{
		vector<int>path;
		Dfs(i,path);
		reverse(path.begin(),path.end());
		ANS.push_back(path);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,f,t;i<M;i++)
		{
			scanf("%d%d%d%d",&a,&b,&f,&t),a--,b--;
			if(t<f)t+=2;
			for(int j=0;j<t-f;j++)AddEdge(a,b);
		}
		if(!Solve())puts("NIE");
		else
		{
			printf("%d\n",(int)ANS.size());
			for(int i=0;i<(int)ANS.size();i++)
			{
				printf("%d",(int)ANS[i].size()-1);
				for(int j=0;j<(int)ANS[i].size();j++)printf(" %d",ANS[i][j]+1);
				puts("");
			}
		}
	}
	return 0;
}
