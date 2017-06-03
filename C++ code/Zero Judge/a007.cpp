#include<cstdio>
#include<vector>
using namespace std;
bool IS_PRIME[65537];
vector<int>PRIMES;
bool IsPrime(const int x)
{
	if(x<=65536)return IS_PRIME[x];
	for(const int p:PRIMES)
	{
		if(p>x/p)break;
		if(x%p==0)return false;
	}
	return true;
}
int main()
{
	for(int i=2;i<=65536;i++)IS_PRIME[i]=true;
	for(int n=2;n<=65536;n++)
	{
		if(IS_PRIME[n])PRIMES.push_back(n);
		for(int i=0;i<(int)PRIMES.size()&&PRIMES[i]<=65536/n;i++)
		{
			IS_PRIME[n*PRIMES[i]]=false;
			if(n%PRIMES[i]==0)break;
		}
	}
	for(int x;scanf("%d",&x)==1;)puts(IsPrime(x)?"質數":"非質數");
	return 0;
}
