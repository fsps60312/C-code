#include<cstdio>
#include<cstdlib>
long long p[10000],ans,n,t;
int main()
{
	p[0]=2,p[1]=3;
	for(long long i=2,j;;i++)
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
		if(p[i]>=65536)
		{
			//printf("%lld\n",i);
			break;
		}
	}
	long long kase=1;
	while(scanf("%lld",&n)==1&&n)
	{
		ans=0,t=0;
		for(long long i=0,j=0,k=1;p[i]<=n/p[i];i++)
		{
			while(n%p[i]==0)
			{
				j++;
				n/=p[i];
				k*=p[i];
			}
			if(j)
			{
				ans+=k;
				k=1,j=0,t++;
			}
		}
		if(n>1) ans+=n,t++;
		if(t<=1) ans+=2-t;
		printf("Case %lld: %lld\n",kase++,ans);
	}
	return 0;
}
