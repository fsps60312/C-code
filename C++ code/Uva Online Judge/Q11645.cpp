#include<cstdio>
#include<cstdlib>
unsigned long long n;
int main()
{
	//freopen("in.txt","r",stdin);
	int T=1;
	while(scanf("%llu",&n)==1&&n>=0)
	{
		unsigned long long now=2,ans=0,n1,n2=3;
		do
		{
			now<<=1;
			ans+=n/now*(now>>2);
			n1=n%now;//*100
			if(n1>=(now>>1)+(now>>2))
			{
				ans+=n1-((now>>1)+(now>>2))+1;
			}
			n2>>=1;
			if(now>n)
			{
				now>>=1;
				break;
			}
		}while(now!=(unsigned long long)1<<63);
		printf("Case %d: %llu\n",T++,ans);
	}
	return 0;
}
