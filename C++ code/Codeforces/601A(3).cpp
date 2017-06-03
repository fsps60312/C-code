#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
//const int INF=2147483647;
struct Pq
{
	int A,B,DIST;
	Pq(){}
	Pq(const int _A,const int _B,const int _DIST):A(_A),B(_B),DIST(_DIST){}
};
bool operator<(const Pq &a,const Pq &b){return a.DIST>b.DIST;}
int N,M,DIST[400][400];
bool EDGE[400][400];
bool VIS[400][400];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			EDGE[a][b]=EDGE[b][a]=true;
		}
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=-1,VIS[i][j]=false;
		priority_queue<Pq>pq;pq.push(Pq(0,0,0));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DIST[p.A][p.B]!=-1)continue;
			DIST[p.A][p.B]=p.DIST;
			if(p.A!=0&&p.A==p.B)continue;
			for(int bnxt=0;bnxt<N;bnxt++)if(EDGE[p.B][bnxt]&&!VIS[p.A][bnxt])
			{
				VIS[p.A][bnxt]=true;
				for(int anxt=0;anxt<N;anxt++)if(!EDGE[p.A][anxt])
				{
					if(DIST[anxt][bnxt]==-1)pq.push(Pq(anxt,bnxt,p.DIST+1));
				}
			}
		}
		printf("%d\n",DIST[N-1][N-1]);
	}
	return 0;
}
