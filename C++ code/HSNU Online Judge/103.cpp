#include<cstdio>
typedef long long LL;
int T;
LL N,M;
bool Solve()
{
	if(M%2LL==0LL)M--;
	LL mx=(1LL+M)*(M+1LL)/2LL/2LL;
	if(N>mx)return false;
	if(mx-N==2LL)return false;
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
