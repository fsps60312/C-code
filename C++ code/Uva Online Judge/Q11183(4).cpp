#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(int to,int cost):to(to),cost(cost){}
};
vector<Edge>RA[1000];
int FA[1000],DJ[1000];
int VIS[1000];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool Dfs(int u,int &ans,int &kase)
{
//	printf("u=%d\n",u);
	if(VIS[u])
	{
		if(VIS[u]!=kase)return false;
		vector<int>cycle;
		cycle.push_back(u);
		for(int i=RA[u][FA[u]].to;i!=u;i=RA[i][FA[i]].to)cycle.push_back(i);
		int mn=INF,i1=-1,i2=-1;
		for(int i=0;i<cycle.size();i++)
		{
			int &d=cycle[i],rc=RA[d][FA[d]].cost;
			for(int j=0;j<RA[d].size();j++)
			{
				Edge &e=RA[d][j];
				if(FindDJ(d)==FindDJ(e.to))continue;
				if(e.cost-rc<mn)mn=e.cost-rc,i1=d,i2=j;
			}
		}
		if(i1==-1)return true;
		ans+=mn;
		FA[i1]=i2;
		int &newfa=RA[i1][i2].to;
		DJ[FindDJ(i1)]=FindDJ(newfa);
		if(!VIS[newfa])Dfs(newfa,ans,kase);
		return false;
	}
	VIS[u]=kase;
	if(FA[u]==-1)return true;
	return Dfs(RA[u][FA[u]].to,ans,kase);
}
int Solve()
{
	for(int i=0;i<N;i++)DJ[i]=i,VIS[i]=0;
	int ans=0,cnt=0;
	for(int i=1;i<N;i++)
	{
		int mn=INF,idx=-1;
		for(int j=0;j<RA[i].size();j++)
		{
			Edge &e=RA[i][j];
			if(e.cost<mn)mn=e.cost,idx=j;
		}
		FA[i]=idx;
		if(idx==-1){cnt++;continue;}
		ans+=mn;
		DJ[FindDJ(i)]=FindDJ(RA[i][idx].to);
	}
	FA[0]=-1;
	if(cnt>1)return -1;
	cnt=0;
	for(int i=0;i<N;i++)
	{
		if(VIS[i])continue;
//		printf("cnt=%d\n",cnt);
		static int kase=0;
		kase++;
		if(Dfs(i,ans,kase))cnt++;
	}
	if(cnt>1)return -1;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<N;i++)
			{
				RA[i].clear();
			}
			for(int i=0;i<M;i++)
			{
				int a,b,c;
				scanf("%d%d%d",&a,&b,&c);
				RA[b].push_back(Edge(a,c));
			}
			static int kase=1;
			printf("Case #%d: ",kase++);
			int ans=Solve();
			if(ans==-1)puts("Possums!");
			else printf("%d\n",ans);
		}
	}
}
