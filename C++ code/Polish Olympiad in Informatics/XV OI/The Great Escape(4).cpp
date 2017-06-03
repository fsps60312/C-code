#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,K,X,Y,A,B,C,D;
char GRID[100][101];
int DP[2][50*51*50*52];
int UPON[100][100],DOWN[100][100],LEFT[100][100],RIGT[100][100];
int &GetReference(const int direction,const int left,const int rigt,const int upon,const int down)
{
	switch(direction)
	{
		case 0:return DP[0][left*B+rigt*C+upon*D+down];
		case 1:return DP[0][down*B+upon*C+left*D+rigt+1];
		case 2:return DP[1][rigt*B+left*C+down*D+upon];
		case 3:return DP[1][upon*B+down*C+rigt*D+left+1];
		default:assert(0);static int error;return error;
	}
}
int GetLimit(const int direction,const int left,const int down)
{
	switch(direction)
	{
		case 0:return Y-UPON[Y+down][X-left];
		case 1:return RIGT[Y-left][X-down]-X;
		case 2:return DOWN[Y-down][X+left]-Y;
		case 3:return X-LEFT[Y+left][X+down];
		default:assert(0);return -1;
	}
}
int Query(const int direction,const int left,const int rigt,const int upon,const int down);
int QueryNonDp(const int direction,const int left,const int rigt,const int upon,const int down)
{
	const int mx=min(upon,GetLimit(direction,left,down)-1);
	if(mx<0)return 0;
	if((mx^upon)&1)return Query(direction,left,rigt,mx,down);
	if(left==0)return 1;
	int dp=Query((direction+1)&3,mx,down,rigt,left-1);
	if(mx>0)
	{
		dp+=Query(direction,left,rigt,mx-1,down);
		if(dp>=K)dp-=K;
	}
	return dp;
}
int Query(const int direction,const int left,const int rigt,const int upon,const int down)
{
	assert(left!=-1&&rigt!=-1&&upon!=-1&&down!=-1);
	const int mx=min(upon,GetLimit(direction,left,down)-1);
	if(mx<0)return 0;
	if((mx^upon)&1)return QueryNonDp(direction,left,rigt,mx,down);
	int &dp=GetReference(direction,left,rigt,upon,down);
	assert(dp!=-2);
	if(dp!=-1)return dp;
	if(left==0)return dp=1;
	dp=QueryNonDp((direction+1)&3,mx,down,rigt,left-1);
	if(mx>0)
	{
		dp+=QueryNonDp(direction,left,rigt,mx-1,down);
		if(dp>=K)dp-=K;
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		scanf("%d%d",&X,&Y),--X,--Y;
		for(int i=0;i<N;i++)scanf("%s",GRID[i]);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			UPON[i][j]=(GRID[i][j]=='*'?i:(i==0?-1:UPON[i-1][j]));
			LEFT[i][j]=(GRID[i][j]=='*'?j:(j==0?-1:LEFT[i][j-1]));
		}
		for(int i=N-1;i>=0;i--)for(int j=M-1;j>=0;j--)
		{
			DOWN[i][j]=(GRID[i][j]=='*'?i:(i==N-1?N:DOWN[i+1][j]));
			RIGT[i][j]=(GRID[i][j]=='*'?j:(j==M-1?M:RIGT[i][j+1]));
		}
		A=X-0,B=(M-1)-X,C=Y-0,D=(N-1)-Y;
		++A,++B,++C,++D,++D;
		A*=(B*=(C*=D));
		for(int d=0;d<2;d++)for(int i=0;i<50*51*50*52;i++)DP[d][i]=-1;
		printf("%d\n",QueryNonDp(0,X-0,(M-1)-X,Y-0,(N-1)-Y));
	}
	return 0;
}
