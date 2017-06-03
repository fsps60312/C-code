#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,M;
double Solve()
{
	if(N==1L)return 2.0*(M-1L);
	if(N&M&1L)return (double)N*M-1.0+sqrt(2.0);
	return (double)N*M;
}
int main()
{
	while(scanf("%lld%lld",&N,&M)==2)
	{
		if(N>M)swap(N,M);
		printf("%.2f\n",Solve());
	}
	return 0;
}
