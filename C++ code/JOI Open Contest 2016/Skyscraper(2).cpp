#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int N,L,S[101];
LL DP[101][3][201][1001];
void Add(LL &a,const LL b){(a+=b)%=MOD;}
void Add(LL *a,const int len,const LL b)
{
	if(len>L)return;
	Add(a[len],b);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		S[N]=S[N-1];
		for(int i=0;i<=N;i++)for(int j=0;j<=3;j++)for(int k=0;k<=N*2;k++)for(int l=0;l<=L;l++)DP[i][j][k][l]=0LL;
		++DP[0][0][2][(S[1]-S[0])*2];
		++DP[0][1][1][S[1]-S[0]];
		for(int idx=0;idx<N;idx++)
		{
			for(int one_used=0;one_used<=2;one_used++)for(int level=1;level<=2*N;level++)for(int len=0;len<=L;len++)if(DP[idx][one_used][level][len])
			{
				const LL dp=DP[idx][one_used][level][len];
				if(level>=2)Add(DP[idx+1][one_used][level-2],len+(S[idx+1]-S[idx])*(level-2),dp);
				Add(DP[idx+1][one_used][level+2],len+(S[idx+1]-S[idx])*(level+2),dp);
				Add(DP[idx+1][one_used][level][len+(S[idx+1]-S[idx])*level],(dp*level)%MOD);
				if(level>=1&&one_used+1<=2)Add(DP[idx+1][one_used+1][level-1],len+(S[idx+1]-S[idx])*(level-1),dp);
				if(one_used+1<=2)Add(DP[idx+1][one_used+1][level+1],len+(S[idx+1]-S[idx])*(level+1),dp);
			}
		}
		LL ans=0LL;
		for(int i=0;i<=L;i++)Add(ans,DP[N][2][0][i]);
		printf("%lld\n",ans);
	}
	return 0;
}
