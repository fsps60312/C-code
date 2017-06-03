#include<cstdio>
#include<cstdlib>
long long n;
int main()
{
	while(scanf("%lld",&n)==1)
	{
		if(n<3) break;
		n-=3;
		//if(!n%2)
		{
			long long a=n/2;
			printf("%lld\n",((n*n+n)*(a+1)+(-2-4*n)*(a*(a+1)/2)+4*a*(a+1)*(2*a+1)/6)/2);
		}
		//else
		{
			
		}
	}
	return 0;
}
