#include<cstdio>
#include<vector>
using namespace std;
int N,X,Y,K;
int DP[2][10][901][910];
vector<int>V[2];
inline int DigitSum(int n){int ans=0;while(n)ans+=n%10,n/=10;return ans;}
int main()
{
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<=9;i++)for(int j=0;j<=N*9;j++)for(int k=0;k<=(N+1)*9;k++)DP[0][i][j][k]=DP[1][i][j][k]=-1;
	for(int n=0;n<=9;n++)
	{
		DP[0][DigitSum(n)][DigitSum(n*K)]
	}
	return 0;
}
