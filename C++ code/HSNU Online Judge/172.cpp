#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,DIST[1000*1000*2];
char GRID[1000][1000];
int Solve(const int &s,const int &t)
{
	for(int i=0;i<N*M*2;i++)DIST[i]=INF;
	queue<int>q;
	q.push(s);
	DIST[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		int vis=u&1;
		int x=(u>>1)%M,y=(u>>1)/M;
//		printf("(%d,%d,%d):%d\n",x,y,vis);
		static int d[8][2]={{1,2},{2,1},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1}};
		for(int i=0;i<8;i++)
		{
			int r=y+d[i][0],c=x+d[i][1];
			if(r>=0&&c>=0&&r<N&&c<M&&GRID[r][c]!='X')
			{
				int n=r*M+c;n<<=1;
				n|=vis;n|=(GRID[r][c]=='B');
				if(DIST[u]+1<DIST[n])
				{
					DIST[n]=DIST[u]+1;
					if(n==t)return DIST[n];
					q.push(n);
				}
			}
		}
	}
	return -1;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		static int s,t;s=t=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				char &c=GRID[i][j];
				scanf("%c",&c);
				switch(c)
				{
					case'A':s=i*M+j;c='.';break;
					case'C':t=i*M+j;break;
					case'B':
					case'X':
					case'.':break;
					default:j--;break;
				}
			}
		}
		assert(s!=-1&&t!=-1);
		s<<=1,t<<=1,t|=1;
		printf("%d\n",Solve(s,t));
	}
	return 0;
}
