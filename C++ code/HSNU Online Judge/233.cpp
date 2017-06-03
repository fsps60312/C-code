#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int M,N,K,DP[1501][1501],MX[1501][1501],GRID[1501][1501],SUM[1501][1501];
int Sum(const int &r1,const int &c1,const int &r2,const int &c2){return SUM[r2][c2]-SUM[r2][c1-1]-SUM[r1-1][c2]+SUM[r1-1][c1-1];}
int max(const int &a,const int &b,const int &c){return max(a,max(b,c));}
int main()
{
	scanf("%d%d%d",&M,&N,&K);
	for(int i=1;i<=M;i++)for(int j=1;j<=N;j++)scanf("%d",&GRID[i][j]);
	SUM[0][0]=0;
	for(int i=1;i<=M;i++)SUM[i][0]=0;
	for(int i=1;i<=N;i++)SUM[0][i]=0;
	for(int i=1;i<=M;i++)for(int j=1;j<=N;j++)SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+DP[i][j];
	for(int r=0;r<=M;r++)for(int c=0;c<=N;c++)MX[r][c]=DP[r][c]=0;
	for(int i=1;i+K-1<=M;i++)for(int j=1;j+K-1<=N;j++)DP[i][j]=Sum(i,j,i+K-1,j+K-1);
	for(int r=1;r<=M;r++)for(int c=1;c<=N;c++)MX[r][c]=max(MX[r-1][c],MX[r][c-1],DP[r][c]);
	return 0;
}
