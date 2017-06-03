#include<cstdio>
#include<vector>
#define LL long long
using namespace std;
const LL MOD=1000000000;
int N;
LL DP[300][300];
char TAP[301];
LL getDP(int l,int r)
{
	if(l>r)return 0;
	LL &dp=DP[l][r];
	if(dp!=-1)return dp;
	if(l==r)return dp=1;
	if(TAP[l]!=TAP[r])return dp=0;
	dp=0;
	for(int i=l+1;i<=r;i++)
	{
		if(TAP[i]!=TAP[l])continue;
		dp+=getDP(l+1,i-1)*getDP(i,r);
		dp%=MOD;
	}
	return dp;
}
LL solve()
{
	N=-1;while(TAP[++N]);
	for(int i=N-1;i>=0;i--)
	{
		for(int j=i;j>=0;j--)
		{
			DP[j][i]=-1;
		}
	}
	return getDP(0,N-1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",TAP)==1)
	{
		printf("%lld\n",solve());
	}
	return 0;
}
