#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
const int INF=2147483647,BFSX=1000,NUM=10;//50
int T,X1,Y1=2,X2,Y2,D[6]={48,44,28,16,42,39};
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
	if(p.y>=4||p.y<0||p.x<0||p.x>BFSX*2)return;
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
int MinCost(int x,int y)
{
	int ans=INF;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			ans=min(ans,DP[x][y][i][j]);
		}
	}
	return ans;
}
void OutPut()
{
//	for(int i=1;i<=BFSX;i++)printf("%3d%3d%3d%3d\n"
//	,MinCost(i,0)-MinCost(i-1,0)
//	,MinCost(i,1)-MinCost(i-1,1)
//	,MinCost(i,2)-MinCost(i-1,2)
//	,MinCost(i,3)-MinCost(i-1,3));
	vector<int>v[4];
	for(int i=1;i<=BFSX;i++)
	{
		for(int j=0;j<4;j++)v[j].push_back(MinCost(i,j)-MinCost(i-1,j));
	}
	for(int i=0;i<4;i++)
	{
		for(int j=8;j<v[i].size()-500;j++)if(v[i][j]!=v[i][j-4])
		{
			printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d\n",D[0],D[1],D[2],D[3],D[4],D[5],Y1);
			printf("j==%d\n",j);
			assert(0);
			printf(" %d",j);
		}
//		puts("");
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	srand(time(NULL));
	X1=BFSX;
	for(int &i0=D[0]=1;i0<=NUM;i0++)
	{
		printf("i0=%2d\n",i0);
		for(int &i1=D[1]=1;i1<=NUM;i1++)
		{
			printf("\ti1=%2d\n",i1);
			for(int &i2=D[2]=1;i2<=NUM;i2++)
			{
				printf("\t\ti2=%2d:",i2);
				for(int &i3=D[3]=1;i3<=NUM;i3++)
				{
					printf("*");
					for(int &i4=D[4]=1;i4<=NUM;i4++)
					for(int &i5=D[5]=1;i5<=NUM;i5++)
					for(int &y=Y1=0;y<4;y++)
					{
//						printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d",i0,i1,i2,i3,i4,i5,y);
						Bfs();
//						printf("a");
						OutPut();
//						printf("b\n");
					}
				}
				puts("");
			}
		}
	}
//	Bfs();
//	OutPut();return 0;
	for(int cnt=0;cnt<100000;cnt++)
	{
		if(cnt%1000==0)printf("case %d\n",cnt);
		for(int i=0;i<6;i++)D[i]=(rand()%10+10)%10+1;
		Y1=(rand()%4+4)%4;
		printf("%2d,%2d,%2d,%2d,%2d,%2d:%1d",D[0],D[1],D[2],D[3],D[4],D[5],Y1);
		Bfs();
		printf("a");
		OutPut();
		printf("b\n");
	}
	printf("successed!\n");
	system("pause");
	return 0;
}
