#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
const LL MAX_N=285112LL;
//const LL INF=9223372036854775807LL;
LL rankR_DP[21][19];
LL GetRankR(const int digitPos,const int remainder,const int n)
{
	LL &dp=rankR_DP[digitPos][remainder];
	if(dp!=-1)return dp;
	if(digitPos==0)return dp=min(remainder+1,10);
	dp=0;
	for(int digit=0;digit<=9&&digit<=remainder;digit++)
	{
		const int nxtRemainder=(remainder-digit)*2+(int)((n>>(digitPos-1))&1);
		dp+=GetRankR(digitPos-1,min(nxtRemainder,18),n);
	}
	return dp;
}
LL rankL_DP[21][19];
int GetBinaryNumber(const LL x)
{
	if(x==1)return 0;
	for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankR_DP[i][j]=-1,rankL_DP[i][j]=0;
	int ans=0;
	++rankL_DP[20][0];
	for(int digitPos=19;digitPos>=0;digitPos--)
	{
		ans|=1<<digitPos;
		for(int i=0;i<=18;i++)rankR_DP[digitPos+1][i]=-1;
		LL *preDpL=rankL_DP[digitPos+1],*dpL=rankL_DP[digitPos];
		LL tmp=0;
		for(int i=0;i<=18;i++)tmp+=preDpL[i]*GetRankR(digitPos+1,i,ans);
		int flag=1;
		if(tmp>=x)
		{
			ans-=1<<digitPos;
//			for(int i=0;i<=18;i++)rankR_DP[digitPos+1][i]=-1;
			flag=0;
		}
		for(int remainder=0;remainder<=18;remainder++)if(preDpL[remainder])
		{
			const LL dp=preDpL[remainder];
			for(int digit=0;digit<=9&&digit<=remainder;digit++)
			{
				dpL[min(((remainder-digit)<<1)+flag,18)]+=dp;
			}
		}
	}
	return ans+1;
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
unsigned long long Solve(const LL x)
{
	const int bn=GetBinaryNumber(x);
//	printf("bn=%lld\n",bn);
	LL tmp=0;
	for(int i=0;i<=18;i++)tmp+=rankL_DP[0][i]*min(i+1,10);
	const LL goal=x-(bn==0?0:tmp);
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
