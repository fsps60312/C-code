#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,A[100000];
int DP[100000][2][2];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		DP[0][0][0]=0,DP[0][1][1]=A[0],DP[0][0][1]=DP[0][1][0]=-INF;
		for(int i=1;i<N;i++)
		{
			for(int d=0;d<2;d++)
			{
				DP[i][d][0]=max(DP[i-1][d][0],DP[i-1][d][1]);
				DP[i][d][1]=DP[i-1][d][0]+A[i];
			}
		}
		printf("%d\n",max(DP[N-1][0][0],max(DP[N-1][0][1],DP[N-1][1][0])));
	}
	return 0;
}
