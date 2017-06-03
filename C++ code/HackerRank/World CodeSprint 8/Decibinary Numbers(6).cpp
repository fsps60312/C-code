#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
const LL MAX_N=285112LL;
const LL INF=9223372036854775807LL;
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
LL deciCnt_DP[21][18];
LL GetDeciCnt(const int digitPos,const int remainder,const LL rawN)
{
	LL &dp=deciCnt_DP[digitPos][remainder];
	if(dp!=-1)return dp;
	if(digitPos==0)return dp=(remainder<=9?1:0);
	dp=0;
	for(int digit=0;digit<=9&&digit<=remainder;digit++)
	{
		const int nxtRemainder=(remainder-digit)*2+(int)(rawN>>(digitPos-1)&1);
		if(nxtRemainder<18)dp+=GetDeciCnt(digitPos-1,nxtRemainder,rawN);
	}
	return dp;
}
void GetDeci(const int digitPos,const int remainder,const LL rawN,LL rank,vector<int>&ans)
{
	if(digitPos==0)
	{
		assert(rank==1);
		assert(0<=remainder&&remainder<=9);
		ans.push_back(remainder);
		return;
	}
	for(int digit=0;digit<=9&&digit<=remainder;digit++)
	{
		const int nxtRemainder=(remainder-digit)*2+(int)(rawN>>(digitPos-1)&1);
		if(nxtRemainder<18)
		{
			const LL cnt=GetDeciCnt(digitPos-1,nxtRemainder,rawN);
			if(cnt<rank)rank-=cnt;
			else
			{
				GetDeci(digitPos-1,nxtRemainder,rawN,rank,ans);
				ans.push_back(digit);
				return;
			}
		}
	}
	assert(0);
}
LL GetBinaryNumber(const LL x)
{
	LL l=0,r=MAX_N;
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(GetRank(mid)<x)l=mid+1;
		else r=mid;
	}
	return r;
}
unsigned long long Solve(const LL x)
{
	const LL bn=GetBinaryNumber(x);
//	printf("bn=%lld\n",bn);
	const LL goal=x-(bn==0?0:GetRank(bn-1));
//	printf("goal=%lld\n",goal);
	assert(0<goal);
	vector<int>ansArray;
	for(int i=0;i<=20;i++)for(int j=0;j<18;j++)deciCnt_DP[i][j]=-1;
	GetDeci(20,0,bn,goal,ansArray);
	LL ans=0;
	for(int i=(int)ansArray.size()-1;i>=0;i--)ans*=10,ans+=ansArray[i];
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		LL x;scanf("%lld",&x);
		printf("%llu\n",Solve(x));
	}
	return 0;
}
