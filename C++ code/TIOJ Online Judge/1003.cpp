#include<cstdio>
typedef long long LL;
LL F(const int n)
{
	if(n==0)return 1LL;
	return n+F(n-1);
}
int main()
{
	for(int n;scanf("%d",&n)==1;)
	{
		printf("%lld\n",F(n));
	}
	return 0;
}
