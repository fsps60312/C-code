#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Edge
{
	int nxt;
	bool incycle;
	Edge(){}
	Edge(const int _n,const int _i):nxt(_n),incycle(_i){}
};
vector<Edge>ET[10000];
int CUR[10000],VIS[10000],KASE;
int N,M;
bool Dfs(const int u,const int target)
{
	if(VIS[u])
	{
		if(VIS[u]==1)return false;
		for(int t=ET[u][CUR[u]];;t=ET[t][CUR[t]].nxt)
		{
			ET[t][CUR[t]].vis=true;
			assert(VIS[t]==2);
			VIS[t]=1;
			if(t==u)return true;
		}
	}
	VIS[u]=2;
	bool ans=false;
	for(int &i=CUR[u]=0;i<ET[u].size();i++)
	{
		Edge &e=ET[u][i];
		if(e.vis)continue;
		ans|=true;
		if(!Dfs())
	}
	VIS[u]=false;
	return ans;
}
bool Solve()
{
	 
	for(int i=0;i<N;i++)if(!VIS[i])return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		assert(N>0&&N<=10000);
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=0;
		KASE=2;
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2&&a>=0&&a<N&&b>=0&&b<N);
			ET[a].push_back(Edge(b,false));
		}
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
