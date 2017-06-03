#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M,GRID[50][50],SUM[51][51];
int DP[50][50][50][50];
int GetSum(const int r1,const int c1,const int r2,const int c2)
{
	return SUM[r2+1][c2+1]-SUM[r2+1][c1]-SUM[r1][c2+1]+SUM[r1][c1];
}
int GetDP(const int r1,const int c1,const int r2,const int c2)
{
	int &dp=DP[r1][c1][r2][c2];
	if(dp!=INF)return dp;
	if(r1==r2&&c1==c2)return dp=0;
	for(int row=r1;row<r2;row++)getmin(dp,GetSum(r1,c1,r2,c2)+GetDP(r1,c1,row,c2)+GetDP(row+1,c1,r2,c2));
	for(int col=c1;col<c2;col++)getmin(dp,GetSum(r1,c1,r2,c2)+GetDP(r1,c1,r2,col)+GetDP(r1,col+1,r2,c2));
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d%d",&N,&M)==2);
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)
	{
		assert(scanf("%d",&GRID[i][j])==1);
		SUM[i+1][j+1]=SUM[i+1][j]+SUM[i][j+1]-SUM[i][j]+GRID[i][j];
	}
	for(int r1=0;r1<N;r1++)for(int r2=r1;r2<N;r2++)for(int c1=0;c1<M;c1++)for(int c2=c1;c2<M;c2++)DP[r1][c1][r2][c2]=INF;
	printf("%d\n",GetDP(0,0,N-1,M-1));
	return 0;
}
