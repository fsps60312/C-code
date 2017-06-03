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
void Trans(const int digitPos,const int flag)
{
	LL *preDp=rankR_DP[digitPos-1],*nowDp=rankR_DP[digitPos];
	for(int remainder=0;remainder<=18;remainder++)
	{
		LL &dp=nowDp[remainder]=0;
		for(int digit=min(9,remainder);digit>=0;digit--)
		{
			dp+=preDp[min(((remainder-digit)<<1)+flag,18)];
		}
	}
}
LL rankL_DP[21][19];
int GetBinaryNumber(const LL x)
{
	if(x==1)return 0;
	for(int i=0;i<=20;i++)for(int j=0;j<=18;j++)rankL_DP[i][j]=0;
	for(int i=0;i<=18;i++)rankR_DP[0][i]=min(i+1,10);
	for(int digitPos=1;digitPos<=19;digitPos++)Trans(digitPos,0);
	int ans=0;
	++rankL_DP[20][0];
	for(int digitPos=19;digitPos>=0;digitPos--)
	{
		ans|=1<<digitPos;
		for(int i=0;i<=18;i++)rankR_DP[digitPos+1][i]=-1;
		LL *preDpL=rankL_DP[digitPos+1],*dpL=rankL_DP[digitPos];
		Trans(digitPos+1,1);
		LL tmp=0;
		for(int i=0;i<=18;i++)tmp+=preDpL[i]*rankR_DP[digitPos+1][i];
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
			for(int digit=min(remainder,9);digit>=0;digit--)
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
	for(int digit=min(9,remainder),flag=(int)(rawN>>(digitPos-1)&1);digit>=0;digit--)
	{
		const int nxtRemainder=((remainder-digit)<<1)+flag;
		if(nxtRemainder>=18)break;
		dp+=GetDeciCnt(digitPos-1,nxtRemainder,rawN);
	}
	return dp;
}
void GetDeci(const int digitPos,const int remainder,const LL rawN,LL rank,vector<int>&ans)
{
	if(digitPos==0)
	{
//		assert(rank==1);
//		assert(0<=remainder&&remainder<=9);
		ans.push_back(remainder);
		return;
	}
	for(int digit=0,limit=min(9,remainder),flag=(int)(rawN>>(digitPos-1)&1);digit<=limit;digit++)
	{
		const int nxtRemainder=((remainder-digit)<<1)+flag;
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
	for(int ccc=0;querycount--;ccc++)
	{
		LL x;scanf("%lld",&x);
		printf("%llu\n",Solve(x));
//		assert(ccc<10000);
	}
	return 0;
}
