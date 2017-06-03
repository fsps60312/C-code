#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const double EPS=1e-9;
const int INF=2147483647;
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
int CNT[1000];
bool CheckCycle()
{
	queue<int>q;
	for(int i=0;i<N;i++)if(!CNT[i])q.push(i);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(!--CNT[e.b])q.push(e.b);
		}
	}
	for(int i=0;i<N;i++)if(CNT[i]>0)return true;
	return false;
}
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
			const Edge &e=ET[u][i];
			if(DIST[e.b]<DIST[u]+FUN[e.b]-e.c*limit)
			{
				DIST[e.b]=DIST[u]+FUN[e.b]-e.c*limit;
				if(++CNT[e.b]==N)return true;
				if(!INQ[e.b])
				{
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
		for(int i=0;i<N;i++)ET[i].clear(),CNT[i]=0;
		for(int i=0;i<M;i++)
		{
			int a,b;
			double c;
			scanf("%d%d%lf",&a,&b,&c);
			ET[--a].push_back(Edge(--b,c));
			CNT[b]++;
		}
		if(!CheckCycle()){puts("0");assert(0);}
		else
		{
			double l=0.0,r=1000.0,mid;
			while(r-l>EPS)
			{
				mid=0.5*(r+l);
				if(Solve(mid))l=mid;
				else r=mid;
			}
			assert(l!=0.0);
			printf("%.2f\n",0.5*(l+r));
		}
		break;
	}
	return 0;
}
