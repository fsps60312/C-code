#include<cstdio>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M;
void getmin(int &a,const int &b){if(b<a)a=b;}
char GRID[100][101];
int DIST[10000];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%s",GRID[i]);
	queue<int>q;
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)
	{
		DIST[i*M+j]=INF;
		if(GRID[i][j]=='H'){DIST[i*M+j]=0;q.push(i*M+j);}
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
		for(int i=0;i<4;i++)
		{
			int y=u/M+d[i][0],x=u%M+d[i][1];
			if(y<0||x<0||y>=N||x>=M)continue;
			int n=y*M+x;
			if(GRID[y][x]=='S'){getmin(DIST[n],DIST[u]+1);}
			if(GRID[y][x]!='.')continue;
			if(DIST[u]+1<DIST[n])
			{
				DIST[n]=DIST[u]+1;
				q.push(n);
			}
		}
	}
//	for(int i=0;i<N;i++)
//	{
//		for(int j=0;j<M;j++)printf(" %2d",DIST[i*M+j]==INF?-1:DIST[i*M+j]);
//		puts("");
//	}
	int ans=INF;
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)
	{
		if(GRID[i][j]!='S'||DIST[i*M+j]==INF)continue;
		static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
		for(int k=0;k<4;k++)
		{
			int y=i+d[k][0],x=j+d[k][1];
			if(y<0||x<0||y>=N||x>=M||GRID[y][x]!='S'||DIST[y*M+x]==INF)continue;
//			printf("(%d,%d),(%d,%d)\n",i,j,y,x);
			getmin(ans,DIST[i*M+j]+DIST[y*M+x]);
		}
	}
	if(ans==INF)puts("Hi and Ho will not have lunch.");
	else printf("%d\n",ans);
	return 0;
}
