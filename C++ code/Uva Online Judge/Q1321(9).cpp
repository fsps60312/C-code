#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
const int INF=2147483647,BFSX=100000;
int T,X1,Y1,X2,Y2,D[6],CNT,L,R,LB,RB;
int DP[BFSX*2+1][4][6][6];
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
void Clear(int x)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<6;j++)
		{
			for(int k=0;k<6;k++)
			{
				DP[x][i][j][k]=INF;
				INQ[x][i][j][k]=false;
			}
		}
	}
}
void Access(int x)
{
	for(;R<=x;R++)
	{
		Clear(R);
	}
	for(;L>=x;L--)
	{
		Clear(L);
	}
}
void Push(int dp,Pq p,queue<Pq>&q)
{
	if(p.y>=4||p.y<0||p.x<0||p.x>BFSX*2)return;
	Access(p.x);
	if(dp+D[p.top]>=DP[p.x][p.y][p.top][p.front])return;
	DP[p.x][p.y][p.top][p.front]=dp+D[p.top];
	if(INQ[p.x][p.y][p.top][p.front])return;
	INQ[p.x][p.y][p.top][p.front]=true;
	q.push(p);
	if(p.x>=LB&&p.x<=RB)CNT++;
}
Pq Pop(queue<Pq>&q)
{
	Pq p=q.front();q.pop();
	if(p.x>=LB&&p.x<=RB)CNT--;
	INQ[p.x][p.y][p.top][p.front]=false;
	return p;
}
void Bfs()
{
	L=R=BFSX;
	CNT=0;
	queue<Pq>q;
	Push(-D[0],Pq(X1,Y1,0,1,2),q);
//		printf("A%d\n",CNT);
//		printf("B%d\n",CNT);
	int cnt=0;
	while(!q.empty())
	{
		cnt++;
		assert(cnt<=1000000);
//		printf("a%d\n",CNT);
		Pq p=Pop(q);
//		printf("b%d\n",CNT);
		int &dp=DP[p.x][p.y][p.top][p.front];
		Push(dp,p.MoveUp(),q);
		Push(dp,p.MoveRight(),q);
		Push(dp,p.MoveDown(),q);
		Push(dp,p.MoveLeft(),q);
//		printf("c%d\n",CNT);
		if(!CNT)break;
	}
//	printf("time=%d\n",cnt);
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
int Solve()
{
	Bfs();
	if(abs(X2-BFSX)<=12)return MinCost(X2,Y2);
	if(X2>BFSX)
	{
		int mod=(X2-BFSX)%4;
		int v1=MinCost(BFSX+4+mod,Y2),v2=MinCost(BFSX+8+mod,Y2);
		assert((X2-(BFSX+8+mod))%4==0);
		return v2+(v2-v1)*(X2-(BFSX+8+mod))/4;
	}
	else
	{
		int mod=(BFSX-X2)%4;
		int v1=MinCost(BFSX-4-mod,Y2),v2=MinCost(BFSX-8-mod,Y2);
		assert(((BFSX-8-mod)-X2)%4==0);
		return v2-(v2-v1)*((BFSX-8-mod)-X2)/4;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			for(int i=0;i<6;i++)scanf("%d",&D[i]);
			scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
			Y1--,Y2--;
			X2+=BFSX-X1,X1=BFSX;
//			printf("(%d,%d)->(%d,%d)\n",X1,Y1,X2,Y2);
			LB=BFSX-512,RB=BFSX+512;
			printf("%d\n",Solve());
		}
	}
	return 0;
}
