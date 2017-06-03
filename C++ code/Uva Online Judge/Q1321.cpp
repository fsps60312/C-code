#include<cstdio>
#include<queue>
using namespace std;
const int INF=2147483647;
int T,D[6],X1,Y1,X2,Y2;
int DP[10001][4][6][6];
int PRE[10001][4][6][6];
bool INQ[10001][4][6][6];
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
	for(int i=0;i<=10000;i++)for(int j=0;j<4;j++)for(int k=0;k<6;k++)for(int l=0;l<6;l++)
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
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			for(int i=0;i<6;i++)scanf("%d",&D[i]);
			scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
			Y1--,Y2--;
			X2+=5000-X1,X1=5000;
			puts("a");
			Bfs();
			puts("b");
			int ans=INF;
			for(int i=0;i<6;i++)for(int j=0;j<6;j++)ans=min(ans,DP[X2][Y2][i][j]);
			printf("%d\n",ans);
			return 0;
			for(int i=0;i<=10000;i++)
			{
				printf("(%4d)=",i);
				for(int j=0;j<4;j++)
				{
					for(int k=0;k<6;k++)
					{
						for(int l=0;l<6;l++)
						{
							printf("%d",PRE[i][j][k][l]);
						}
					}
				}
				puts("");
			}
		}
	}
	return 0;
}
