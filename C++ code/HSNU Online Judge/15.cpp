#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,M,VIS[100][3];
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
vector<Edge>AD[100];
struct Pq
{
	int u,l,c;
	Pq(){}
	Pq(int u,int l,int c):u(u),l(l),c(c){}
	bool operator<(const Pq &p)const{return l>p.l;}
};
int Solve(const int &s)
{
	static int kase=0;kase++;
	VIS[s][0]=VIS[s][1]=kase;
	priority_queue<Pq>pq;
	for(int i=0;i<AD[s].size();i++)
	{
		Edge &e=AD[s][i];
		pq.push(Pq(e.to,e.l,0));
	}
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.u][p.c]==kase)continue;
		VIS[p.u][p.c]=kase;
		if(p.u==s)return p.l;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Edge &e=AD[p.u][i];
			pq.push(Pq(e.to,p.l+e.l,p.c==2?2:p.c+1));
		}
	}
	return INF;
}
int Solve()
{
	int ans=INF;
	for(int i=0;i<N;i++)ans=min(ans,Solve(i));
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)for(int j=0;j<3;j++)VIS[i][j]=0;
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)AD[i].clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			AD[a].push_back(Edge(b,c));
			AD[b].push_back(Edge(a,c));
		}
		int ans=Solve();
		if(ans==INF)puts("No solution.");
		else printf("%d\n",ans);
	}
	return 0;
}
