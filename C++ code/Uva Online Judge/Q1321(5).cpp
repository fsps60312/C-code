#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
const int INF=2147483647,BFSX=300;
int T,X1,Y1=3,X2,Y2,D[6]={28,30,38,4,9,10};
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
	DP[i][j][k][l]=INF,INQ[i][j][k][l]=false,PRE[i][j][k][l]=-1;
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
void OutPut()
{
	for(int i=4;i<=BFSX;i++)
	{
		if(!Same(BFSX+i,BFSX+i+4))printf(" %d",i);
	}
	puts("");
	for(int i=4;i<=BFSX;i++)
	{
		if(!Same(BFSX-i,BFSX-i-4))printf(" %d",i);
	}
	puts("");
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	srand(time(NULL));
	X1=BFSX;
	Bfs();
	OutPut();return 0;
	int xl=64,xr=68;
	for(int cnt=0;cnt<10000;cnt++)
	{
		for(int i=0;i<6;i++)D[i]=(rand()%50+50)%50+1;
		Y1=(rand()%4+4)%4;
		printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d",D[0],D[1],D[2],D[3],D[4],D[5],Y1);
		Bfs();
		printf("a");
		for(int i=xl;i<xr;i++)
		{
			if(!Same(BFSX+i,BFSX+i+4)||!Same(BFSX-i,BFSX-i-4))
			{
				assert(0);
			}
		}
		printf("b\n");
	}
	printf("successed!\n");
	system("pause");
	return 0;
}
