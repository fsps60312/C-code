#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int T;
LL N,M;
LL func(int n,int m)
{
    LL result=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(i!=j)result+=(LL)(n%i)*(m%j);
            //(n-n/i*i)(m-m/j*j)
            //n*m-n(m/j*j)-m(n/i*i)+(n/i*i)(m/j*j)
            
    return result;
}
LL GetSum(const LL &n)
{
	LL ans=n%MOD*n%MOD;
//	printf("ans=%lld\n",ans);
//	printf("n=%lld\n",n);
	for(LL l=1LL,r;l<=n;)
	{
		r=n/(n/l);
		LL aaa=ans;
		ans-=(n/l)%MOD*(((l+r)*(r-l+1LL))>>1)%MOD;
//		printf("(%lld,%lld)%lld\n",l,r,aaa-ans);
		ans%=MOD;
//		printf("ans=%lld\n",ans);
		l=++r;
	}
	return ans;
}
LL min(const LL &a,const LL &b){return a<b?a:b;}
int main()
{
//	for(LL i=1;i<=10LL;i++)printf("%lld\n",GetSum(i));return 0;
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		LL ans=GetSum(N)%MOD*GetSum(M)%MOD;
		for(LL i=1LL;i<=min(N,M);i++)ans-=(N%i)*(M%i),ans%=MOD;
		ans=(ans%MOD+MOD)%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
