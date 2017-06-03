#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
bool IsPrime(const int n)
{
	switch(n)
	{
		case 2:
		case 3:
		case 5:
		case 7:
		case 11:
		case 13:
		case 17:
		case 19:
		case 23:
		case 29:
		case 31:
		case 37:
		case 41:
		case 43:
		case 47:
			return true;
		default:
			assert(0<=n&&n<=50);
			return false;
	}
}
int DigitSum(int n)
{
	assert(0<=n&&n<=99999);
	return n/10000+n/1000%10+n/100%10+n/10%10+n%10;
}
bool IsDigitSumPrime(int n)
{
	return IsPrime(DigitSum(n));
}
LL Sum(const LL *dp)
{
	LL ans=0;
	for(int i=0;i<100000;i++)ans+=dp[i];
	return ans;
}
int N;
LL DP[2][100000];
vector<int>VIS[2];
LL Solve()
{
	if(N==1)return 9;
	if(N==2)return 90;
	VIS[0].clear(),VIS[1].clear();
	for(int i=0;i<100000;i++)DP[0][i]=DP[1][i]=0;
	VIS[0].clear();
	VIS[1].clear();
	int d=0;
	for(int i=10;i<=99;i++)++DP[d][i],VIS[d].push_back(i);
	for(int counter=3;counter<=N;counter++)
	{
		d^=1;
		//assert(VIS[d].empty());
		//for(int i=0;i<100000;i++)assert(DP[d][i]==0);
		for(const int i:VIS[d^1])
		{
			LL &dp=DP[d^1][i];
			assert(dp>0);
			for(int n=0;n<=9;n++)
			{
				if(IsDigitSumPrime(i*10%1000+n)
				 &&IsDigitSumPrime(i*10%10000+n)
				 &&IsDigitSumPrime(i*10%100000+n))(DP[d][i*10%100000+n]+=dp)%=MOD,VIS[d].push_back(i*10%100000+n);
			}
			dp=0;
		}
		VIS[d^1].clear();
		sort(VIS[d].begin(),VIS[d].end());
		VIS[d].resize(unique(VIS[d].begin(),VIS[d].end())-VIS[d].begin());
	}
	return Sum(DP[d]);
}
int main()
{
	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		scanf("%d",&N);
		printf("%lld\n",Solve());
	}
	return 0;
}
