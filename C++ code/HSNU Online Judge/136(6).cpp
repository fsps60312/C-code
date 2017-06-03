#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
const int INF=2147483647;
int N,M,SUM;
vector<int>ET[1000];
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(int _a,int _b,int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
void RemoveUnnecessaryEdge()
{
	static int color[1000];
	for(int i=0;i<N;i++)color[i]=-1;
	queue<int>q;
	color[0]=0,q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(color[nxt]!=-1)assert(color[nxt]==color[u]^1);
			else color[nxt]=color[u]^1,q.push(nxt);
		}
	}
	vector<Edge>edge;
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(color[e.a]!=color[e.b])continue;
		edge.push_back(e);
	}
	EDGE.swap(edge);
}
int BRANCH[1000];
void SetBRANCH(const int u,const int fa,const int branch)
{
	BRANCH[u]=branch;
	for(int i=0;i<ET[u].size();i++)if(ET[u][i]!=fa)SetBRANCH(ET[u][i],u,branch);
}
void SearchBRANCH(const int u,const int upward)
{
	BRANCH[u]=upward;
	for(int i=0;i<ET[u].size();i++)SetBRANCH(ET[u][i],u,i);
}
int DP[1000][1<<10],MX[1000],CNT[1000],NOW[1000];
void InitDP(const int u,const int fa,const int upward)
{
	for(int i=0;i<(1<<CNT[u]);i++)DP[u][i]=0;
//	int &dp=DP[u][(1<<CNT[u])-1-(1<<upward)]=0;
	int &mx=MX[u]=0;
	for(int i=0;i<ET[u].size();i++)if(i!=upward)mx+=MX[ET[u][i]];
//	MX[u]=dp;
}
void BuildDP(const int u,const int fa)
{
	int upward=-1;
	for(int i=0;i<ET[u].size();i++)
		if(ET[u][i]!=fa)BuildDP(ET[u][i],u);
		else upward=i;
	SearchBRANCH(u,upward);
	InitDP(u,fa,upward);
	const int limit=(1<<CNT[u])-1;
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		const int ba=BRANCH[e.a],bb=BRANCH[e.b];
		if(ba==bb||(ba==upward&&e.a!=u)||(bb==upward&&e.b!=u))continue;
		if(ba==upward)getmax(DP[u][1<<bb],e.cost+NOW[e.b]);
		else if(bb==upward)getmax(DP[u][1<<ba],e.cost+NOW[e.a]);
		else
		{
			int ta=e.cost+NOW[e.a]+NOW[e.b];
			getmax(DP[u][(1<<ba)+(1<<bb)],ta);
		}
	}
	for(int s=1;s<=limit;s++)
	{
		if(s&(1<<upward))continue;
		for(int a=(s-1)&s,b;a;a=(a-1)&s)
		{
			b=s^a;
			getmax(DP[u][s],DP[u][a]+DP[u][b]);
		}
		getmax(MX[u],DP[u][s]);
	}
	NOW[u]=DP[u][limit-(1<<upward)];
	for(int i=0;i<N;i++)if(BRANCH[i]!=upward)NOW[i]+=DP[u][limit-(1<<upward)-(1<<BRANCH[i])];
}
int Solve()
{
	RemoveUnnecessaryEdge();
	BuildDP(0,-1);
	return SUM-MX[0];
}
int main()
{
//	printf("%d %d %d\n",4<<-1,4<<-2,4<<-3);
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),CNT[i]=0;
		EDGE.clear();
		SUM=0;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			if(c)EDGE.push_back(Edge(a,b,c));
			else ET[a].push_back(b),ET[b].push_back(a),CNT[a]++,CNT[b]++;
			SUM+=c;
		}
		printf("%d\n",Solve());
//		break;
	}
	return 0;
}
