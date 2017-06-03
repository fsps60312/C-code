#include<cstdio>
#define LL long long
LL K1,K2;
LL pow(LL v,LL p,LL mod)
{
	LL ans=1LL;
	while(p)
	{
		if(p&1LL)
		{
			ans*=v;
			ans%=mod;
		}
		v*=v;
		v%=mod;
		p>>=1;
	}
	return ans;
}
bool dfs(int dep,LL v,LL d)
{
	printf("%d:%lld\n",dep,v);
	if(dep==12)
	{
		if(v>=100000000000LL&&pow(K1,v,d*10LL)==v)
		{
			printf("%lld",v);
			return true;
		}
		return false;
	}
	LL mod=d*10LL;
	for(LL i=0LL,K2=v;i<10LL;i++,K2+=d)
	{
		if(pow(K1,K2,mod)!=K2)continue;
		if(dfs(dep+1,K2,d*10LL))return true;
	}
	return false;
}
int main()
{
	int kase=1;
	while(scanf("%lld",&K1)==1)
	{
		printf("Case %d: Public Key = %lld Private Key = ",kase++,K1);
		dfs(0,0LL,1LL);
		puts("");
	}
	return 0;
}
