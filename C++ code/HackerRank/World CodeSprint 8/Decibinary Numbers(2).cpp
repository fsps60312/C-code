#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MAX_X=10000000000000000LL;
//vector<LL>digitCntOfBinary_cntOfCase;
LL digitCntOfBinary_cntOfCase_DP[100][18];
void Build_digitCntOfBinary_cntOfCase()
{
	for(int i=0;i<18;i++)digitCntOfBinary_cntOfCase_DP[0][i]=0;
	for(int i=0;i<=9;i++)++digitCntOfBinary_cntOfCase_DP[0][i]=1;
	for(int digitCntOfBinary=0;digitCntOfBinary+1<100;digitCntOfBinary++)
	{
		const LL *dp=digitCntOfBinary_cntOfCase_DP[digitCntOfBinary];
		LL *nxtDp=digitCntOfBinary_cntOfCase_DP[digitCntOfBinary+1];
		for(int i=0;i<18;i++)nxtDp[i]=0;
		for(int remain=0;remain<18;remain++)if(dp[remain])
		{
			for(int digit=0;digit<=9;digit++)
			{
				const int nxtRemain=remain/2+digit;
				nxtDp[nxtRemain]+=dp[remain];
			}
		}
		printf("%lld %lld\n",nxtDp[0]+nxtDp[1],nxtDp[0]);
		if(nxtDp[0]+nxtDp[1]>MAX_X)break;
	}
}
LL Get_binaryNumber(const LL x,const int digitCnt)
{
	
}
LL Get_binaryNumber(const LL x)
{
	for(int i=0;;i++)if(digitCntOfBinary_cntOfCase_DP[i][0]>=x)return Get_binaryNumber(x,i);
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
