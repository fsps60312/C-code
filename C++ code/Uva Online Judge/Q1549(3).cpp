#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		LL ans=0LL;
		for(LL y=1LL,v=N;y<N;++y)
		{
			for(;v*v+y*y>N*N;--v);
			ans+=v;
		}
		ans*=4LL;
		ans+=N*4LL+1LL;
		printf("%lld\n%lld\n",N,ans);
	}
	return 0;
}
