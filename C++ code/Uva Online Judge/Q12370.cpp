#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int T,N,M;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(min(_a,_b)),b(max(_a,_b)){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
};
vector<Edge>EDGE;
int DEG[100];
bool AVAIL[300];
struct Dj
{
	int s[100],n;
	void clear(){n=N;for(int i=0;i<N;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b,n--;return true;}
}DJ[300];
bool Refresh(Dj &dj,vector<int>&trash)
{
	map<Edge,vector<int> >dup;
	for(int ie=0;ie<M;ie++)if(AVAIL[ie])
	{
		const Edge &e=EDGE[ie];
		if(dj.Find(e.a)==dj.Find(e.b))trash.push_back(ie);
		else dup[Edge(dj.Find(e.a),dj.Find(e.b))].push_back(ie);
	}
	bool ans=false;
	for(const auto &it:dup)if(it.second.size()>1)
	{
		ans|=true;
		for(const auto ie:it.second)trash.push_back(ie);
		dj.Merge(EDGE[it.second[0]].a,EDGE[it.second[0]].b);
	}
	for(const int v:trash){assert(AVAIL[v]==true);AVAIL[v]=false;}
	return ans;
}
bool ColorEdge(const int dep)
{
	
}
bool CutEdge(const int dep)
{
	if(DJ[dep].n==1)return false;
	for(int i=0;i<M;i++)if(AVAIL[i])
	{
		AVAIL[i]=false;
		
		AVAIL[i]=true;
	}
}
bool Solve()
{
	for(int i=0;i<M;i++)AVAIL[i]=true;
	vector<int>trash;
	DJ[0].clear();
	while(Refresh(DJ[0],trash));
	return !CutEdge(0);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)DEG[i]=0;
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),EDGE.push_back(Edge(a,b));
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
