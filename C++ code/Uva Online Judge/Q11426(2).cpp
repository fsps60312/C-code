#include<cstdio>
#include<cstdlib>
long long euler[4000001];//how many coprime below
long long f[4000001];//sum: gcd(1,n)+gcd(2,n)+...+gcd(n-1,n)
//==sum: i*g(n,i), n%i==0
//==sum: i*euler(n/i), n%i==0
//	prove g(n,i)==euler(n/i)
//g(n,i):how many x<n make gcd(x,n)==i (n%i==0 of course)
//sum: gcd(x,n)==i == g(n,i)
//==sum: gcd(x/i,n/i)==1
//==how many coprime below n/i
//==euler(n/i)#
long long ans[4000001];//ans[n]==anns[n-1]+f[n]
long long n;
int main()
{
	for(int i=2;i<=4000000;i++)
	{
		euler[i]=0;
		f[i]=0;
	}
	euler[1]=1;
	for(int i=2;i<=4000000;i++)
	{
		if(!euler[i])
		{
			for(int j=i;j<=4000000;j+=i)
			{
				if(!euler[j])
				{
					euler[j]=j;
				}
				euler[j]=euler[j]*(i-1)/i;
			}
		}
	}
	for(int i=1;i<=4000000;i++)
	{
		for(int j=i*2;j<=4000000;j+=i)
		{
			f[j]+=i*euler[j/i];
		}
	}
	ans[1]=0;
	for(int i=2;i<=4000000;i++)
	{
		ans[i]=ans[i-1]+f[i];
	}
	while(scanf("%lld",&n)==1)
	{
		if(n==0) break;
		printf("%lld\n",ans[n]);
	}
	return 0;
}
