#include<cstdio>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,GRID[1000][1000],DP[1000000];
bool INQ[1000000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			scanf("%d",&GRID[i][j]);
			DP[i*N+j]=INF;
			INQ[i*N+j]=false;
		}
	}
	queue<int>q;
	q.push(0);
	DP[0]=GRID[0][0];
	INQ[0]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
		for(int i=0;i<4;i++)
		{
			int x=u/N+d[i][0],y=u%N+d[i][1];
			if(x<0||y<0||x>=N||y>=N)continue;
			if(GRID[y][x]==0)continue;
			if(DP[y*N+x]<=DP[u]+GRID[y][x])continue;
			DP[y*N+x]=DP[u]+GRID[y][x];
			if(INQ[y*N+x])continue;
			INQ[y*N+x]=true;
			q.push(y*N+x);
		}
	}
	printf("%d\n",DP[N*N-1]);
	return 0;
}
