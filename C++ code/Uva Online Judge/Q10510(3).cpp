#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int nxt,cnt;
	Edge(){}
	Edge(const int _n,const int _c):nxt(_n),cnt(_c){}
};
vector<Edge>ET[10000];
int CUR[10000];
bool VIS[10000];
int N,M;
bool Dfs(const int u)
{
	if(CUR[u]!=-1)
	{
		for(int t=ET[u][CUR[u]].nxt;;t=ET[t][CUR[t]].nxt)
		{
			ET[t][CUR[t]].cnt++;
			if(t==u)break;
		}
		return true;
	}
	if(VIS[u])return false;
	VIS[u]=true;
	for(int &i=CUR[u]=0;i<(int)ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		if(!Dfs(e.nxt))return false;
	}
	CUR[u]=-1;
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)CUR[i]=-1,VIS[i]=false;
	if(!Dfs(0))return false;
	for(int i=1;i<N;i++)if(!VIS[i])return false;
	for(int i=0;i<N;i++)for(const Edge &e:ET[i])if(e.cnt!=1)return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		assert(N>0&&N<=10000);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2&&a>=0&&a<N&&b>=0&&b<N);
			ET[a].push_back(Edge(b,0));
		}
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
