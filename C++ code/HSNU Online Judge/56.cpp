#include<cstdio>
int N;
int main()
{
	scanf("%d",&N);
	unsigned long long sum=0LL,ans=0LL;
	for(int i=0;i<N;i++)
	{
		static unsigned long long v;
		scanf("%llu",&v);
		ans+=v*sum;
		sum+=v;
	}
	printf("%llu\n",ans);
}
