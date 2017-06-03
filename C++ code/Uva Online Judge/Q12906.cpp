#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long LL;
const LL MOD=1000000007LL;
//LL LEVEL[100001];
int N;
vector<pair<int,LL> >S;
LL Solve1()
{
	LL ans=0LL,sum=0LL;
	for(const auto &p:S)
	{
		sum+=p.second;//)%=MOD;
		ans+=sum*p.second;//)%=MOD;
	}
	return ans;
}
int main()
{
//	LEVEL[0]=1LL;
//	for(int i=1;i<=100000;i++)LEVEL[i]=(LEVEL[i-1]*i)%MOD;
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		S.clear();
		for(int i=0,v,f;i<N;i++)scanf("%d%d",&v,&f),S.push_back(make_pair(v,(LL)f));
		sort(S.begin(),S.end());
		const LL ans1=Solve1();
		LL ans2=1LL;
//		for(const auto &p:S)(ans2*=LEVEL[p.second])%=MOD;
		S.pop_back();
		for(const auto &p:S)(ans2*=p.second+1LL)%=MOD;
		static int kase=1;
		printf("Case %d: %llu %llu\n",kase++,ans1,ans2);
	}
	return 0;
}
