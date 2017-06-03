#include<cstdio>
#include<cstdlib>
int T,n;
int digitsum(int a)
{
	int b=a;
	while(a)
	{
		b+=a%10;
		a/=10;
	}
	return b;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=45;i++)
		{
			if(digitsum(n-i)==n) ans=i;
		}
		if(ans) printf("%d\n",n-ans);
		else printf("0\n");
	}
	return 0;
}
