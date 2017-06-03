#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647,BFSX=200;
int T,X1,Y1=3,X2,Y2,D[6]={1,1,1,1,14,15};
int DP[BFSX*2+1][4][6][6];
int PRE[BFSX*2+1][4][6][6];
bool INQ[BFSX*2+1][4][6][6];
struct Pq
{
	int x,y,top,front,right;
	Pq(){}
	Pq(int x,int y,int top,int front,int right):x(x),y(y),top(top),front(front),right(right){}
	Pq MoveUp(){return Pq(x,y+1,front,5-top,right);}
	Pq MoveRight(){return Pq(x+1,y,5-right,front,top);}
	Pq MoveDown(){return Pq(x,y-1,5-front,top,right);}
	Pq MoveLeft(){return Pq(x-1,y,right,front,5-top);}
};
void Push(int &dp,Pq p,queue<Pq>&q,int pre)
{
	if(p.y>=4||p.y<0||p.x<0||p.x>10000)return;
	if(dp+D[p.top]>=DP[p.x][p.y][p.top][p.front])return;
	DP[p.x][p.y][p.top][p.front]=dp+D[p.top];
	PRE[p.x][p.y][p.top][p.front]=pre;
	if(INQ[p.x][p.y][p.top][p.front])return;
	INQ[p.x][p.y][p.top][p.front]=true;
	q.push(p);
}
void Bfs()
{
	for(int i=0;i<=BFSX*2;i++)for(int j=0;j<4;j++)for(int k=0;k<6;k++)for(int l=0;l<6;l++)
	DP[i][j][k][l]=INF,INQ[i][j][k][l]=false;
	queue<Pq>q;
	q.push(Pq(X1,Y1,0,1,2));
	DP[X1][Y1][0][1]=0;
	while(!q.empty())
	{
		Pq p=q.front();q.pop();
		INQ[p.x][p.y][p.top][p.front]=false;
		int &dp=DP[p.x][p.y][p.top][p.front];
		Push(dp,p.MoveUp(),q,0);
		Push(dp,p.MoveRight(),q,1);
		Push(dp,p.MoveDown(),q,2);
		Push(dp,p.MoveLeft(),q,3);
	}
}
bool Same(int a,int b)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<6;j++)
		{
			for(int k=0;k<6;k++)
			{
				if(PRE[a][i][j][k]!=PRE[b][i][j][k])return false;
			}
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	X1=BFSX;Bfs();
	int xl=100,xr=104;
	for(int i=xl;i<xr;i++)
	{
		printf("%d %d\n",Same(BFSX+i,BFSX+i+4),Same(BFSX-i,BFSX-i-4));
	}
	for(int &i0=D[0]=1;i0<=50;i0++)
	{
		printf("i0=%2d\n",i0);
		for(int &i1=D[1]=1;i1<=50;i1++)
		{
			printf("\ti1=%2d\n",i1);
			for(int &i2=D[2]=1;i2<=50;i2++)
			{
				printf("\t\ti2=%2d:",i2);
				for(int &i3=D[3]=1;i3<=50;i3++)
				{
					printf("*");
					for(int &i4=D[4]=1;i4<=50;i4++)
					for(int &i5=D[5]=1;i5<=50;i5++)
					for(int &y=Y1=0;y<4;y++)
					{
//						printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d",i0,i1,i2,i3,i4,i5,y);
						Bfs();
//						printf(" checking");
						for(int i=xl;i<xr;i++)
						{
							if(!Same(BFSX+i,BFSX+i+4)||!Same(BFSX-i,BFSX-i-4))
							{
								printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d\n",i0,i1,i2,i3,i4,i5,y);
								assert(0);
							}
						}
//						puts(" done");
					}
				}
				puts("");
			}
		}
	}
	printf("successed!\n");
	system("pause");
	return 0;
}
