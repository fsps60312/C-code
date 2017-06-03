#include<cstdio>
typedef long long LL;
const LL MOD=2076030LL;
LL P,ANS=1LL,A=2LL;
int main()
{
	scanf("%lld",&P);
	while(P>0LL)
	{
		if((P&1LL)==1LL)ANS*=A,ANS%=MOD;
		P>>=1;
		A*=A,A%=MOD;
	}
	printf("%lld\n",ANS);
	return 0;
}
