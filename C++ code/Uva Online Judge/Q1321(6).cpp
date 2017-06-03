#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
const int INF=2147483647,BFSX=200;
int T,X1,Y1=1,X2,Y2,D[6]={37,48,31,24,6,14};
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
		for(int j=4;j<v[i].size();j++)if(v[i][j]!=v[i][j-4])printf(" %d",j);
		puts("");
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	srand(time(NULL));
	X1=BFSX;
	Bfs();
	OutPut();
	return 0;
}
