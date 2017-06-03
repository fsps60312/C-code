#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
bool IS_PRIME[51];
inline bool IsPrime(const int n)
{
	return IS_PRIME[n];
}
int DIGIT_SUM[100000];
inline int DigitSum(int n)
{
	return DIGIT_SUM[n];
}
inline bool IsDigitSumPrime(const int n)
{
	return IsPrime(DigitSum(n));
}
inline LL Sum(const LL *dp,const vector<int>&vis)
{
	LL ans=0;
	for(const int i:vis)ans+=dp[i];
	return ans;
}
bool IsAllDigitSumPrime_DP[100000][10];
inline bool IsAllDigitSumPrime(const int i,const int n)
{
	return IsAllDigitSumPrime_DP[i][n];
}
LL DP[2][100000];
vector<int>VIS[2];
LL ANS[400001];
void Solve()
{
	{
		int s[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
		for(int i=0;i<=50;i++)IS_PRIME[i]=false;
		for(int i=0;i<15;i++)IS_PRIME[s[i]]=true;
	}
	{
		for(int i=0;i<100000;i++)DIGIT_SUM[i]=i/10000+i/1000%10+i/100%10+i/10%10+i%10;
	}
	{
		for(int i=0;i<100000;i++)
		{
			for(int n=0;n<10;n++)IsAllDigitSumPrime_DP[i][n]=(IsDigitSumPrime(i*10%1000+n)
															&&IsDigitSumPrime(i*10%10000+n)
															&&IsDigitSumPrime(i*10%100000+n));
		}
	}
	ANS[1]=9;
	ANS[2]=90;
	VIS[0].clear(),VIS[1].clear();
	for(int i=0;i<100000;i++)DP[0][i]=DP[1][i]=0;
	VIS[0].clear();
	VIS[1].clear();
	int d=0;
	for(int i=10;i<=99;i++)++DP[d][i],VIS[d].push_back(i);
	for(int counter=3;counter<=400000;counter++)
	{
		d^=1;
		//assert(VIS[d].empty());
		//for(int i=0;i<100000;i++)assert(DP[d][i]==0);
		//if(counter%100000==0)printf("cnt=%d\n",(int)VIS[d^1].size());
		LL &ans=ANS[counter]=0;
		for(const int i:VIS[d^1])
		{
			LL &dp=DP[d^1][i];
			if(dp==0)continue;
			const int v=i*10%100000,vds=DigitSum(v);
			if(vds<=2)
			{
				for(int n=0;n<=9;n++)
				{
					if(IsAllDigitSumPrime(i,n))(DP[d][v+n]+=dp)%=MOD,VIS[d].push_back(v+n),ans+=dp;
				}
			}
			else
			{
				for(int n=(vds&1?0:1);n<=9;n+=2)
				{
					if(IsAllDigitSumPrime(i,n))(DP[d][v+n]+=dp)%=MOD,VIS[d].push_back(v+n),ans+=dp;
				}
			}
			ans%=MOD;
			dp=0;
		}
		VIS[d^1].clear();
	}
}
int N;
int main()
{
	Solve();
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		scanf("%d",&N);
		printf("%lld\n",ANS[N]);
	}
	return 0;
}
