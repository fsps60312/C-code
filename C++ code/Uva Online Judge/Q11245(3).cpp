#include<cstdio>
#include<cassert>
//#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
LL N;
int P;
LL Solve()
{
	vector<pair<LL,pair<LL,LL> > >s;
	pair<LL,pair<LL,LL> >p;
	s.push_back(p=make_pair(1LL,make_pair(1LL,1LL)));
	for(LL add=1LL;;)
	{
		s.push_back(p);
		p.first*=P-1;
		p.second.first+=add;
		if(p.second.second>(INF-add)/(P-1))break;
		(p.second.second*=P-1)+=add;
		add*=P;
//		printf("%lld %lld\n",p.first,p.second);
	}
	LL ans=1LL;
	for(int i=(int)s.size()-1;i>=0;i--)
	{
		p=s[i];
		const LL cnt=N/p.first;
		N-=cnt*p.first;
		ans+=cnt*p.second.second;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%d",&N,&P);
		N--;
		printf("%lld\n",Solve());
	}
	return 0;
}
