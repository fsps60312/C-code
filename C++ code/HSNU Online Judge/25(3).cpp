#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,M;
void Solve()
{
	if(N==1L)printf("%lld.00\n",2L*(M-1L));
	else
	{
		printf("%lld.",N*M);
		if(N&M&1L)puts("41");
		else puts("00");
	}
}
int main()
{
	while(scanf("%lld%lld",&N,&M)==2)
	{
		if(N>M)swap(N,M);
		Solve();
	}
	return 0;
}
