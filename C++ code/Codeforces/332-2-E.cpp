#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
int N,M,Q;
LL DP[13][1<<13];//root,s
LL GetDP(const int root,const int s)
{
	assert(s&(1<<root));
	
}
int DJ[13];
int FindDJ(const int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
map<int,int>IDX;
struct Lca
{
	int a,b;
	Lca(){}
	Lca(const int _a,const int _b):a(_a),b(_b){}
};
vector<Lca>LCA[13];
int main()
{
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			assert(FindDJ(a)!=FindDJ(b));
			DJ[FindDJ(a)]=FindDJ(b);
		}
		IDX.clear();
		for(int i=0;i<N;i++)IDX[FindDJ(i)]=-1;
		int cnt=0;
		for(auto &it:IDX)it.second=cnt++;
		for(int i=0;i<N;i++)DJ[i]=IDX[DJ[i]];
		for(int i=0;i<N;i++)LCA[i].clear();
		for(int i=0,a,b,c;i<Q;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--,c--;
			LCA[c].push_back(Lca(a,b));
		}
	}
	return 0;
}
