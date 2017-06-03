#include<cstdio>
#include<cstdlib>
long long n,p[10000],ans2;
int main()
{
	p[0]=2,p[1]=3;
	for(int i=2,j;;i++)
	{
		p[i]=p[i-1];
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		if(p[i]>=100000)
		{
			//printf("%d\n",i);
			break;
		}
	}
	while(scanf("%lld",&n)==1&&n)
	{
		printf("%lld ",n);
		ans2=1;
		for(int i=0,j=0;p[i]*p[i]<=n;i++)
		{
			while(n%p[i]==0)
			{
				n/=p[i];
				j++;
			}
			if(j)
			{
				//ans1++;
				ans2*=j*2+1;
				j=0;
			}
		}
		if(n>1) ans2*=3;
		//ans2*=2;
		printf("%lld\n",(ans2+1)/2);
	}
	return 0;
}
