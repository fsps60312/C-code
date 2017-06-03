#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
LL N;
map<LL,bool>DP;
bool Win(const LL &n)
{
	auto it=DP.find(n);
	if(it!=DP.end())return it->second;
	bool &dp=DP[n];
	if(n*9LL>=N)return dp=true;
	for(LL i=2LL;i<=9LL;i++)if(!Win(n*i))return dp=true;
	return dp=false;
}
int main()
{
	while(scanf("%lld",&N)==1)DP.clear(),puts(Win(1LL)?"Stan wins.":"Ollie wins.");
	return 0;
}
