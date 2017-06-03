#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M,DIST[100][100],DP[100][100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=DP[i][j]=INF;
		for(int i=0;i<N;i++)DIST[i][i]=0;
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),a--,b--,getmin(DIST[a][b],1);
		for(int m=0;m<N;m++)
		{
			for(int a=0;a<N;a++)if(DIST[a][m]!=INF)
			{
				for(int b=0;b<N;b++)if(DIST[m][b]!=INF)getmin(DIST[a][b],DIST[a][m]+DIST[m][b]);
			}
		}
		static bool inq[100][100];
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)inq[i][j]=false;
		queue<int>qa,qb;
		DP[0][0]=2,qa.push(0),qb.push(0),inq[0][0]=true;
		while(!qa.empty())
		{
			const int a=qa.front(),b=qb.front();
			qa.pop(),qb.pop();
			inq[a][b]=false;
			if(DIST[a][b]==INF)continue;
			for(int nxta=0;nxta<N;nxta++)if(DIST[b][nxta]!=INF)
			{
				for(int nxtb=0;nxtb<N;nxtb++)if(DIST[nxtb][a]!=INF)
				{
					if(nxta==a&&nxtb==b)continue;
					const int update=DP[a][b]+(DIST[a][b]-1)+DIST[b][nxta]+DIST[nxtb][a];
					if(DP[nxta][nxtb]>update)
					{
						DP[nxta][nxtb]=update;
						if(!inq[nxta][nxtb])qa.push(nxta),qb.push(nxtb),inq[nxta][nxtb]=true;
					}
				}
			}
		}
		assert(DP[1][1]!=INF);
		printf("%d\n",DP[1][1]-1);
	}
	return 0;
}
