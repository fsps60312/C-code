#include<cstdio>
#define LL long long
LL K1,K2;
LL ModMul(LL &a,LL &b,LL &mod)
{
	LL v1=a>>20,v2=a&((1LL<<20)-1LL);
	return ((((v1*b)%mod)<<20)%mod+v2*b%mod)%mod;
}
LL pow(LL v,LL p,LL mod)
{
	LL ans=1LL;
	while(p)
	{
		if(p&1LL)
		{
			ans=ModMul(ans,v,mod);
		}
		v=ModMul(v,v,mod);
		p>>=1;
	}
	return ans;
}
bool dfs(int dep,LL v,LL mod)
{
	if(dep==12)
	{
		if(v>=100000000000LL&&pow(K1,v,mod)==v)
		{
			printf("%lld",v);
			return true;
		}
		return false;
	}
//	printf("%d:%lld\n",dep,v);
	LL d=mod*10LL,K2=v;
	for(int i=0;i<10;i++,K2+=mod)
	{
		if(pow(K1,K2,mod)!=v)continue;
		if(dfs(dep+1,K2,d))return true;
	}
	return false;
}
int main()
{
	int kase=1;
	while(scanf("%lld",&K1)==1&&K1)
	{
		printf("Case %d: Public Key = %lld Private Key = ",kase++,K1);
		for(LL v=0LL;v<10LL;v++)
		{
			if(dfs(1,v,10LL))break;
		}
		puts("");
	}
	return 0;
}
