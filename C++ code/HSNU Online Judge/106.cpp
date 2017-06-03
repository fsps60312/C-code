#include<cstdio>
typedef long long LL;
LL T,N,M;
LL Solve()
{
	if(N>=M)
	{
		if(M%2==1)return (M+1)/2-1;
		else return M/2+1-1;
	}
	else if(N==M-1)
	{
		if(N%2==1)return (N+1)/2-1;
		else return N/2-1;
	}
	else if(N+N-1>=M)
	{
		LL first=M-N;
		LL cnt=N-first+1;
		LL ans=(3+first+1)*(first-1)/2;
		if(cnt%2==1)return ans+(cnt-1)/2;
		else return ans+cnt/2-1;
	}
	else
	{
		return (3+N+1)*(N-1)/2;
	}
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		printf("%lld\n",Solve());
	}
	return 0;
}
