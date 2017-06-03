#include<cstdio>
#include<vector>
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
int CNT[1000],PRE_CNT;
bool CheckCycle(const int &u)
{
	CNT[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		Edge &e=ET[u][i];
		if(CNT[e.b]<CNT[u])return true;
		if(CNT[e.b]==INF&&CheckCycle(e.b))return true;
	}
	return false;
}
bool CheckCycle()
{
	for(int i=0;i<N;i++)CNT[i]=INF;
	for(int i=0;i<N;i++)
	{
		PRE_CNT=-i*N;
		if(CNT[i]==INF&&CheckCycle(i))
		{
			for(int i=0;i<N;i++)printf("i=%d:%d\n",i,CNT[i]);
			return true;
		}
	}
	return false;
}
#include<queue>
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
