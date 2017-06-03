#include<cstdio>
#include<cstdlib>
const long long large=10000000000;
long long n;
unsigned long long ans[2];
int main()
{
	int T=1;
	while(scanf("%lld",&n)==1&&n>=0)
	{
		ans[0]=ans[1]=0;
		unsigned long long now=2,n1,n2=3;
		do
		{
			now<<=1;
			ans[0]+=n/now*(now>>2);
			ans[1]+=ans[0]/large;
			ans[0]%=large;
			n1=n%now;//*100
			if(n1>=(now>>1)+(now>>2))
			{
				ans[0]+=n1-((now>>1)+(now>>2))+1;
				ans[1]+=ans[0]/large;
				ans[0]%=large;
			}
			n2>>=1;
			if(now>n)
			{
				now>>=1;
				break;
			}
		}while(now!=(unsigned long long)1<<63);
		ans[1]+=ans[0]/large;
		ans[0]%=large;
		printf("Case %d: ",T++);
		if(ans[1])
		{
			printf("%lld%010lld\n",ans[1],ans[0]);
		}
		else
		{
			printf("%lld\n",ans[0]);
		}
	}
}
