#include<cstdio>
#include<cstdlib>
long long a,b,n,t;
long long powt[51];
long long gcd(long long a,long long b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
int main()
{
	//freopen("in.txt","r",stdin);
	powt[0]=1;
	while(scanf("%lld%lld",&n,&t)==2)//n bead, t color
	{
		for(long long i=1;i<=n;i++) powt[i]=powt[i-1]*t;
		a=0;
		for(long long i=1;i<=n;i++)
		{
			//n/gcd(i,n): how much must same color
			//n/(n/gcd(i,n)): how many color can draw
			//t^(gcd(i,n)): sum of method to draw color that make it the same after change
			a+=powt[gcd(n,i)];
		}
		b=0;
		if(n&1)
		{
			//sum of color can draw: (n+1)/2
			b=n*powt[(n+1)/2];
		}
		else
		{
			//sum of color can draw: n/2+(n/2+1)
			b+=n/2*(powt[n/2]+powt[n/2+1]);
		}
		printf("%lld %lld\n",a/n,(a+b)/2/n);
	}
	return 0;
}
