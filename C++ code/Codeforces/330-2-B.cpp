#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
LL N,K,A[100000],B[100000];
int main()
{
	scanf("%I64d%I64d",&N,&K);
	for(LL i=0;i<N/K;i++)scanf("%I64d",&A[i]);
	for(LL i=0;i<N/K;i++)scanf("%I64d",&B[i]);
	LL ans=1LL;
	for(LL i=0LL;i<N/K;i++)
	{
		const LL a=A[i],b=B[i];
		LL l=0LL;
		LL n=b;
		l+=n/a,n%=a;
		l%=MOD;
		for(LL j=1LL;j<K;j++)
		{
			n*=10LL,l*=10LL;
			l+=n/a,n%=a;
			l%=MOD;
		}
		if(n==0LL)l--;
		LL r=0LL;
		n=b;
		r+=n/a,n%=a;
		r%=MOD;
		for(LL j=1LL;j<K;j++)
		{
			n*=10LL,n+=9LL,r*=10LL;
			r+=n/a,n%=a;
			r%=MOD;
		}
		LL all=0LL;
		n=9LL;
		all+=n/a,n%=a;
		all%=MOD;
		for(LL j=1LL;j<K;j++)
		{
			n*=10LL,n+=9LL,all*=10LL;
			all+=n/a,n%=a;
			all%=MOD;
		}
		all++;
//		printf("l=%I64d,r=%I64d,all=%I64d\n",l*a,r*a,all);
		LL ta=((all-(r-l))%MOD+MOD)%MOD;
		ans*=ta,ans%=MOD;
	}
	printf("%I64d\n",ans);
	return 0;
}
