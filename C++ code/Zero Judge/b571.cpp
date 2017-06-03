#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M;
char S[500][501];
int DIST[3][500][500];
int Solve()
{
	int sy,sx,ey,ex;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(S[i][j]=='X')sy=i,sx=j;
			if(S[i][j]=='Y')ey=i,ex=j;
			for(int k=0;k<3;k++)DIST[k][i][j]=INF;
		}
	}
	queue<int>q;
	DIST[0][sy][sx]=0;
	q.push(sy*M*3+sx*3+0);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		int y=u/3/M,x=u/3%M,track=(u+1)%3;
		static int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
		for(int i=0;i<4;i++)
		{
			int ty=y+d[i][0],tx=x+d[i][1];
			if(ty<0||ty>=N||tx<0||tx>=M)continue;
			if(S[ty][tx]=='#')continue;
			if(DIST[u%3][y][x]+1>=DIST[track][ty][tx])continue;
			if(S[ty][tx]=='A'+track)continue;//DIST[ty][tx]=DIST[y][x]+3;
			DIST[track][ty][tx]=DIST[u%3][y][x]+1;
			q.push(ty*M*3+tx*3+track);
		}
	}
	int ans=min(DIST[0][ey][ex],min(DIST[1][ey][ex],DIST[2][ey][ex]));
	return ans==INF?-1:ans;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%s",S[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
