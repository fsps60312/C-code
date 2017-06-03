#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int T,N,M;
vector<int>AD[100];
struct Edge
{
	int a,b,cost;
	bool enable;
	Edge(){}
	Edge(int a,int b,int cost):a(a),b(b),cost(cost),enable(false){}
	int To(int from){return from!=a?a:b;}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
int DJ[100];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
int FindSpanTree1()
{
	for(int i=0;i<N;i++)DJ[i]=i;
	int ans=0,cnt=N;
	for(int i=0;i<M;i++)
	{
		int &a=EDGE[i].a,&b=EDGE[i].b;
//		printf("C(%d,%d)\n",a,b);
//		printf("F(%d,%d)\n",FindDJ(a),FindDJ(b));
		if(FindDJ(a)==FindDJ(b))continue;
		EDGE[i].enable=true;
		ans+=EDGE[i].cost;
		DJ[FindDJ(a)]=FindDJ(b);
//		AD[a].push_back(i);
//		AD[b].push_back(i);
		if(--cnt==1)break;
	}
//	printf("cnt==%d\n",cnt);
	assert(cnt==1);
	return ans;
}
int CNT;
bool Dfs(int fa,int u,int t,int &ans)
{
	if(CNT++>N){assert(0);}
	if(u==t)
	{
		ans=-INF;
		return true;
	}
	for(int i=0;i<AD[u].size();i++)
	{
		Edge &e=EDGE[AD[u][i]];
		int nx=e.To(u);
		if(!e.enable||nx==fa)continue;
		if(Dfs(u,nx,t,ans))
		{
			ans=max(ans,e.cost);
			return true;
		}
	}
	return false;
}
int FindSpanTree2(int a1)
{
	int ans=INF;
	for(int i=0;i<M;i++)
	{
		if(EDGE[i].enable)continue;
		static int mx;
		CNT=0;
		assert(Dfs(-1,EDGE[i].a,EDGE[i].b,mx));
		ans=min(ans,a1+EDGE[i].cost-mx);
	}
	assert(ans!=INF);
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
//			printf("N=%d,M=%d\n",N,M);
			EDGE.clear();
			for(int i=0;i<M;i++)
			{
				static int a,b,c,sz;
				scanf("%d%d%d",&a,&b,&c);
				EDGE.push_back(Edge(--a,--b,c));
			}
			sort(EDGE.begin(),EDGE.end());
			for(int i=0;i<N;i++)AD[i].clear();
			for(int i=0;i<M;i++)
			{
				int &a=EDGE[i].a,&b=EDGE[i].b;
				AD[a].push_back(i);
				AD[b].push_back(i);
			}
			int a1=FindSpanTree1();
			int a2=FindSpanTree2(a1);
			printf("%d %d\n",a1,a2);
		}
	}
	return 0;
}
