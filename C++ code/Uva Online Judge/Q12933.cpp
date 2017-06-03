#include<cstdio>
#include<queue>
using namespace std;
int N,M,R1,C1,R2,C2,MAZE[502][502];
struct Pq1
{
	int r,c,cost;
	Pq1(){}
	Pq1(int r,int c,int cost):r(r),c(c),cost(cost){}
	bool operator<(const Pq1 &p)const{return cost>p.cost;}
};
int Solve1()
{
	if(!MAZE[R1][C1]||!MAZE[R2][C2])return -1;
	static bool vis[501][501];
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)vis[i][j]=false;
	}
	priority_queue<Pq1>pq;
	pq.push(Pq1(R1,C1,MAZE[R1][C1]));
	while(!pq.empty())
	{
		Pq1 u=pq.top();pq.pop();
		if(vis[u.r][u.c])continue;
		vis[u.r][u.c]=true;
		if(u.r==R2&&u.c==C2)return u.cost;
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			int r=u.r+d[i][0],c=u.c+d[i][1];
			if(!MAZE[r][c])continue;
			pq.push(Pq1(r,c,u.cost+MAZE[r][c]));
		}
	}
	return -1;
}
struct Pq2
{
	int r,c,d,cost;
	Pq2(){}
	Pq2(int r,int c,int d,int cost):r(r),c(c),d(d),cost(cost){}
	bool operator<(const Pq2 &p)const{return cost>p.cost;}
};
int Solve2()
{
	if(!MAZE[R1][C1]||!MAZE[R2][C2])return -1;
	static bool vis[501][501][4];
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			for(int k=0;k<4;k++)vis[i][j][k]=false;
		}
	}
	priority_queue<Pq2>pq;
	for(int i=0;i<4;i++)pq.push(Pq2(R1,C1,i,MAZE[R1][C1]));
	while(!pq.empty())
	{
		Pq2 u=pq.top();pq.pop();
		if(vis[u.r][u.c][u.d])continue;
		vis[u.r][u.c][u.d]=true;
		if(u.r==R2&&u.c==C2)return u.cost;
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=1;i<=3;i++)
		{
			int r=u.r+d[(u.d+i)%4][0],c=u.c+d[(u.d+i)%4][1];
			if(!MAZE[r][c])continue;
			pq.push(Pq2(r,c,(u.d+i)%4,u.cost+MAZE[r][c]));
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d%d%d",&N,&M,&R1,&C1,&R2,&C2)==6)
	{
		for(int i=1;i<=N;i++)MAZE[i][0]=MAZE[i][M+1]=0;
		for(int i=1;i<=M;i++)MAZE[0][i]=MAZE[N+1][i]=0; 
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
			{
				static char s[4];
				scanf("%s",s);
				static int v;
				if(sscanf(s,"%d",&v)==1)MAZE[i][j]=v;
				else MAZE[i][j]=0;
			}
		}
		static int kase=1;
		printf("Case %d: %d %d\n",kase++,Solve1(),Solve2());
	} 
	return 0;
}
