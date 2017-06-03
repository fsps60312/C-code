#include<cstdio>
#include<vector>
#include<map>
using namespace std;
void assert(bool valid){if(valid)return;int a=0,b=0;a/=b;}
int N,M;
struct Dj
{
	int s[10],n;
	void clear(const int _n){n=_n;for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b,n--;return true;}
}DJ;
int ET[100],TET[100];
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
bool Merge(int *et,int &n)
{
	DJ.clear(n);
	bool result=false;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(et[i*n+j]>1)if(DJ.Merge(i,j))result=true;
	if(!result)return false;
	map<int,int>idx;
	for(int i=0;i<n;i++)idx[DJ.Find(i)]=-1;
	int cnt=0;
	for(auto &it:idx)it.second=cnt++;
	for(int i=0;i<n;i++)DJ.s[i]=idx[DJ.s[i]];
	int tn=DJ.n;
	for(int i=0;i<tn*tn;i++)TET[i]=0;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(DJ.s[i]!=DJ.s[j])
	{
		TET[DJ.s[i]*tn+DJ.s[j]]+=et[i*n+j];
		TET[DJ.s[j]*tn+DJ.s[i]]+=et[i*n+j];
	}
	n=tn;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)et[i*n+j]=TET[i*n+j];
	return true;
}
Dj TMP[31];
map<int,bool>DP[31];
bool ColorEdge(const int dep,const int s);
bool CutEdge(const int dep,const int s)
{
	auto it=DP[dep].find(s);
	if(it!=DP[dep].end())return it->second;
	if(TMP[dep].n==1)return DP[dep][s]=false;
	for(int i=0;(1<<i)<=s;i++)if(s&(1<<i)&&TMP[dep].Find(EDGE[i].a)!=TMP[dep].Find(EDGE[i].b))
	{
		TMP[dep+1]=TMP[dep];
		if(!ColorEdge(dep+1,s-(1<<i)))return DP[dep][s]=true;
	}
	return DP[dep][s]=false;
}
bool ColorEdge(const int dep,const int s)
{
	auto it=DP[dep].find(s);
	if(it!=DP[dep].end())return it->second;
	for(int i=0;(1<<i)<=s;i++)if(s&(1<<i)&&TMP[dep].Find(EDGE[i].a)!=TMP[dep].Find(EDGE[i].b))
	{
		TMP[dep+1]=TMP[dep];
		assert(TMP[dep+1].Merge(EDGE[i].a,EDGE[i].b));
		if(!CutEdge(dep+1,s-(1<<i)))return DP[dep][s]=true;
	}
	return DP[dep][s]=false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&!(N==-1&&M==-1))
	{
		for(int i=0;i<N*N;i++)ET[i]=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			if(a!=b)ET[a*N+b]++,ET[b*N+a]++;
		}
		while(Merge(ET,N));
		EDGE.clear();
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(ET[i*N+j])EDGE.push_back(Edge(i,j));
		assert(EDGE.size()<=30);
		for(int i=0;i<=EDGE.size();i++)DP[i].clear();
		TMP[0].clear(N);
		puts(CutEdge(0,(1<<EDGE.size())-1)?"NO":"YES");
	}
	return 0;
}
