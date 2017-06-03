#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
LL Abs(const LL &a){return a>=0LL?a:-a;}
LL Max(const LL &a,const LL &b){return a>b?a:b;}
LL MaxDif(const LL &a,const LL &b,const LL &c){return Max(Max(Abs(a-b),Abs(a-c)),Abs(b-c));}
int N;
LL S[24];
LL GetSum(const int s)
{
	LL ans=0LL;
	for(int i=0;i<N;i++)if(s&(1<<i))ans+=S[i];
	return ans;
}
LL GetSum(const int s,const int n,const vector<LL>&staff)
{
	LL ans=0LL;
	for(int i=0;i<n;i++)if(s&(1<<i))ans+=staff[i];
	return ans;
}
LL GetDis(const int s)
{
	vector<LL>staff;
	for(int i=0;i<N;i++)if(s&(1<<i))staff.push_back(S[i]);
	const int n=staff.size();
	const int half=n/2;
	set<LL>tmp;
	if(1)
	{
		LL sum=0LL;for(int i=0;i<half;i++)sum+=staff[i];
		for(int i=0;i<(1<<half);i++)tmp.insert(sum-2LL*GetSum(i,n,staff));
	}
	LL ans=INF,sum=0LL;for(int i=half;i<n;i++)sum+=staff[i];
	for(int i=0;i<(1<<(n-half));i++)
	{
		const LL dis=sum-2LL*GetSum(i<<half,n,staff);
		auto it=tmp.lower_bound(dis);
		if(it!=tmp.end())getmin(ans,Abs((*it)-dis));
		if(it!=tmp.begin())getmin(ans,Abs((*--it)-dis));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	LL sum=0LL;
	for(int i=0;i<N;i++)scanf(1,"%lld",&S[i]),sum+=S[i];
	LL ans=INF;
	const int all=(1<<N)-1;
	for(int s=0;s<(1<<N);s++)if(GetSum(s)<=sum/3LL)
	{
		const LL dis=GetDis(all^s);
		getmin(ans,MaxDif(GetSum(s),(GetSum(all^s)-dis)/2LL,(GetSum(all^s)+dis)/2LL));
	}
	printf("%lld\n",ans);
	return 0;
}
