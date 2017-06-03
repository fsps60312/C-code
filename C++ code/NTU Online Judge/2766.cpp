#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const int MOD=1e9+7;
int N,Narray[9];
LL TEN[9];
LL DP[9][1<<20];
LL WAY[1<<10],ANS[1<<10];
LL getDP(const int n,const int s,bool boundReached)
{
//	printf("getDP(%d,%d,%d)\n",n,s,boundReached);
	if(n==-1)
	{
		if((s&((1<<10)-1))==0)return 1;
		else return 0;
	}
	if(!boundReached)
	{
		LL &dp=DP[n][s];
		if(dp!=-1)return dp;
		dp=0;
		for(int i=0;i<10;i++)if((1<<i)&(s>>10))
		{
			(dp+=getDP(n-1,s&(~(1<<i)),false))%=MOD;
		}
		return dp;
	}
	else
	{
		LL dp=0;
		for(int i=0;i<=Narray[n];i++)if((1<<i)&(s>>10))
		{
			(dp+=getDP(n-1,s&(~(1<<i)),i==Narray[n]))%=MOD;
		}
		return dp;
	}
}
LL getFirstDP(const int n,const int s)
{
//	printf("getFirstDP(%d,%d)\n",n,s);
	if(TEN[n]>N)return 0;
	LL dp=0;
	for(int i=1;i<10;i++)
	{
		if((1<<i)&(s>>10))(dp+=getDP(n-1,s&(~(1<<i)),TEN[n]*(i+1)>N))%=MOD;
		if(TEN[n]*(i+1)>N)
		{
//			printf("N=%d,i=%d,Narray[%d]=%d\n",N,i,n,Narray[n]);
			assert(i==Narray[n]);
			break;
		}
	}
	return dp;
}
LL getWAY(const int s)
{
//	printf("getWAY(%d)\n",s);
	LL &dp=WAY[s];
	if(dp!=-1)return dp;
	dp=0;
	for(int i=0;i<9;i++)(dp+=getFirstDP(i,(1+(1<<10))*s))%=MOD;
//	printf("getWAY(%d)=%lld\n",s,dp);
	return dp;
}
LL getANS(const int s)
{
//	printf("getANS(%d)\n",s);
	LL &dp=ANS[s];
	if(dp!=-1)return dp;
	dp=getWAY(s);//getWAY(0)==0
	for(int a=s;a>=(s^a);a=(a-1)&s)
	{
		(dp+=getWAY(a)*getANS(s^a))%=MOD;
	}
//	printf("getANS(%d)=%lld\n",s,dp);
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	TEN[0]=1;
	for(int i=1;i<9;i++)TEN[i]=TEN[i-1]*10;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0,n=N;i<9;i++)Narray[i]=n%10,n/=10;
		for(int i=0;i<(1<<10);i++)WAY[i]=ANS[i]=-1;
		WAY[0]=ANS[0]=0;
		for(int i=0;i<9;i++)for(int j=0;j<(1<<20);j++)DP[i][j]=-1;
		static int kase=0;
		LL ans=0;
		for(int i=0;i<(1<<10);i++)(ans+=getANS(i))%=MOD;
		printf("Case %d: %lld\n",++kase,ans);
	}
	return 0;
}
