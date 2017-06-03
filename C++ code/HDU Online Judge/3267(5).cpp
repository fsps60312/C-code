#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;int a=0,b=0;for(;;)a/=b;}
int N,M;
struct Dj
{
	int s[10];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
}DJ[31];
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
map<int,bool>DP[31];
bool Connect(const int s,const Dj &_dj)
{
	static Dj dj;
	dj=_dj;
	for(int i=0;i<EDGE.size();i++)if(s&(1<<i))dj.Merge(EDGE[i].a,EDGE[i].b);
	for(int i=1;i<N;i++)if(dj.Find(0)!=dj.Find(i))return false;
	return true;
}
bool ColorEdge(const int dep,const int s);
bool CutEdge(const int dep,const int s)
{
	auto it=DP[dep].find(s);
	if(it!=DP[dep].end())return it->second;
	if(!Connect(s,DJ[dep]))return DP[dep][s]=true;
	for(int i=0;i<EDGE.size();i++)if(s&(1<<i))
	{
		DJ[dep+1]=DJ[dep];
		if(!ColorEdge(dep+1,s-(1<<i)))return DP[dep][s]=true;
	}
	return DP[dep][s]=false;
}
vector<int>EI[10][10];
bool Merge(int &s,Dj &dj)
{
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)EI[i][j].clear();
	for(int i=0;i<EDGE.size();i++)if(s&(1<<i))
	{
		const int a=dj.Find(EDGE[i].a),b=dj.Find(EDGE[i].b);
		if(a==b)s-=(1<<i);
		else EI[min(a,b)][max(a,b)].push_back(i);
	}
	bool ans=false;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(EI[i][j].size()>1)
	{
		for(const auto v:EI[i][j])assert(s&(1<<v)),s-=(1<<v);
		dj.Merge(i,j);
		ans|=true;
	}
	return ans;
}
bool ColorEdge(const int dep,const int s)
{
	auto it=DP[dep].find(s);
	if(it!=DP[dep].end())return it->second;
	if(!Connect(s,DJ[dep]))return DP[dep][s]=false;
	for(int i=0;i<EDGE.size();i++)if(s&(1<<i))
	{
		DJ[dep+1]=DJ[dep];
		assert(DJ[dep+1].Merge(EDGE[i].a,EDGE[i].b));
		int nxts=s-(1<<i);
		while(Merge(nxts,DJ[dep+1]));
		if(!CutEdge(dep+1,nxts))return DP[dep][s]=true;
	}
	return DP[dep][s]=false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&!(N==-1&&M==-1))
	{
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			EDGE.push_back(Edge(a,b));
		}
		int s=(1<<EDGE.size())-1;
		DJ[0].clear(N);
		while(Merge(s,DJ[0]));
		for(int i=0;i<=EDGE.size();i++)DP[i].clear();
		puts(CutEdge(0,s)?"NO":"YES");
	}
	return 0;
}
