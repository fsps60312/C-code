#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int INF=(1<<30)-1;
int T,A,B,M,L,K,N;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(int to,int cost):to(to),cost(cost){}
};
int AD[100][100],F[100][100];
void Floyd()
{
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)F[i][j]=AD[i][j];
	for(int m=0;m<A;m++)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				getmin(F[i][j],F[i][m]+F[m][j]);
			}
		}
	}
}
struct Pq
{
	int u,k,cost;
	Pq(){}
	Pq(int u,int k,int cost):u(u),k(k),cost(cost){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:k>p.k;}
};
bool VIS[100][11];
Pq solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<=K;j++)VIS[i][j]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(N-1,0,0));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.u][p.k])continue;
		VIS[p.u][p.k]=true;
		if(p.u==0)return p;
		for(int i=0;i<N;i++)
		{
			if(F[p.u][i]==INF)continue;
			pq.push(Pq(i,p.k,p.cost+F[p.u][i]));
			if(p.k<K&&F[p.u][i]<=L)pq.push(Pq(i,p.k+1,p.cost));
		}
	}
}
int main()
{
//	freopen("inn.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d%d%d",&A,&B,&M,&L,&K);
			N=A+B;
			for(int i=0;i<N;i++)for(int j=0;j<N;j++)AD[i][j]=INF;
			for(int i=0;i<M;i++)
			{
				static int a,b,l;scanf("%d%d%d",&a,&b,&l);
				a--,b--;
				AD[a][b]=AD[b][a]=l;
			}
			Floyd();
			Pq ans=solve();
			printf("%d\n",ans.cost);
		}
	}
	return 0;
}
