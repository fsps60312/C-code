#include<cstdio>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M;
int GRID[1000][1000];
int DIST[3][1000000];
int RESULT[1000000];
void Bfs(const int f)
{
	queue<int>q;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			DIST[f][i*M+j]=INF;
			if(GRID[i][j]==f)
			{
				DIST[f][i*M+j]=0;
				q.push(i*M+j);
			}
		}
	}
	while(!q.empty())
	{
		const int u=q.front();q.pop();
//		printf("u=%d,dist=%d\n",u,DIST[f][17]);
		const int x=u/M,y=u%M;
		static int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
		for(int i=0;i<4;i++)
		{
			int tx=x+d[i][0],ty=y+d[i][1];
			if(tx<0||ty<0||tx>=N||ty>=M)continue;
			if(GRID[tx][ty]==4)continue;
			if(DIST[f][u]+1<DIST[f][tx*M+ty])
			{
				DIST[f][tx*M+ty]=DIST[f][u]+1;
				q.push(tx*M+ty);
			}
		}
	}
}
void Cover(int f1,int f2)
{
	int ans=INF;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(GRID[i][j]==f1)ans=min(ans,DIST[f2][i*M+j]);
		}
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			if(GRID[i][j]==f1)DIST[f2][i*M+j]=ans;
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			char c;
			do
			{
				scanf("%c",&c);
			}while(c!='#'&&c!='.'&&c!='1'&&c!='2'&&c!='3');
			int &g=GRID[i][j];
			switch(c)
			{
				case'1':g=0;break;
				case'2':g=1;break;
				case'3':g=2;break;
				case'.':g=3;break;
				case'#':g=4;break;
				default:assert(0);
			}
		}
	}
	for(int f=0;f<3;f++)Bfs(f);
	for(int f=0;f<3;f++)for(int g=0;g<3;g++)Cover(f,g);
	for(int i=0;i<N*M;i++)
	{
		int &res=RESULT[i];
		for(int k=0;k<3;k++)
		{
			if(DIST[k][i]==INF){res=INF;break;}
			res+=DIST[k][i];
		}
	}
	int ans=INF;
	for(int i=0;i<N*M;i++)ans=min(ans,RESULT[i]);
	if(ans==INF)puts("-1");
	else printf("%d\n",ans-2);
	return 0;
}
