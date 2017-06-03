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
		LL pass0=1LL,pass1=0LL,pass2=0LL;
		for(int i=0;i<N;i++)
		{
//			DP[i][0]=unpass;
//			DP[i][1]=pass;
			LL p0=0LL,p1=0LL,p2=0LL;
			if(K[i]==2)
			{
				(p0+=pass0)%=MOD,(p0+=pass1)%=MOD;
				(p1+=pass0)%=MOD,(tp+=pass1*2)%=MOD;
			}
			else
			{
				(p0+=pass0)%=MOD,(p0+=pass1)%=MOD;
				(p1+=pass0)%=MOD;
			}
			pass0=p0,pass1=p1;
		}
	}
	return 0;
}
