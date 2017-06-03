#include<cstdio>
#include<cstdlib>
int T,n;
long long pow(long long a,int b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
			ans%=1000000007;
		}
		a*=a;
		a%=1000000007;
		b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		//ans is n*2^(n-1)
		printf("Case #%d: %lld\n",kase,n*pow(2,n-1)%1000000007);
	}
	return 0;
}
