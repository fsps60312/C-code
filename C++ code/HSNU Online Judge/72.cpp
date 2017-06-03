#include<cstdio>
typedef long long LL;
LL A[4],D,N;
LL Solve()
{
	LL ans=D;
	ans*=(--N)>>2<<1;
	return ans+=A[N%=4];
}
int main()
{
	while(scanf("%lld%lld%lld%lld%lld",&A[0],&A[1],&A[2],&D,&N)==5)
	{
		A[3]=A[0]-A[1]+A[2]+D;
		/*
		F(n) + F(n+2) + D = F(n+1) + F(n+3)
		F(n+3)=F(n)-F(n+1)+F(n+2)+D
		=F(n)-F(n+1)+(F(n-1)-F(n)+F(n+1)+D)+D
		=(F(n-1)+D)+D
		=F(n-1)+2D
		*/
		printf("%lld\n",Solve());
	}
	return 0;
}
