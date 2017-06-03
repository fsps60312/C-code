#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
//vector<LL>digitCntOfBinary_cntOfCase;
vector<LL>digitCntOfBinary_cntOfCase_DP[100][18];
void Build_digitCntOfBinary_cntOfCase()
{
	for(int digitCntOfBinary=0;;digitCntOfBinary++)
	{
		vector<LL>*dp=digitCntOfBinary_cntOfCase_DP[digitCntOfBinary];
		for(int i=0;i<18;i++)dp[i].clear(),dp[i].resize(digitCntOfBinary+1,0LL);
		++dp[0][digitCntOfBinary];
		++dp[1][digitCntOfBinary];
		for(int i=digitCntOfBinary;i>=1;i--)
		{
			for(int remain=0;remain<18;remain++)if(dp[remain][i])
			{
				for(int digit=0;digit<=9&&digit<=remain;digit++)
				{
					for(int nxtbit=0;nxtbit<=1;nxtbit++)
					{
						const int nxt_remain=(remain-digit)*2+nxtbit;
						if(nxt_remain<18)dp[nxt_remain][i-1]+=dp[remain][i];
					}
				}
			}
		}
//		LL ans=(digitCntOfBinary_cntOfCase.empty()?0:digitCntOfBinary_cntOfCase.back())+dp[0][0];
//		digitCntOfBinary_cntOfCase.push_back(ans);
//		printf("%lld\n",dp[0][0]);
		if(dp[0][0]>MAX_X)break;
	}
}
LL Get_binaryNumber(const LL x,const int digitCnt)
{
	if()
	vector<LL>dp[18];
	for(int i=0;i<18;i++)dp[i].clear(),dp[i].resize(digitCnt+1,0LL);
	LL ans=0LL;
	assert(0);
//	for(int i=digitCntOfBinary;i>=1;i--)
//	{
////		if(x>=digitCntOfBinary_cntOfCase_DP[i-1][0][0])x-=digitCntOfBinary_cntOfCase_DP[i-1][0][0],++dp[0][i];
//		for(int remain=0;remain<18;remain++)if(dp[remain][i])
//		{
//			for(int digit=0;digit<=9&&digit<=remain;digit++)
//			{
//				for(int nxtbit=0;nxtbit<=1;nxtbit++)
//				{
//					const int nxt_remain=(remain-digit)*2+nxtbit;
//					if(nxt_remain<18)dp[nxt_remain][i-1]+=dp[remain][i];
//				}
//			}
//		}
//	}
}
LL Get_binaryNumber(const LL x)
{
	for(int i=0;;i++)if(digitCntOfBinary_cntOfCase_DP[i][0][0]>=x)return Get_binaryNumber(x,i);
}
void Solve(const LL x)
{
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	Build_digitCntOfBinary_cntOfCase();
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		LL x;scanf("%lld",&x);
		Solve(x);
	}
	return 0;
}
