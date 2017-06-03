#include<cstdio>
typedef long long LL;
LL X;
int main()
{
	while(scanf("%lld",&X)==1)
	{
		LL l=0LL,r=2147483647LL,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			LL v;
			if(mid%2LL==0LL)v=mid/2LL*(mid+1LL);
			else v=mid*((mid+1LL)/2LL);
			if(X>v)l=mid+1;
			else r=mid;
		}
		printf("%lld\n",l);
	}
	return 0;
}
