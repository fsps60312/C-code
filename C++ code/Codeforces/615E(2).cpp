#include<cstdio>
#include<cassert>
#include<utility>
#include<cmath>
using namespace std;
typedef long long LL;
LL N;
pair<LL,LL>Solve()
{
	if(N==0LL)return make_pair(0LL,0LL);
//	6+12+18...
//	6(1+2+3+...+n)
//	6(n(n+1)/2)
//	3n(n+1)=x
//3n^2+3n-x=0
//(-3+sqrt(9+12x))/6
	const LL cyc=(LL)((-3.0+sqrt(9.0+12.0*N))/6.0-1e-8)+1LL;
//	printf("cyc=%lld,%.9f\n",cyc,(-3.0+sqrt(9.0+12.0*N))/6.0);
	pair<LL,LL>ans=make_pair(2LL*cyc,0LL);
	LL move=3LL*cyc*(cyc+1LL),dis=move-N;
	if(dis<=cyc)
	{
		ans.first-=dis,ans.second-=dis*2LL;
		return ans;
	}
	ans.first-=cyc,ans.second-=2LL*cyc,dis-=cyc;
	if(dis<=cyc)
	{
		ans.first-=2LL*dis;
		return ans;
	}
	ans.first-=2LL*cyc,dis-=cyc;
	if(dis<=cyc)
	{
		ans.first-=dis,ans.second+=dis*2LL;
		return ans;
	}
	ans.first-=cyc,ans.second+=2LL*cyc,dis-=cyc;
	if(dis<=cyc)
	{
		ans.first+=dis,ans.second+=dis*2LL;
		return ans;
	}
	ans.first+=cyc,ans.second+=2LL*cyc,dis-=cyc;
	if(dis<=cyc)
	{
		ans.first+=2LL*dis;
		return ans;
	}
	ans.first+=2LL*cyc,dis-=cyc;
	assert(dis<cyc);
	ans.first+=dis,ans.second-=2LL*dis;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		const pair<LL,LL>&ans=Solve();
		printf("%lld %lld\n",ans.first,ans.second);
	}
	return 0;
}
