#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M;
char A[50001],B[50001];
unsigned int BIT[26][50000/32+1];
int Solve()
{
	static unsigned int tmp[2][50000/32+1];
	unsigned int *dp=tmp[0],*pre=tmp[1];
	for(int i=0;i<M/32+1;i++)pre[i]=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M/32+1;j++)
		{
			const unsigned int fit=C[A[i]-'a'][j];
			dp[j]=pre|fit
		}
		swap(dp,pre);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%s%s",A,B)==2)
	{
		N=-1;while(A[++N]);
		M=-1;while(B[++M]);
		for(int c=0;c<26;c++)for(int i=0;i<M/32+1;i++)BIT[c][i]=0;
		for(int i=0;i<M;i++)BIT[B[i]-'a'][i/32]|=1U<<(i%32);
		printf("%d\n",Solve());
	}
	return 0;
}
