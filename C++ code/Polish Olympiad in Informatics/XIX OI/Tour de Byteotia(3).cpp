#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct DisjointSets
{
	int S[1000000];
	void Clear(const int n){for(int i=0;i<n;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b;return true;}
}DJ;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
int N,M,K;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	DJ.Clear(N);
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		if(a>=K&&b>=K)DJ.Merge(a,b);
		else EDGE.push_back(Edge(a,b));
	}
	vector<Edge>ans;
	for(int i=0;i<(int)EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(!DJ.Merge(e.a,e.b))ans.push_back(e);
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)printf("%d %d\n",ans[i].a+1,ans[i].b+1);
	return 0;
}
