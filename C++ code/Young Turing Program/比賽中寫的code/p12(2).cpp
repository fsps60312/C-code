#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,DP[5001][5001];
char A[5002],B[5002];
int main()
{
//	freopen("in.txt","r",stdin);
	gets(A+1),gets(B+1);
	{
		N=0;while(A[++N]&&A[N]!='\n');--N;
		M=0;while(B[++M]&&A[N]!='\n');--M;
		assert(N<=5000&&M<=5000);
		DP[0][0]=0;
		for(int i=1;i<=N;i++)DP[i][0]=i*3;
		for(int i=1;i<=M;i++)DP[0][i]=i*4;
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			int &d=DP[i][j]=2147483647;
			d=min(d,DP[i-1][j-1]+(A[i]==B[j]?0:5));
			d=min(d,DP[i-1][j]+3);
			d=min(d,DP[i][j-1]+4);
//			printf("DP[%d][%d]=%d\n",i,j,d);
		}
		printf("%d\n",DP[N][M]);
	}
	return 0;
}
