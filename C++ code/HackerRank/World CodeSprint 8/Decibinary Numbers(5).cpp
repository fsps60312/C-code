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
LL GetDeciRank(vector<int>n,const LL rawN)
{
	static LL dp[60][2][19];//digitPos, upBoundReached, remainder
	int numberLength=59;
//	while((1<<numberLength)<=rawN)++numberLength;
	while((int)n.size()<=numberLength)n.push_back(0);
	for(int i=0;i<19*2;i++)dp[numberLength][i&1][i>>1]=0;
	++dp[numberLength][1][0];
	for(int i=numberLength-1;i>=0;i--)
	{
		for(int j=0;j<19*2;j++)dp[i][j&1][j>>1]=0;
		for(int remainder=0;remainder<=18;remainder++)
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
//				if((remainder-n[i+1])*2>=18)for(int j=i+1;j>=0;j--)n[j]=10;
//				if(n[i+1]>remainder)return INF;
				for(int digit=0;digit<n[i+1]&&digit<=remainder;digit++)
				{
					const int nxtRemainder=(remainder-digit)*2;
					if(nxtRemainder<18)dp[i][0][nxtRemainder+(int)((rawN>>i)&1)]+=v;
				}
//				if(n[i+1]<10)
				{
					const int nxtRemainder=(remainder-n[i+1])*2;
					if(nxtRemainder<18)dp[i][1][nxtRemainder+(int)((rawN>>i)&1)]+=v;
//					else return -INF;
				}
			}
		}
	}
	LL ans=0;
	for(int i=0;i<=9;i++)ans+=dp[0][0][i];
	LL check=ans+1;
	for(int i=0;i<=n[0];i++)ans+=dp[0][1][i];
//	if(ans!=check)
//	{
//		assert(ans==check-1);
//		return -INF;
//	}
//	printf("check=%lld, ans=%lld\n",check,ans);
//	assert(ans==check);
	return ans;
}
vector<int>GetNArray(unsigned long long n)
{
	vector<int>ans;
	while(n)ans.push_back((int)(n%10)),n/=10;
	return ans;
}
//LL ToDeciBinary(unsigned long long n)
//{
//	LL ans=0;
//	for(LL v=1;n;)
//	{
//		ans+=v*(int)(n%10);
//		n/=10;
//		v<<=1;
//	}
//	return ans;
//}
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
	printf("bn=%lld\n",bn);
	const LL goal=x-(bn==0?0:GetRank(bn-1));
	assert(0<goal);
	unsigned long long l=0ULL,r=10000000000000000000ULL;
	while(l<r)
	{
		const unsigned long long mid=l+(r-l)/2;
		printf("mid=%lld\n",mid);
		if(GetDeciRank(GetNArray(mid),bn)<goal)l=mid+1;
		else r=mid;
	}
	return r;
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
