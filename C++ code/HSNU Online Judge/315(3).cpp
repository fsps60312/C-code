#include<cstdio>
#include<cassert>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N;
map<LL,LL>CHANGE;
void Add(const LL &key)
{
	auto it=CHANGE.find(key);
	if(it==CHANGE.end())CHANGE[key]=1;
	else it->second++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	CHANGE.clear();
	static LL l,r;scanf(2,"%lld%lld",&l,&r);
	Add(l),Add(r);
	LL cost=0LL,locate=l,cnt=(l==r?1LL:0LL);
	puts("0");
	for(int i=1;i<N;i++)
	{
		scanf(2,"%lld%lld",&l,&r);
		Add(l),Add(r);
		if(l>locate)cnt--,cost+=(l-locate);
		if(r<=locate)cnt++,cost+=(locate-r);
		if(cnt<0LL)
		{
			const auto it=CHANGE.upper_bound(locate);
			assert(it!=CHANGE.end());
			cost+=cnt*((it->first)-locate);
			locate=it->first;
			cnt+=it->second;
			assert(cnt>=0LL);
		}
		else
		{
			auto it=CHANGE.find(locate);
			assert(it!=CHANGE.end());
			if(cnt-(it->second)>0LL)
			{
				cnt-=it->second;
				assert(it!=CHANGE.begin());
				it--;
				cost-=cnt*(locate-(it->first));
				locate=it->first;
				assert(cnt-(it->second)<=0LL);
			}
		}
		printf("%lld\n",cost);
	}
	return 0;
}
