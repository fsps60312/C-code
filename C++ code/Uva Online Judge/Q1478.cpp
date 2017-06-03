#include<cstdio>
#define LL long long
#define Big LL
LL N,K;
int main()
{
//N ups and N downs: C(2N,N)-C(2N,N+1)
//Sum(C(N,K)(C(N-K,(N-K)/2)-C(N-K,(N-K)/2+1))),(N-K)%2==0
//=Sum(N!/K!/(N-K)!*((N-K)!/((N-K)/2)!^2-(N-K)!/((N-K)/2+1)!/((N-K)/2-1)!))
//=Sum(N!/K!*(1/((N-K)/2)!^2-1/((N-K)/2+1)!/((N-K)/2-1)!))
//=Sum(N!/K!/((N-K)/2)!^2-N!/K!/((N-K)/2+1)!/((N-K)/2-1)!)
//K->K-2=>
//*K*(K-1)/(N-K+)
	while(scanf("%lld",&N)==1)
	{
		Big tmp=1LL;
		Big ans=1LL;//+=tmp
		for(K=N;K>=0;K-=2LL)
		{
			
		}
	}
	return 0;
}
