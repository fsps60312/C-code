#include<cstdio>
#include<queue>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Pair
{
	LL now,p;
	Pair(){}
	Pair(const LL _now,const LL _p):now(_now),p(_p){}
	bool operator<(const Pair &p)const{return now>p.now;}
};
LL A,B;
map<LL,LL>DP;
void Initialize()
{
	priority_queue<Pair>pq;
	if(true)
	{
		bool *isp=new bool[100];
		for(int i=0;i<100;i++)isp[i]=true;
		for(int i=2;i<100;i++)if(isp[i])
		{
			pq.push(Pair(i,i));
			for(int j=2;i*j<100;j++)isp[i*j]=false;
		}
	}
	DP.clear();
	DP[1LL]=1;
	LL lcm=1LL,now=1LL;
	for(;;)
	{
		now=pq.top().now;
		while(pq.top().now<=now)
		{
			const Pair p=pq.top();pq.pop();
			if(lcm>INF/p.p)goto finished;
			lcm*=p.p;
			if(p.now<=INF/p.p)pq.push(Pair(p.now*p.p,p.p));
		}
		while(lcm%(now+1LL)==0LL)now++;
		DP[lcm]=now;
	}
	finished:;
//	for(auto it:DP)printf("(%lld,%lld)\n",it.first,it.second);
}
LL F(const LL x)
{
	if(x==2LL)return 1LL;
	auto it=DP.upper_bound(x);it--;
	while(x%(it->first)!=0LL)it--;
	return (it->second)+1LL;
}
LL Lolipop(const LL x){return x==1?0LL:Lolipop(F(x))+1;}
LL Cnt(const LL interval){return B/interval-(A-1)/interval;}
int main()
{
	Initialize();
//	for(int i=1;i<=20;i++)printf("%d=%lld\n",i,Lolipop(i));
	while(scanf("%lld%lld",&A,&B)==2)
	{
		LL used=0LL;
		LL ans=0LL;
		for(auto it=DP.rbegin();it!=DP.rend();it++)
		{
			const LL cnt=Cnt(it->first);
			ans+=(cnt-used)*(Lolipop(it->second+1LL)+1LL);
			used+=cnt-used;
		}
		assert(used==B-A+1LL);
		printf("%lld\n",ans);
	}
	return 0;
}
