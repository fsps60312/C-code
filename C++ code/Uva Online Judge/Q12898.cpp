#include<cstdio>
typedef long long LL;
int T;
LL A,B;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&A,&B);
		int d;
		LL ans=0LL;
		for(d=62;d>=0;d--)
		{
			if((A&(1LL<<d))!=(B&(1LL<<d)))break;
			ans|=A&(1LL<<d);
		}
		LL anda=ans,ora=ans;
		for(;d>=0;d--)anda|=(1LL<<d);
		static int kase=1;
		printf("Case %d: %lld %lld\n",kase++,anda,ora);
	}
	return 0;
}
