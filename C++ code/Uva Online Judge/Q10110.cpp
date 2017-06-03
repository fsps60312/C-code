#include<cstdio>
typedef long long LL;
LL N;
bool NumOfFactor()
{
	for(LL i=2LL;i*i<=N;i++)
	{
		int cnt=0;
		while(N%i==0LL)N/=i,cnt++;
		if((cnt+1)%2==0)return false;
	}
	return N==1;
}
int main()
{
	while(scanf("%lld",&N)==1&&N!=0LL)puts(NumOfFactor()?"yes":"no");
	return 0;
}
