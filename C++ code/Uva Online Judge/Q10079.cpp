#include<cstdio>
long long N;
int main()
{
	while(scanf("%lld",&N)==1&&N>=0LL)
	{
		printf("%lld\n",1LL+N*(1LL+N)/2LL);
	}
	return 0;
}
