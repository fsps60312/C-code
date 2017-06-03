#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL Pow(LL a,int p)
{
	LL ans=1LL;
	while(p)
	{
		if(p&1)(ans*=a)%=MOD;
		(a*=a)%=MOD;
		p>>=1;
	}
	return ans;
}
int main()
{
	int ans[40]={2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,4423,9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,216091,756839,859433,1257787,1398269,2976221,3021377,6972593,13466917,20996011};
	for(int n;scanf("%d",&n)==1;)
	{
		printf("%lld\n",(Pow(2,ans[--n]-1)-1+MOD)%MOD);
	}
	return 0;
}
