#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,ID[600],H[600];
vector<int>MN,MX,SZ;
struct Solver1
{
	vector<int>EU[600],ED[600];
	bool Dfs(const int u,const int h,int &mn,int &mx)
	{
		if(H[u]!=INF)return H[u]==h;
		getmin(mn,h),getmax(mx,h);
		SZ[ID[u]=M]++,H[u]=h;
		for(const int nxt:EU[u])if(!Dfs(nxt,h+1,mn,mx))return false;
		for(const int nxt:ED[u])if(!Dfs(nxt,h-1,mn,mx))return false;
		return true;
	}
	bool Initialize(const int m)
	{
		for(int i=0;i<N;i++)EU[i].clear(),ED[i].clear();
		MN.clear(),MX.clear();
		for(int i=0,a,b;i<m;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			EU[a].push_back(b),ED[b].push_back(a);
		}
		for(int i=0;i<N;i++)ID[i]=-1,H[i]=INF;
		M=0;
		MN.clear(),MX.clear(),SZ.clear();
		for(int i=0;i<N;i++)if(ID[i]==-1)
		{
			int mn=INF,mx=-INF;
			SZ.push_back(0);
			if(!Dfs(i,0,mn,mx))return false;
			MN.push_back(mn),MX.push_back(mx);
			M++;
		}
		return true;
	}
}SOLVER1;
struct Solver2
{
	struct Edge
	{
		int to,cost;
		Edge(){}
		Edge(const int _t,const int _c):to(_t),cost(_c){}
	};
	vector<Edge>EU[600];
	int PRE[600],LOW[600],PRE_CNT,DIST[600];
	bool VIS[600],INQ[600];
	vector<vector<int> >NODE;
	stack<int>STK;
	void Dfs(const int u)
	{
		PRE[u]=LOW[u]=++PRE_CNT;
		STK.push(u);
		for(const Edge &e:EU[u])
		{
			if(!PRE[e.to])Dfs(e.to),getmin(LOW[u],LOW[e.to]);
			else if(!VIS[e.to])getmin(LOW[u],PRE[e.to]);
		}
		if(LOW[u]==PRE[u])
		{
			vector<int>node;
			for(;;)
			{
				const int v=STK.top();STK.pop();
				VIS[v]=true;
				node.push_back(v);
				if(v==u)break;
			}
			NODE.push_back(node);
		}
	}
	bool Bfs(const int source)
	{
		queue<int>q;
		DIST[source]=0;
		q.push(source),INQ[source]=true;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			if(DIST[source]<0)return false;
			for(const Edge &e:EU[u])if(DIST[u]+e.cost<DIST[e.to])
			{
				DIST[e.to]=DIST[u]+e.cost;
				if(!INQ[e.to])q.push(e.to),INQ[e.to]=true;
			}
		}
		return true;
	}
	int Bfs(const vector<int>&nodes)
	{
		for(int i=0;i<M;i++)INQ[i]=true;
		int ans=-1;
		for(const int source:nodes)
		{
			for(const int v:nodes)DIST[v]=INF,INQ[v]=false;
			if(!Bfs(source))return -1;
			int result=-INF;
			for(const int v:nodes)getmax(result,(MX[source]-MN[source])+DIST[v]);
			result++;
			getmax(ans,result);
		}
		return ans;
	}
	int Solve(const int m2)
	{
		for(int i=0;i<M;i++)EU[i].clear();
		for(int i=0,a,b;i<m2;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			const int ha=H[a]-MN[ID[a]],hb=H[b]-MN[ID[b]];
			if(ID[a]==ID[b])
			{
				if(ha>hb)return -1;
			}
			else EU[ID[a]].push_back(Edge(ID[b],hb-ha));//,printf("(%d,%d)%d\n",ID[a],ID[b],hb-ha);
		}
		for(int i=0;i<M;i++)PRE[i]=0,VIS[i]=false;
		PRE_CNT=0;
		NODE.clear();
		for(int i=0;i<M;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
		int ans=0;
		for(const vector<int>&nodes:NODE)
		{
			const int result=Bfs(nodes);
			if(result==-1)return -1;
			ans+=result;
		}
		return ans;
	}
}SOLVER2;
int Solve(const int m1,const int m2)
{
	if(!SOLVER1.Initialize(m1))return -1;
	return SOLVER2.Solve(m2);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int m1,m2;
	scanf("%d%d%d",&N,&m1,&m2);
	const int ans=Solve(m1,m2);
	if(ans==-1)puts("NIE");
	else printf("%d\n",ans);
	return 0;
}
