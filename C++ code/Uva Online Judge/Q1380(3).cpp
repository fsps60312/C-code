#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
const int INF=1<<30;
struct Edge
{
	int from,to,type;
};
vector<Edge> EDGE;
vector<int> GETO[201];
int N,K,GN,G[201];
void init(int n)
{
	while(N<n)
	{
		N++;
		GETO[N].clear();
		G[N]=-1;
	}
}
void add_EDGE(int from,int to,char type)
{
	int t1,t2;
	if(type=='d')t1=1,t2=-1;
	else if(type=='u')t1=-1,t2=1;
	else t1=t2=0;
	GETO[from].push_back(EDGE.size());
	EDGE.push_back((Edge){from,to,t1});
	GETO[to].push_back(EDGE.size());
	EDGE.push_back((Edge){to,from,t2});
}
struct Point{int x,y;};
vector<Point> DEP[201];
void dfs_G(int u,int fa,int dep)
{
	G[u]=GN;
	DEP[GN].push_back((Point){u,dep});
	for(int i=0;i<GETO[u].size();i++)
	{
		Edge &e=EDGE[GETO[u][i]];
		if(e.to==fa||e.type==0||G[e.to]!=-1)continue;
		dfs_G(e.to,u,dep+e.type);
	}
}
int GL[201],D[201];
vector<int> LEV;
int main()
{
	freopen("in.txt","r",stdin);
	while(1)
	{
		int n;
		N=0;
		EDGE.clear();
		while(scanf("%d",&n)==1&&n)
		{
			init(n);
			int a;char c;
			while(scanf("%d%c",&a,&c)==2&&a){init(a);add_EDGE(n,a,c);}
		}
		if(!N)break;
		GN=0;
		for(int i=1;i<=N;i++)
		{
			if(G[i]!=-1)continue;
			DEP[GN].clear();
			dfs_G(i,-1,0);
			GN++;
		}
		int K=0;
		for(int i=0;i<GN;i++)
		{
			int low=INF,up=-INF;
			for(int j=0;j<DEP[i].size();j++)
			{
				getmin(low,DEP[i][j].y);
				getmax(up,DEP[i][j].y);
			}
			GL[i]=up-low;
			getmax(K,GL[i]);
			for(int j=0;j<DEP[i].size();j++)
			{
				Point &p=DEP[i][j];
				D[p.x]=p.y-low;
			}
		}
		bool found=true;
		for(int i=0;i<EDGE.size();i++)
		{
			Edge &e=EDGE[i];
			if(e.type!=0)continue;
			if(GL[G[e.from]]!=K||GL[G[e.to]]!=K)continue;
			if(D[G[e.from]]==D[G[e.to]])
			{
				found=false;
				break;
			}
		}
		for(int i=1;i<=N;i++)printf("D[%d] : %d\n",i,D[i]);
		printf("%d\n",found?K+1:K+2);
	}
	return 0;
}
