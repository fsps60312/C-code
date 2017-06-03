#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
void getmax(int &a,int b){if(b>a)a=b;}
struct Edge{int to,type;};
vector<Edge> EDGE;
struct Vertex
{
	vector<int> to;
	bool have_fa;
	int down,up;
}V[201];
int N,K,ROOT;
void add_EDGE(int from,int to,char type);
void init(int n);
bool read_data();
int get_K(int u)
{
	int ans=1;
	for(int i=0;i<V[u].to.size();i++)
	{
		Edge &e=EDGE[V[u].to[i]];
		if(e.type!=1)continue;
		getmax(ans,get_K(e.to)+1);
	}
	return ans;
}
bool cmp_down(Vertex a,Vertex b){return a.down<b.down;}
bool cmp_up(Vertex a,Vertex b){return a.up<b.up;}
int TARAY[201];
bool dfs_DP(int u,int fa)
{
	V[u].down=V[u].up=0;
	vector<Vertex> sons;
	for(int i=0;i<V[u].to.size();i++)
	{
		Edge &e=EDGE[V[u].to[i]];
		if(e.to==fa)continue;
		dfs_DP(e.to,u);
		if(e.type==1)getmax(V[u].down,V[e.to].down+1);
		else if(e.type==-1)getmax(V[u].up,V[e.to].up+1);
		else sons.push_back(V[e.to]);
	}
	if(sons.size())
	{
		int sz=sons.size();
		sort(sons.begin(),sons.end(),cmp_down);
		int *mx_up=TARAY;
		mx_up[sz-1]=sons[sz-1].up;
		for(int i=sz-2;i>=0;i--)
		{
			mx_up[i]=mx_up[i+1];
			getmax(mx_up[i],sons[i].up);
		}
		bool found=false;
		for(int i=0;i<=sz;i++)
		{
			int tu=V[u].up,td=V[u].down;
			if(i>0)getmax(td,sons[i-1].down+1);
			if(i<sz)getmax(tu,mx_up[i]+1);
			if(tu+td+1<=K)
			{
				getmax(V[u].down,td);
				found=true;
				break;
			}
		}
		if(!found)goto return_false;
		sort(sons.begin(),sons.end(),cmp_up);
		int *mx_down=TARAY;
		mx_down[sz-1]=sons[sz-1].down;
		for(int i=sz-2;i>=0;i--)
		{
			mx_down[i]=mx_down[i+1];
			getmax(mx_down[i],sons[i].down);
		}
		found=false;
		for(int i=0;i<=sz;i++)
		{
			int tu=V[u].up,td=V[u].down;
			if(i>0)getmax(tu,sons[i-1].up+1);
			if(i<sz)getmax(td,mx_down[i]+1);
			if(tu+td+1<=K)
			{
				getmax(V[u].up,tu);
				found=true;
				break;
			}
		}
		if(!found)goto return_false;
	}
	if(V[u].up+V[u].down+1>K)
	{
		return_false:;
		V[u].up=V[u].down=INF;
	}
//	printf("u=%d : %d %d\n",u,V[u].down,V[u].up);
	return V[u].up!=INF;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(read_data())
	{
		for(int i=1;i<=N;i++)getmax(K,get_K(i));
		if(dfs_DP(ROOT,-1))printf("%d\n",K);
		else printf("%d\n",K+1);
	}
	return 0;
}
void add_EDGE(int from,int to,char type)
{
	int t1,t2;
	if(type=='d')t1=1,t2=-1;
	else if(type=='u')t1=-1,t2=1;
	else
	{
		V[from].to.push_back(EDGE.size());
		EDGE.push_back((Edge){to,0});
		return;
	}
	V[from].to.push_back(EDGE.size());
	EDGE.push_back((Edge){to,t1});
	V[to].to.push_back(EDGE.size());
	EDGE.push_back((Edge){from,t2});
}
void init(int n)
{
	while(N<n)
	{
		N++;
		V[N].to.clear();
		V[N].have_fa=false;
	}
}
bool read_data()
{
	int n;
	N=K=0;
	EDGE.clear();
	while(scanf("%d",&n)==1&&n)
	{
		init(n);
		int a;char c;
		while(scanf("%d%c",&a,&c)==2&&a)
		{
			init(a);
			add_EDGE(n,a,c);
			V[a].have_fa=true;
		}
	}
	if(!N)return false;
	for(int i=1;i<=N;i++)
	{
		if(!V[i].have_fa)
		{
			ROOT=i;
			return true;
		}
	}
	termin();
}
