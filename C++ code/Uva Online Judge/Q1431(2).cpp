#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N,D,E;
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
LL Sqrt(const LL &a)
{
	LL l=0LL,r=2147483647LL;
	while(l<r)
	{
		const LL mid=(l+r)/2LL;
		if(mid*mid<a)l=mid+1LL;
		else r=mid;
	}
//	assert(l*l==a);
	assert(l*l<=a);
	return l;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&N,&D,&E)==3&&!(N==0LL&&D==0LL&&E==0LL))
	{
		const LL all=D*E;
		LL v;
		for(LL n=1LL;;n++)if(all%n==1LL)
		{
			v=(all-1LL)/n;//v=N-p-q+1=(p-1)(q-1)
			if(v<N&&Gcd(E,v)==1LL)break;
		}
		const LL add=N-v+1LL;
		const LL sub=Sqrt(add*add-4LL*N);
		LL p=(add-sub)/2LL,q=(add+sub)/2LL;
		static int kase=1;
		printf("Case #%d: %lld %lld\n",kase++,p,q);
	}
	return 0;
}
