#include<cstdio>
#include<cstdlib>
long long T,n,m,kase=1;
long long gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		//if(n==1||m==1) printf("Case %lld: %lld\n",kase++,1);
		//else
		printf("Case %lld: %lld\n",kase++,(n+m)/gcd(n,m));
	}
	return 0;
}
