#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
const LL MAX_N=285112LL;
//const LL INF=9223372036854775807LL;
//LL cnt_DP[60][19];
//LL GetCnt(const int digitPos,const int remainder)
//{
//	LL &dp=cnt_DP[digitPos][remainder];
//	if(dp!=-1)return dp;
//	if(digitPos==0)return dp=min(remainder+1,10);
//	dp=0;
//	for(int digit=0;digit<=9&&digit<=remainder;digit++)
//	{
//		const int nxtRemainder=(remainder-digit)*2+1;
//		dp+=GetCnt(digitPos-1,min(nxtRemainder,18));
//	}
//	return dp;
//}
LL rank_DP[60][19];
LL GetRank(const int digitPos,const int remainder,const LL n)
{
	LL &dp=rank_DP[digitPos][remainder];
	if(dp!=-1)return dp;
	if(digitPos==0)return dp=min(remainder+1,10);
	dp=0;
	for(int digit=0;digit<=9&&digit<=remainder;digit++)
	{
		const int nxtRemainder=(remainder-digit)*2+(int)((n>>(digitPos-1))&1);
		dp+=GetRank(digitPos-1,min(nxtRemainder,18),n);
	}
	return dp;
}
LL GetRank(const LL n)
{
	for(int i=0;i<60;i++)for(int j=0;j<=18;j++)rank_DP[i][j]=-1;
	return GetRank(59,0,n);
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
//	for(int i=0;i<60;i++)for(int j=0;j<=18;j++)cnt_DP[i][j]=-1;
	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		LL x;scanf("%lld",&x);
		printf("%llu\n",Solve(x));
	}
	return 0;
}
