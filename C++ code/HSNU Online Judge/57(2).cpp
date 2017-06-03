#include<cstdio>
#include<vector>
using namespace std;
const double EPS=1e-9;
int N,M;
double FUN[1000],DIST[1000];
struct Edge
{
	int b;
	double c;
	Edge(){}
	Edge(const int &_b,const double &_c):b(_b),c(_c){}
};
vector<Edge>ET[1000];
bool CheckCycle(const int &u,const double &g)
{
	if(DIST[u]!=0.0)return DIST[u]==g;
	DIST[u]=g;
	for(int i=0;i<ET[u].size();i++)
	{
		Edge &e=ET[u][i];
		if(CheckCycle(e.b,g))return true;
	}
	return false;
}
bool CheckCycle()
{
	for(int i=0;i<N;i++)DIST[i]=0.0;
	for(int i=0;i<N;i++)if(DIST[i]==0.0&&CheckCycle(i,i+1.0))return true;
	return false;
}
#include<queue>
int CNT[1000];
bool INQ[1000];
bool Solve(const double &limit)
{
	queue<int>q;
	for(int i=0;i<N;i++)DIST[i]=0.0,CNT[i]=0,INQ[i]=true,q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			Edge &e=ET[u][i];
			if(DIST[e.b]<DIST[u]+FUN[e.b]-e.c*limit)
			{
				DIST[e.b]=DIST[u]+FUN[e.b]-e.c*limit;
				if(!INQ[e.b])
				{
					if(++CNT[e.b]==N)return true;
					q.push(e.b);
					INQ[e.b]=true;
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%lf",&FUN[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<M;i++)
		{
			int a,b;
			double c;
			scanf("%d%d%lf",&a,&b,&c);
			ET[--a].push_back(Edge(--b,c));
		}
		if(!CheckCycle())puts("0");
		else
		{
			double l=0.0,r=1000.0,mid;
			while(r-l>EPS)
			{
				mid=0.5*(r+l);
				if(Solve(mid))l=mid;
				else r=mid;
			}
			printf("%.2f\n",0.5*(l+r));
		}
		break;
	}
	return 0;
}
