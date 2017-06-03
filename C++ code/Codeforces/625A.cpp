#include<cstdio>
#include<cassert>
using namespace std;
typedef unsigned long long LL;
LL N,A,B,C;
LL Solve()
{
	assert(A>0&&B>C);
	if(A<=B-C)return N/A;
	LL ans=0;
	if(N>=B)
	{
		ans=(N-C)/(B-C);
		N-=ans*(B-C);
		assert(C<=N&&N<B);
	}
	return ans+N/A;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%llu",&N)==1)
	{
		scanf("%llu%llu%llu",&A,&B,&C);
		printf("%llu\n",Solve());
//		break;
	}
	return 0;
}
