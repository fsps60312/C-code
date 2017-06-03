#include<bits/stdc++.h>
using namespace std;
int N,M,A[3000],B[3000],DP[3000][3000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	static int v;
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	for(int i=0;i<M;i++)scanf("%d",&B[i]);
	DP[0][0]=A[0]==B[0]?1:0;
	for(int i=1;i<N;i++)DP[i][0]=max(A[i]==B[0]?1:0,DP[i-1][0]);
	for(int j=1;j<M;j++)DP[0][j]=max(A[0]==B[j]?1:0,DP[0][j-1]);
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<M;j++)
		{
			int &v=DP[i][j];
			v=DP[i-1][j-1];
			if(A[i]==B[j])v++;
			v=max(v,max(DP[i][j-1],DP[i-1][j]));
		}
	}
	printf("%d\n",DP[N-1][M-1]);
	return 0;
}
