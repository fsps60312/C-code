#include<cstdio>
typedef long long LL;
LL T,N,A,B,C,CNT,SUM;
LL getSUM(LL a,LL b,LL c)
{
	LL ans=1LL;
	LL NOW=a+1LL;
	for(LL i=1LL;i<=b;i++,NOW++)
	{
		ans*=NOW;
		ans/=i;
	}
	for(LL i=1LL;i<=c;i++,NOW++)
	{
		ans*=NOW;
		ans/=i;
	}
//	LL i=1LL;
//	if(a)ans/=i++;
//	if(b)ans/=i++;
//	if(c)ans/=i++;
	printf("%lld %lld %lld => %lld\n",a,b,c,ans);
	return ans;
}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&A,&B,&C);
		N=A+B+C;
		SUM=getSUM(A,B,C);
		CNT=1LL;
		for(LL i=1LL,n;i<N;i++)
		{
			n=gcd(N,i);
			for(LL a=0LL,b,c;a<=A&&a<=n;a++)
			for(b=0LL;b<=B&&a+b<=n;b++)
			{
				c=n-a-b;
				if(c>C)continue;
				SUM+=getSUM(a,b,c);
			}
			CNT++;
		}
		if(N&1LL)
		{
			LL n=(N+1LL)>>1,sum=0LL;
			for(LL a=0LL,b,c;a<=A&&a<=n;a++)
			for(b=0LL;b<=B&&a+b<=n;b++)
			{
				c=n-a-b;
				if(c>C)continue;
				sum+=getSUM(a,b,c);
			}
			CNT+=N;
			SUM+=N*sum;
		}
		else
		{
			LL n=N>>1,sum=0LL;
			for(LL a=0LL,b,c;a<=A&&a<=n;a++)
			for(b=0LL;b<=B&&a+b<=n;b++)
			{
				c=n-a-b;
				if(c>C)continue;
				sum+=getSUM(a,b,c);
			}
			SUM+=(N>>1)*sum;
			n=(N+2LL)>>1,sum=0LL;
			for(LL a=0LL,b,c;a<=A&&a<=n;a++)
			for(b=0LL;b<=B&&a+b<=n;b++)
			{
				c=n-a-b;
				if(c>C)continue;
				sum+=getSUM(a,b,c);
			}
			SUM+=(N>>1)*sum;
			CNT+=N;
		}
		printf("%lld %lld\n",SUM,CNT);
		printf("%lld\n",SUM/CNT);
	}
	return 0;
}
