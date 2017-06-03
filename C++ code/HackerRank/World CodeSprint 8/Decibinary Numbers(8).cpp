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
LL GetRankR(const int digitPos,const int remainder,const LL n)
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
LL GetRankL(const int digitPos,const int remainder,const LL n)
{
	LL &dp=rankL_DP[digitPos][remainder];
	if(dp!=-1)return dp;
	if(digitPos==20)return dp=(remainder==0?1:0);
	dp=0;
	if((remainder&1)==(int)((n>>digitPos)&1))
	{
		for(int digit=0;digit<=9;digit++)
		{
			const int nxtRemainder=remainder/2;
			dp+=GetRankL(digitPos+1,nxtRemainder+digit,n);
		}
	}
	return dp;
}
LL GetBinaryNumber(const LL x)
{
	if(x==1)return 0;
	for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankR_DP[i][j]=rankL_DP[i][j]=-1;
	LL ans=0;
	for(int digitPos=19;digitPos>=0;digitPos--)
	{
		ans+=1LL<<digitPos;
		for(int i=0;i<=18;i++)rankR_DP[digitPos+1][i]=rankL_DP[digitPos][i]=-1;
		for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankR_DP[i][j]=rankL_DP[i][j]=-1;
		LL tmp=0;
		for(int i=0;i<=18;i++)tmp+=GetRankL(digitPos+1,i,ans)*GetRankR(digitPos+1,i,ans);
//		if(true)
//		{
//			for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankR_DP[i][j]=rankL_DP[i][j]=-1;
//			tmp=GetRankR(20,0,ans);
//		}
		printf("ans=%lld, tmp=%lld\n",ans,tmp);
		if(tmp>=x)
		{
//			puts("a");
			ans-=1LL<<digitPos;
			for(int i=0;i<=18;i++)rankR_DP[digitPos+1][i]=rankL_DP[digitPos][i]=-1;
		}
//		else puts("b");
	}
	return ans+1;
//	LL l=0,r=MAX_N;
//	while(l<r)
//	{
//		const LL mid=(l+r)/2;
//		if(GetRank(mid)<x)l=mid+1;
//		else r=mid;
//	}
//	return r;
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
	const LL bn=GetBinaryNumber(x);
	printf("bn=%lld\n",bn);
	for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankR_DP[i][j]=-1;
	const LL goal=x-(bn==0?0:GetRankR(20,0,bn-1));
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
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		LL x;scanf("%lld",&x);
		printf("%llu\n",Solve(x));
	}
	return 0;
}
