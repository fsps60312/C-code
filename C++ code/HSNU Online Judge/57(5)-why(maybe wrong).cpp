#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const double EPS=1e-9;
const int INF=2147483647;
int N,M;
double FUN[1005],DIST[1005];
struct Edge
{
	int b;
	double c;
	Edge(){}
	Edge(const int &_b,const double &_c):b(_b),c(_c){}
};
vector<Edge>ET[1005];
int CNT[1005],PRE_CNT;
bool CheckCycle(const int &u)
{
	CNT[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		if(!CNT[e.b]){if(CheckCycle(e.b))return true;}
		else if(CNT[u]<CNT[e.b])return true;
	}
	return false;
}
bool CheckCycle()
{
	PRE_CNT=0;
	for(int i=0;i<N;i++)CNT[i]=0;
	for(int i=0;i<N;i++)if(!CNT[i]&&CheckCycle(i))return true;
	return false;
}
bool INQ[1005];
bool Solve(const double &limit)
{
	queue<int>q;
	for(int i=0;i<N;i++)DIST[i]=0.0,CNT[i]=0,INQ[i]=true,q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		if(CNT[u]==N+1)return true;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(DIST[e.b]>DIST[u]+e.c*limit-FUN[e.b])
			{
				DIST[e.b]=DIST[u]+e.c*limit-FUN[e.b];
				if(!INQ[e.b])
				{
					CNT[e.b]++;
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
		}
		if(!CheckCycle()){puts("0");}
		else
		{
			double l=0.0,r=1000000000.0,mid;
			while(r-l>=0.0000001)
			{
				mid=0.5*(r+l);
				if(Solve(mid))l=mid;
				else r=mid;
			}
//			assert(l!=0.0);
			printf("%.2f",r);
		}
		break;
	}
	return 0;
}
