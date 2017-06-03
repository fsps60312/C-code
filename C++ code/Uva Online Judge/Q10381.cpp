#include<cstdio>
#include<queue>
#include<cassert>
using namespace std; 
const int INF=1<<29;
int T,R,C;
char GRID[40][40];
struct Pq
{
	int r,c,len,cost;
	Pq(){}
	Pq(int r,int c,int len,int cost):r(r),c(c),len(len),cost(cost){}
	bool operator<(const Pq &a)const{return cost>a.cost;}
}S,E;
int COST[40][40][4];
int D[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int VIS[40][40];
int Bfs(int _r,int _c,int kase)
{
	queue<int>qr,qc,ql;
	qr.push(_r),qc.push(_c),ql.push(0);
	while(!qr.empty())
	{
		static int r,c,l;
		r=qr.front(),c=qc.front(),l=ql.front();
		qr.pop(),qc.pop(),ql.pop();
		if(r<0||r>=R||c<0||c>=C||VIS[r][c]==kase||GRID[r][c]=='#')continue;
		VIS[r][c]=kase;
//		printf("(%d,%d)\n",r,c);
		if(r==E.r&&c==E.c)return l;
		for(int i=0;i<4;i++)qr.push(r+D[i][0]),qc.push(c+D[i][1]),ql.push(l+1);
	}
	return INF;
//	printf("end(%d,%d)\n",_r,_c);
//	assert(0);
}
void Init()
{
	for(int i=0;i<R;i++)for(int j=0;j<C;j++)
	{
		VIS[i][j]=0;
		for(int k=0;k<4;k++)COST[i][j][k]=INF;
	}
	for(int r=0;r<R;r++)
	{
		for(int c=0;c<C;c++)
		{
			if(GRID[r][c]=='#')continue;
			for(int i=0;i<4;i++)
			{
				static int y,x;y=r+D[i][0],x=c+D[i][1];
				if(y<0||y>=R||x<0||x>=C||GRID[y][x]=='#'||GRID[y][x]=='X')continue;
				static int kase=0;
				kase++;
				VIS[y][x]=kase;
//				printf("Bfs(%d,%d,%d)\n",r,c,i);
				COST[r][c][i]=Bfs(r,c,kase);
			}
		}
	}
}
int Solve()
{
	priority_queue<Pq>pq;
	pq.push(Pq(S.r,S.c,0,0));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(p.r==E.r&&p.c==E.c)return p.cost;
//		printf("(%d,%d)\n",p.r,p.c);
		for(int i=0;i<4;i++)
		{
			static int y,x;
			y=p.r+D[i][0],x=p.c+D[i][1];
			if(y<0||y>=R||x<0||x>=C||GRID[y][x]=='#')continue;
			int cost=p.cost;
			if(GRID[y][x]!='X')
			{
				assert(COST[p.r][p.c][i]!=INF);
				cost=max(p.cost,p.len+COST[p.r][p.c][i]);
			}
			pq.push(Pq(y,x,p.len+1,cost));
		}
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&R,&C);
			S.r=E.r=-1;
			for(int i=0;i<R;i++)
			{
				for(int j=0;j<C;j++)
				{
					char &v=GRID[i][j];
					do
					{
						scanf("%c",&v);
					}while(v!='E'&&v!='X'&&v!='#'&&v!='.');
					if(v=='E')S.r=i,S.c=j;
					else if(v=='X')E.r=i,E.c=j;
				}
			}
			assert(S.r!=-1&&E.r!=-1);
//			printf("from(%d,%d)to(%d,%d)\n",S.r,S.c,E.r,E.c);
			Init();
			printf("%d\n",Solve());
		}
	}
	return 0;
}
