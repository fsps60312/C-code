#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int T,N;
LL R[1000],C[1000],S[1001],DP[1001][1001];
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	LL ans=0LL;
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld%lld",&R[i],&C[i]);
		for(int i=0;i<N;i++)
		{
			S[i]=R[i];
			if(i)assert(R[i]==C[i-1]);
		}
		S[N]=C[N-1];
		for(int i=0;i<=N;i++)for(int j=i+1;j<=N;j++)DP[i][j]=INF;
		for(int i=0;i+1<=N;i++)DP[i][i+1]=0;
		for(int i=0;i+2<=N;i++)DP[i][i+2]=S[i]*S[i+1]*S[i+2];
		for(int len=3;len<=N;len++)
		{
			for(int i=0;i+len<=N;i++)
			{
				for(int k=1;k<len;k++)getmin(DP[i][i+len],DP[i][i+k]+DP[i+k][i+len]+S[i]*S[i+k]*S[i+len]);
			}
		}
		ans+=DP[0][N];
		printf("%lld\n",(DP[0][N]+999LL)/1000LL);
	}
	printf("%lld\n",(ans+999LL)/1000LL);
	return 0;
}
