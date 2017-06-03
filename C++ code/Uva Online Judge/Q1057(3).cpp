#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=1<<30;
int N,M;
int DIST[100][100],DP[100][100];
bool INQ[100][100];
queue<int>QA,QB;
void Push(int a,int b)
{
	if(INQ[a][b])return;
	INQ[a][b]=true;
	QA.push(a),QB.push(b);
}
void Pop(int &a,int &b)
{
	a=QA.front(),b=QB.front();
	QA.pop(),QB.pop();
	INQ[a][b]=false;
}
void Solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		DP[i][j]=INF;
		INQ[i][j]=false;
	}
	DP[0][0]=1;
	Push(0,0);
	while(!QA.empty())
	{
		static int a,b;
		Pop(a,b);
//		printf("a=%d,b=%d,DP=%d\n",a,b,DP[a][b]);
		for(int i=0;i<N;i++)
		{
			if(DIST[a][i]==1)
			{
				int cost=i==b?0:1;
				if(DP[i][b]>DP[a][b]+cost)
				{
					DP[i][b]=DP[a][b]+cost;
					Push(i,b);
				}
			}
			if(DIST[i][b]==1)
			{
				int cost=i==a?0:1;
				if(DP[a][i]>DP[a][b]+cost)
				{
					DP[a][i]=DP[a][b]+cost;
					Push(a,i);
				}
			}
		}
		if(a!=b&&DP[b][a]>DP[a][b]+DIST[a][b]-1)
		{
			DP[b][a]=DP[a][b]+DIST[a][b]-1;
			Push(b,a);
		}
	}
//	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
//	{
//		if(i==j)continue;
//		if(DP[j][i]>DP[i][j]+DIST[i][j]-1)
//		{
//			printf("i=%d,j=%d,(i,j)=%d,(j,i)=%d>%d\n",i,j,DP[i][j],DP[j][i],DP[i][j]+DIST[i][j]-1);
//			assert(0);
//		}
//	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=INF;
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			DIST[a][b]=1;
		}
		for(int m=0;m<N;m++)
		{
			for(int i=0;i<N;i++)
			{
				if(DIST[i][m]==INF)continue;
				for(int j=0;j<N;j++)
				{
					if(DIST[i][j]>DIST[i][m]+DIST[m][j])
					{
						DIST[i][j]=DIST[i][m]+DIST[m][j];
					}
				}
			}
		}
		Solve();
		static int kase=1;
		printf("Network %d\n",kase++);
		if(DP[1][1]!=INF)printf("Minimum number of nodes = %d\n\n",DP[1][1]);
		else puts("IMPOSSIBLE\n");
	}
	return 0;
}
