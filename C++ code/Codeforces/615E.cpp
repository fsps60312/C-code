#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
typedef long long LL;
LL N;
pair<LL,LL>Solve()
{
	if(N==0LL)return make_pair(0LL,0LL);
	const LL t=(N+5LL)/6LL;
	switch(N%6LL)
	{
		case 0LL:return make_pair(1LL+2LL*t,2LL+0LL*t);
		case 1LL:return make_pair(0LL+1LL*t,0LL+2LL*t);
		case 2LL:return make_pair(0LL-1LL*t,0LL+2LL*t);
		case 3LL:return make_pair(0LL-2LL*t,0LL+0LL*t);
		case 4LL:return make_pair(0LL-1LL*t,0LL-2LL*t);
		case 5LL:return make_pair(0LL+1LL*t,0LL-2LL*t);
		default:assert(0);return make_pair(-1LL,-1LL);
	}
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
