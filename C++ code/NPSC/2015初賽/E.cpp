#include<cstdio>
typedef long long LL;
const LL INF=9223372036854775807LL;
LL T,N;
LL Zero(LL n)
{
	LL ans=0LL;
	while(n)ans+=n/5LL,n/=5LL;
	return ans;
}
LL Solve()
{
	if(N==0)return 0LL;
	LL l=1LL,r=INF;
	while(l<r)
	{
		const LL mid=l+(r-l)/2LL;
		if(Zero(mid)<N)l=mid+1LL;
		else r=mid;
	}
	if(Zero(l)==N)return l;
	return -1LL;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&N);
		printf("%lld\n",Solve());
	}
	return 0;
}
