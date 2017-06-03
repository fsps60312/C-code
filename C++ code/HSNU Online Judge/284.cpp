#include<cstdio>
const LL MOD=1000000007LL;
int N,K[1000000];
LL DP[1000000][2];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&K[i]),DP[i][0]=DP[i][1]=0LL;
		DP[0][0]=1LL;
		LL pass=0LL,unpass=1LL;
		for(int i=0;i<N;i++)
		{
//			DP[i][0]=unpass;
//			DP[i][1]=pass;
			LL tu=0LL,tp=0LL;
			if(K[i]==2)
			{
				(tu+=unpass)%=MOD,(tu+=pass)%=MOD;
				(tp+=unpass)%=MOD,(tp+=pass*2)%=MOD;
			}
			else
			{
				(tu+=unpass)%=MOD,(tu+=pass)%=MOD;
				(tp+=unpass)%=MOD;
			}
			unpass=tu,pass=tp;
		}
	}
	return 0;
}
