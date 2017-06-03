#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;
//const int INF=2147483647;
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
		queue<pair<int,int> >q;q.push(make_pair(0,0)),DIST[0][0]=0;
		while(!q.empty())
		{
			const auto p=q.front();q.pop();
			if(p.first!=0&&p.first==p.second)continue;
			for(int bnxt=0;bnxt<N;bnxt++)if(EDGE[p.second][bnxt]&&!VIS[p.first][bnxt])
			{
				VIS[p.first][bnxt]=true;
				for(int anxt=0;anxt<N;anxt++)if(!EDGE[p.first][anxt])
				{
					if(DIST[anxt][bnxt]==-1)q.push(make_pair(anxt,bnxt)),DIST[anxt][bnxt]=DIST[p.first][p.second]+1;
				}
			}
		}
		printf("%d\n",DIST[N-1][N-1]);
	}
	return 0;
}
