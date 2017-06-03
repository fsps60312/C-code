#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL N;
LL Sqrt(const LL v)
{
	LL l=0,r=100000000LL;
	while(l<r)
	{
		const LL mid=(l+r+1LL)/2LL;
		if(mid*mid<=v)l=mid;
		else r=mid-1LL;
	}
	return r;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		LL ans=0LL;
		for(LL y=1LL;y<N;y++)
		{
			ans+=Sqrt(N*N-y*y);
		}
		ans*=4LL;
		ans+=N*4LL+1LL;
		printf("%lld\n%lld\n",N,ans);
	}
	return 0;
}
