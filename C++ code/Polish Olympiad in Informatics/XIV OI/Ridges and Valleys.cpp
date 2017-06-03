#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
int N;
int G[1002][1002];
bool VIS[1002][1002];
bool IsRidge(const int start_r,const int start_c)
{
	queue<int>q;
	q.push(start_r),q.push(start_c);
	bool ans=true;
	while(!q.empty())
	{
		const int r=q.front();q.pop();
		const int c=q.front();q.pop();
		if(VIS[r][c])continue;
		VIS[r][c]=true;
		static int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
		for(int i=0;i<8;i++)
		{
			const int nxtr=r+d[i][0],nxtc=c+d[i][1];
			if(G[nxtr][nxtc]==G[r][c])q.push(nxtr),q.push(nxtc);
			else if(G[nxtr][nxtc]>G[r][c])ans=false;
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)scanf("%d",&G[i][j]);
		for(int i=0;i<=N+1;i++)G[i][0]=G[i][N+1]=-INF;
		for(int i=0;i<=N+1;i++)G[0][i]=G[N+1][i]=-INF;
		int ans_ridge=0,ans_valley=0;
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)VIS[i][j]=false;
		for(int r=1;r<=N;r++)for(int c=1;c<=N;c++)if(!VIS[r][c]&&IsRidge(r,c))++ans_ridge;
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)VIS[i][j]=false,G[i][j]*=-1;
		for(int r=1;r<=N;r++)for(int c=1;c<=N;c++)if(!VIS[r][c]&&IsRidge(r,c))++ans_valley;
		printf("%d %d\n",ans_ridge,ans_valley);
	}
	return 0;
}
