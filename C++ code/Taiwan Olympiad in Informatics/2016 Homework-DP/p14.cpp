#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
char A[1001],B[1001];
int DP[1000][1000],N;
int main()
{
//	freopen("inn.txt","r",stdin);
	scanf("%s",A);
	N=-1;while(A[++N]);
	for(int i=0;i<N;i++)B[N-1-i]=A[i];
	for(int i=0;i<N;i++)DP[0][i]=(A[0]==B[i]?1:0);
	for(int i=0;i<N;i++)DP[i][0]=(A[i]==B[0]?1:0);
	for(int i=1;i<N;i++)for(int j=1;j<N;j++)
	{
		if(A[i]==B[j])DP[i][j]=DP[i-1][j-1]+1;
		else DP[i][j]=max(DP[i-1][j],DP[i][j-1]);
	}
	printf("%d\n",DP[N-1][N-1]);
	return 0;
}
