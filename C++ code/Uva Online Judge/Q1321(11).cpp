#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
typedef long long LL;
const LL INF=1LL<<60,BFSX=1000LL;
void massert(bool valid){if(valid)return;for(;;)printf("E");}
LL T,X1,Y1,X2,Y2,D[6],CNT;
LL DP[BFSX*2LL+1LL][4][6][6];
bool INQ[BFSX*2LL+1LL][4][6][6];
struct Pq
{
	LL x,y,top,front,right;
	Pq(){}
	Pq(LL x,LL y,LL top,LL front,LL right):x(x),y(y),top(top),front(front),right(right){}
	Pq MoveUp(){return Pq(x,y+1LL,front,5LL-top,right);}
	Pq MoveRight(){return Pq(x+1LL,y,5LL-right,front,top);}
	Pq MoveDown(){return Pq(x,y-1LL,5LL-front,top,right);}
	Pq MoveLeft(){return Pq(x-1LL,y,right,front,5LL-top);}
};
void Push(LL dp,Pq p,queue<Pq>&q)
{
	if(p.y>=4LL||p.y<0LL||p.x<0LL||p.x>BFSX*2LL)return;
	if(dp+D[p.top]>=DP[p.x][p.y][p.top][p.front])return;
	DP[p.x][p.y][p.top][p.front]=dp+D[p.top];
	if(INQ[p.x][p.y][p.top][p.front])return;
	INQ[p.x][p.y][p.top][p.front]=true;
	q.push(p);
}
Pq Pop(queue<Pq>&q)
{
	Pq p=q.front();q.pop();
	INQ[p.x][p.y][p.top][p.front]=false;
	return p;
}
void Bfs()
{
	for(int i=0;i<=BFSX*2;i++)for(int j=0;j<4;j++)for(int k=0;k<6;k++)for(int l=0;l<6;l++)
	DP[i][j][k][l]=INF,INQ[i][j][k][l]=false;
	queue<Pq>q;
	Push(-D[0],Pq(X1,Y1,0LL,1LL,2LL),q);
	LL cnt=0LL;
	while(!q.empty())
	{
		cnt++;
//		massert(cnt<=1000000LL);
		Pq p=Pop(q);
		LL &dp=DP[p.x][p.y][p.top][p.front];
		Push(dp,p.MoveUp(),q);
		Push(dp,p.MoveRight(),q);
		Push(dp,p.MoveDown(),q);
		Push(dp,p.MoveLeft(),q);
	}
}
LL MinCost(LL x,LL y)
{
	LL ans=INF;
	for(LL i=0LL;i<6LL;i++)
	{
		for(LL j=0LL;j<6LL;j++)
		{
			ans=min(ans,DP[x][y][i][j]);
		}
	}
	return ans;
}
LL Solve()
{
	Bfs();
	if(abs(X2-BFSX)<=12LL)return MinCost(X2,Y2);
	if(X2>BFSX)
	{
		LL mod=(X2-BFSX)%4LL;
		LL v1=MinCost(BFSX+4LL+mod,Y2),v2=MinCost(BFSX+8+mod,Y2);
		assert(v2>v1);
		assert((X2-(BFSX+8LL+mod))%4LL==0LL);
		return v2+(v2-v1)*(X2-(BFSX+8LL+mod))/4LL;
	}
	else
	{
		LL mod=(BFSX-X2)%4LL;
		LL v1=MinCost(BFSX-4LL-mod,Y2),v2=MinCost(BFSX-8LL-mod,Y2);
		assert(v2>v1);
		assert(((BFSX-8LL-mod)-X2)%4LL==0LL);
		return v2+(v2-v1)*((BFSX-8LL-mod)-X2)/4LL;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&T)==1)
	{
		while(T--)
		{
			for(LL i=0LL;i<6LL;i++)scanf("%lld",&D[i]);
			scanf("%lld%lld%lld%lld",&X1,&Y1,&X2,&Y2);
			Y1--,Y2--;
			X2+=BFSX-X1,X1=BFSX;
			printf("%lld\n",Solve());
			if(T)puts("");
		}
	}
	return 0;
}
