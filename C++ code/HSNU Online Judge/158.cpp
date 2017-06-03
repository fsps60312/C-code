#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
LL N,S[250000],PW;
int K;
LL Solve(const LL &n)
{
//	printf("n=%lld\n",n);
	vector<LL>factor;
	for(LL gap=1LL;gap*gap<=n;gap++)if(n%gap==0LL)
	{
		if(gap*gap<n)factor.push_back(n/gap);
		bool found=false;
		for(int i=0;i<K;i++)if(S[i]%gap==0){found=true;break;}
		if(!found)return Solve(gap)*(n/gap);
	}
	for(int i=(int)factor.size()-1;i>=1;i--)
	{
		const LL &gap=factor[i];
		bool found=false;
		for(int i=0;i<K;i++)if(S[i]%gap==0){found=true;break;}
		if(!found)return Solve(gap)*(n/gap);
	}
	return 1LL;
}
LL Solve()
{
	LL gap=Gcd(N,PW);
	for(int i=0;i<K;i++)if(S[i]%gap==0LL)return 1LL;
	return Solve(gap)*(N/gap);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld%d",&N,&K),K--;
	for(int i=0;i<K;i++)scanf("%lld",&S[i]);
	scanf("%lld",&PW);
	printf("%lld\n",Solve());
	return 0;
}
