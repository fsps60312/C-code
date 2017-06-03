#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
LL GetRank(const LL n)
{
	static LL dp[60][19];//digitPos, remainder
	int numberLength=0;
	while((1<<numberLength)<=n)++numberLength;
	for(int i=0;i<=18;i++)dp[numberLength][i>>1]=0;
	++dp[numberLength][0];
	for(int i=numberLength-1;i>=0;i--)
	{
		for(int j=0;j<=18;j++)dp[i][j]=0;
		for(int remainder=0;remainder<=18;remainder++)
		{
			if(dp[i+1][remainder])
			{
				const LL v=dp[i+1][remainder];
				for(int digit=0;digit<=9&&digit<=remainder;digit++)
				{
					const int nxtRemainder=(remainder-digit)*2;
					dp[i][min(nxtRemainder+(int)((n>>i)&1),18)]+=v;
				}
			}
		}
	}
	LL ans=0;
	for(int i=0;i<=18;i++)ans+=dp[0][i]*min(i+1,10);
	return ans;
}
LL GetDeciRank(vector<int>n,const LL rawN)
{
	static LL dp[60][2][18];//digitPos, upBoundReached, remainder
	int numberLength=0;
	while((1<<numberLength)<=rawN)++numberLength;
	while((int)n.size()<=numberLength)n.push_back(0);
	for(int i=0;i<18*2;i++)dp[numberLength][i&1][i>>1]=0;
	++dp[numberLength][1][0];
	for(int i=numberLength-1;i>=0;i--)
	{
		for(int j=0;j<18*2;j++)dp[i][j&1][j>>1]=0;
		for(int remainder=0;remainder<18;remainder++)
		{
			if(dp[i+1][0][remainder])
			{
				const LL v=dp[i+1][0][remainder];
				for(int digit=0;digit<=9&&digit<=remainder;digit++)
				{
					const int nxtRemainder=(remainder-digit)*2;
					if(nxtRemainder<18)dp[i][0][nxtRemainder+(int)((rawN>>i)&1)]+=v;
				}
			}
			if(dp[i+1][1][remainder])
			{
				const LL v=dp[i+1][1][remainder];
				for(int digit=0;digit<n[i+1]&&digit<=remainder;digit++)
				{
					const int nxtRemainder=(remainder-digit)*2;
					if(nxtRemainder<18)dp[i][0][nxtRemainder+(int)((rawN>>i)&1)]+=v;
				}
				dp[i][1][(remainder-n[i+1])*2+(int)((rawN>>i)&1)]+=v;
			}
		}
	}
	LL ans=0;
	for(int i=0;i<=9;i++)ans+=dp[0][0][i];
	LL check=ans+1;
	ans+=dp[0][1][n[0]];
//	printf("check=%lld, ans=%lld\n",check,ans);
	assert(ans==check);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	LL i=260000;
	while(true)
	{
		printf("i=%lld, rank=%lld\n",i,GetRank(i));
		if(GetRank(i)>MAX_X)break;
		i++;
	}
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		LL x;scanf("%lld",&x);
//		Solve(x);
	}
	return 0;
}
