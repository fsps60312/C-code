#include<cstdio>
typedef long long LL;
const LL MOD=1000000000LL;
int N,X,Y;
LL FREE[1001],DP[1001][1001];
LL GetDP(const int l,const int r)
{
	LL &dp=DP[l][r];
	if(dp!=-1LL)return dp;
	if(l==0)return dp=FREE[r];
//	if(r==0)return dp=FREE[l];
	dp=0LL;
//	(dp+=FREE[l]*FREE[r])%=MOD;
//	for(int i=0;i<=r;i++)(dp+=GetDP(l-1,i)*FREE[r-i])%=MOD;
//	for(int i=1;i<=l;i++)for(int j=1;j<=r;j++)
//	{
//		(dp+=FREE[l-i]*FREE[r-j]%MOD*GetDP(i-1,j-1))%=MOD;
//	}
	for(int i=1;i<=l;i++)(dp+=FREE[i-1]*GetDP(l-i,r))%=MOD;
	for(int i=0;i<=r;i++)(dp+=GetDP(l-1,i)*FREE[r-i])%=MOD;
	return dp;
}
LL Solve()
{
	LL ans=0LL;
	for(int xto=Y;xto<=N;xto++)
	{
		//inside: xto-x
		(ans+=FREE[xto-X]*GetDP(X-1,N-xto))%=MOD;
//		if(X==1)(ans+=FREE[xto-X]*FREE[N-xto])%=MOD;
//		else
//		{
//			for(int i=1;i<X;i++)
//			{
//				LL ta=(2LL*FREE[X-1-i]*FREE[N-X])%MOD;
//				(ta*=FREE[i-1])%=MOD;
//				(ans+=ta)%=MOD;
//			}
//		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=1000;i++)for(int j=0;j<=1000;j++)DP[i][j]=-1LL;
	FREE[0]=1LL,FREE[1]=1LL;
	for(int i=2;i<=1000;i++)
	{
		FREE[i]=0LL;
		for(int j=1;j<=i;j++)(FREE[i]+=FREE[j-1]*FREE[i-j])%=MOD;
	}
	while(scanf("%d%d%d",&N,&X,&Y)==3)printf("%lld\n",Solve());
	return 0;
}
/*
1000 333 666
1000 999 1000
1000 1 2
6 2 4
500 35 67
*/
