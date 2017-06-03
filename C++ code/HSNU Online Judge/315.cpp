#include<cstdio>
#include<cassert>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N;
map<int,int>CHANGE;
int main()
{
	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	CHANGE.clear();
	LL nowcost=0LL;
	for(int i=0,l,r;i<N;i++)scanf(2,"%d%d",&l,&r),CHANGE[l]++,CHANGE[r]++,nowcost+=l;
	LL ans=nowcost;
	LL cnt=-N;
	LL pre=0LL;
	for(const auto &it:CHANGE)
	{
		nowcost+=cnt*(it.first-pre);
		cnt+=it.second;
		pre=it.first;
		if(nowcost<ans)ans=nowcost;
	}
	assert(cnt==N);
	printf("%lld\n",ans);
	return 0;
}
