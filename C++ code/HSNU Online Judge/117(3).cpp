#include<cstdio>
#include<cassert>
#include<set>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int N;
LL S[24],SUM[1<<24],DIS[1<<24];
//int CntBit(int x)
//{
//	x=((x&0xaaaaaaaa)>>1)+(x&0x55555555);
//	x=((x&0xcccccccc)>>2)+(x&0x33333333);
//	x=((x&0xf0f0f0f0)>>4)+(x&0x0f0f0f0f);
//	x=((x&0xff00ff00)>>8)+(x&0x00ff00ff);
//	x=((x&0xffff0000)>>16)+(x&0x0000ffff);
//	return x;
//}
void Dfs(const int dep,const int u,const LL &sum,set<LL>&comb)
{
	if(dep==N){SUM[u]=sum,DIS[u]=abs(sum-2LL*(*comb.lower_bound(sum/2)));return;}
	Dfs(dep+1,u,sum,comb);
	vector<LL>newadd;
	for(const auto &v:comb)if(comb.find(v+S[dep])==comb.end())newadd.push_back(v+S[dep]);
	for(const auto &v:newadd)comb.insert(v);
	Dfs(dep+1,u|(1<<dep),sum+S[dep],comb);
	for(const auto &v:newadd)comb.erase(v);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<(1<<N);i++)SUM[i]=-1LL;
	for(int i=0;i<N;i++)scanf(1,"%lld",&S[i]);
	set<LL>comb;comb.insert(0LL);
	Dfs(0,0,0LL,comb);
	assert((int)comb.size()==1);
	for(int i=0;i<(1<<N);i++)assert(SUM[i]!=-1LL);
	LL ans=INF;
	const int all=(1<<N)-1;
	for(int s=0;s<(1<<N);s++)
	{
		const LL s1=SUM[s],s2=SUM[all^s],dis=DIS[all^s];
		getmin(ans,max(max(abs(s1-(s2-dis)/2),abs(s1-(s2+dis)/2)),dis));
	}
	printf("%lld\n",ans);
	return 0;
}
