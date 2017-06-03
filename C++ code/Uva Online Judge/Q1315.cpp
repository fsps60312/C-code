#include<cstdio>
int T,N,n;
int solve()
{
	n=N/2;
	if(N&1)return n*(n-1)/2+n*(n+1)/2;
	else return n*(n-1);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		printf("%d\n",solve());
	}
	return 0;
}
