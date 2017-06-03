#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,c;
	bool tag;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c):a(_a),b(_b),c(_c),tag(false){}
};
vector<Edge>EDGE;
vector<int>ET[7000];
vector<int>FA[7000],MX[7000];
int DEP[7000];
void Dfs(const int &u,const int &fa,const int &dep,const int &len)
{
	DEP[u]=dep;
	if(fa!=-1)
	{
		FA[u].push_back(fa);
		MX[u].push_back(len);
		int o=fa,mx=len;
		for(int i=0;i<FA[o].size();i++)
		{
			mx=max(mx,MX[o][i]);
			MX[u].push_back(mx);
			FA[u].push_back(FA[o][i]);
			o=FA[o][i];
		}
	}
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int &nxt=(e.a==u?e.b:e.a);
		if(nxt==fa)continue;
		Dfs(nxt,u,dep+1,e.c);
	}
}
int GetMX(int a,int b)
{
	if(DEP[b]<DEP[a])swap(a,b);
	int ans=-INF;
	if(DEP[a]<DEP[b])
	{
		int dis=DEP[b]-DEP[a];
		for(int i=0;dis;i++)
		{
			if(!(dis&(1<<i)))continue;
			ans=max(ans,MX[b][i]);
			b=FA[b][i];
			dis&=~(1<<i);
		}
		assert(DEP[a]==DEP[b]);
	}
	while(a!=b)
	{
		int i=0;
		for(;i+1<FA[a].size()&&FA[a][i+1]!=FA[b][i+1];i++);
		ans=max(ans,max(MX[a][i],MX[b][i]));
		a=FA[a][i],b=FA[b][i];
	}
	assert(a==b);
	return ans;
}
int DJ[7000],IDX[300000];
bool cmp_edgeidx(const int &a,const int &b){return EDGE[a].c<EDGE[b].c;}
int FindDJ(const int &a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
void Solve()
{
	for(int i=0;i<M;i++)IDX[i]=i;
	sort(IDX,IDX+M,cmp_edgeidx);
//	for(int i=0;i<M;i++)printf(" %d",IDX[i]);puts("");
	for(int i=0;i<N;i++)DJ[i]=i,ET[i].clear();
	int cnt=N;
	for(int i=0;i<M&&cnt>1;i++)
	{
		Edge &e=EDGE[IDX[i]];
		int a=FindDJ(e.a),b=FindDJ(e.b);
		if(a==b)continue;
		DJ[a]=b;
		cnt--;
		e.tag=true;
//		printf("%d,(%d,%d)\n",IDX[i],e.a+1,e.b+1);
		ET[e.a].push_back(IDX[i]);
		ET[e.b].push_back(IDX[i]);
	}
	if(cnt!=1)
	{
		assert(0);
		for(int i=0;i<M;i++)EDGE[i].tag=false;
		return;
	}
	else
	{
		for(int i=0;i<N;i++)FA[i].clear(),MX[i].clear();
		Dfs(0,-1,0,-INF);
		for(int i=0;i<M;i++)
		{
			Edge &e=EDGE[i];
			if(e.tag)continue;
			int mx=GetMX(e.a,e.b);
			if(mx==e.c)e.tag=true;
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
		}
		Solve();
		for(int i=0;i<M;i++)puts(EDGE[i].tag?"TAK":"NIE");
	}
	return 0;
}
