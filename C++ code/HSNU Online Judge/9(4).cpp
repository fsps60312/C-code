#include<cstdio>
#include<vector>
using namespace std;
struct Edge
{
	int to;
	double c;
	Edge(){}
	Edge(int to,double c):to(to),c(c){}
};
vector<Edge>AD[2000];
double MN[2000];
int CNT[2000];
bool INQ[2000];
#include<queue>
void Push(queue<int>&q,int v)
{
	if(INQ[v])return;
	q.push(v);
	INQ[v]=true;
}
int N,M,A,B;
double V;
double Solve()
{
	queue<int>q;
	Push(q,A);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		if(CNT[u]++>N*2)return 0.0;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			double f=MN[u]*e.c;
			if(f+1e-9<MN[e.to])
			{
				MN[e.to]=f;
				Push(q,e.to);
			}
		}
	}
	return MN[B];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lf%d%d",&N,&M,&V,&A,&B)==5)
	{
		A--,B--;
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			MN[i]=1e100;
			CNT[i]=0;
			INQ[i]=false;
		}
		MN[A]=V;
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static double c;
			scanf("%d%d%lf",&a,&b,&c);
			a--,b--;
			AD[a].push_back(Edge(b,c));
		}
		printf("%.0f\n",Solve());
	}
	return 0;
}
