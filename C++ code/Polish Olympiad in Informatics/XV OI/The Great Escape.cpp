#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,K,X,Y,A,B,C,D;
char GRID[100][101];
int DP[4][25*26*25*26];
int UPON[100][101],DOWN[100][101],LEFT[100][101],RIGT[100][101];
int QueryUpon(const int left,const int rigt,const int upon,const int down);
int QueryDown(const int left,const int rigt,const int upon,const int down);
int QueryLeft(const int left,const int rigt,const int upon,const int down);
int QueryRigt(const int left,const int rigt,const int upon,const int down);
int QueryUpon(const int left,const int rigt,const int upon,const int down)
{
	if(left==-1||rigt==-1||upon==-1||down==-1)return 0;
	int &dp=DP[0][left*B+rigt*C+upon*D+down];
	if(dp!=-1)return dp;
	const int mx=min(upon,(UPON[X-left][Y+down]-1)-Y);
	if(mx<0)return dp=0;
	if(left==0)return dp=1;
	if(mx==0)return dp=QueryRigt(left-1,rigt,mx,down);
	else
	{
		dp=QueryRigt(left-1,rigt,mx,down)+QueryUpon(left,rigt,mx-1,down);
		if(dp>=K)dp-=K;
		return dp;
	}
}
int QueryRigt(const int left,const int rigt,const int upon,const int down)
{
	if(left==-1||rigt==-1||upon==-1||down==-1)return 0;
	int &dp=DP[3][left*B+rigt*C+upon*D+down];
	if(dp!=-1)return dp;
	const int mx=min(rigt,(RIGT[X-left][Y+upon]-1)-X);
	if(mx<0)return dp=0;
	if(upon==0)return dp=1;
	
}
int QueryDown(const int left,const int rigt,const int upon,const int down)
{
	if(left==-1||rigt==-1||upon==-1||down==-1)return 0;
	int &dp=DP[1][left*B+rigt*C+upon*D+down];
	if(dp!=-1)return dp;
}
int QueryLeft(const int left,const int rigt,const int upon,const int down)
{
	if(left==-1||rigt==-1||upon==-1||down==-1)return 0;
	int &dp=DP[2][left*B+rigt*C+upon*D+down];
	if(dp!=-1)return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		scanf("%d%d",&X,&Y);
		for(int i=0;i<N;i++)scanf("%s",GRID[i]);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			UPON[i][j]=(GRID[i][j]=='*'?i:(i==0?-1:GRID[i-1][j]));
			LEFT[i][j]=(GRID[i][j]=='*'?j:(j==0?-1:GRID[i][j-1]));
		}
		for(int i=N-1;i>=0;i--)for(int j=N-1;j>=0;j--)
		{
			DOWN[i][j]=(GRID[i][j]=='*'?i:(i==N-1?N:GRID[i+1][j]));
			LEFT[i][j]=(GRID[i][j]=='*'?j:(j==N-1?N:GRID[i][j+1]));
		}
		A=X-0,B=(M-1)-X,C=Y-0,D=(N-1)-Y;
		++A,++B,++C,++D;
		A*=(B*=(C*=D));
		for(int d=0;d<4;d++)for(int i=0;i<A;i++)DP[d][i]=-1;
		printf("%d\n",QueryUpon(A/B-1,B/C-1,C/D-1,D-1));
	}
	return 0;
}
