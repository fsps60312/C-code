#include<cstdio>
typedef long long LL;
const LL MOD=910193;
LL ANS[10001];
int main()
{
	//C(L*2,L)-C(L*2,L-1)
	//=(2L)!/L!/L!-(2L)!/(L-1)!/(L+1)!
	//=(2L)!/(L+1)!/L!
	//=C(2L-1,L-1)*2L/L/(L+1)
	ANS[0]=1LL;
	for(int i=1;i<=10000;i++)
	{
		LL &a=ANS[i]=0LL;
		for(int j=0;j<i;j++)a+=ANS[j]*ANS[i-1-j],a%=MOD;
	}
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%lld\n",ANS[n]);
	}
	return 0;
}
