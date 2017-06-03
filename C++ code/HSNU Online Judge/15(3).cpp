#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
vector<Edge>AD[100];
struct Pq
{
	int u,l;
	Pq(){}
	Pq(int u,int l):u(u),l(l){}
	bool operator<(const Pq &p)const{return l>p.l;} 
};
int VIS[100],D[100];
int Solve(int s)
{
	static int kase=0;
	int ans=INF;
	for(int i=0;i<AD[s].size();i++)
	{
		Edge &e=AD[s][i];
		priority_queue<Pq>pq;
		pq.push(Pq(e.to,e.l));
		kase++;
		VIS[s]=kase;
		while(!pq.empty())
		{
			Pq p=pq.top();pq.pop();
			if(VIS[p.u]==kase)continue;
			VIS[p.u]=kase;
			D[p.u]=p.l;
			for(int j=0;j<AD[p.u].size();j++)
			{
				Edge &ee=AD[p.u][j];
				pq.push(Pq(ee.to,p.l+ee.l));
			}
		}
		for(int j=i+1;j<AD[s].size();j++)
		{
			Edge &ee=AD[s][j];
			if(VIS[ee.to]!=kase)continue;
			ans=min(ans,ee.l+D[ee.to]);
		}
	}
	return ans;
}
int Solve()
{
	int ans=INF;
	for(int i=0;i<N;i++)
	{
		ans=min(ans,Solve(i));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)AD[i].clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			AD[a].push_back(Edge(b,c));
			AD[b].push_back(Edge(a,c));
		}
		int ans=Solve();
		if(ans==INF)puts("No solution.");
		else printf("%d\n",ans);
	}
	return 0;
}
