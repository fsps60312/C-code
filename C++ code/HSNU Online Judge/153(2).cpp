#include<cstdio>
#include<vector>
#include<queue>
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
	vector<int>ANS;
	int VIS[600];
	int Bfs(const int source,const int kase)
	{
		static int dist[600];
		static bool inq[600];
		for(int i=0;i<M;i++)dist[i]=INF,inq[i]=false;
		queue<int>q;
		dist[source]=0,q.push(source),inq[source]=true;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			VIS[u]=kase;
//			printf("u=%d,dist=%d\n",u,dist[u]);
			inq[u]=false;
			for(const Edge &e:EU[u])if(dist[u]+e.cost<dist[e.to])
			{
				dist[e.to]=dist[u]+e.cost;
				if(!inq[e.to])q.push(e.to),inq[e.to]=true;
			}
		}
		int ans=-INF;
		for(int i=0;i<M;i++)if(dist[i]!=INF)getmax(ans,(MX[source]-MN[source])+dist[i]);
		ans++;
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
		for(int i=0;i<M;i++)VIS[i]=-1;
		ANS.clear();
		int cnt=0;
		for(int i=0;i<M;i++)
		{
			if(VIS[i]==-1)VIS[i]=cnt++,ANS.push_back(-INF);
			getmax(ANS[VIS[i]],Bfs(i,VIS[i]));
		}
		int ans=0;
		for(const int v:ANS)ans+=v;
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
