#include<cstdio>
typedef long long LL;
LL N,K;
LL min(const LL &a,const LL &b){return a<b?a:b;}
int main()
{
	while(scanf("%lld%lld",&N,&K)==2)
	{
		LL ans=K*N;
		//for(LL i=1LL;i<=N;i++)ans-=K/i;
		for(LL l=1LL,r;l<=N&&K/l>0LL;)
		{
			r=min(N,K/(K/l));
			ans-=K/l*((r+l)*(r-l+1LL)/2LL);
			l=++r;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
