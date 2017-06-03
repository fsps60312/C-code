#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
LL SPARSE[63][1<<16];
void BuildSparse(const vector<pair<LL,LL> >&s,const int n)
{
	for(int i=0;i<n;i++)SPARSE[0][i]=s[i].second;
	for(int d=1;(1<<d)<n;d++)
	{
		for(int i=0;i+(1<<d)<=n;i++)SPARSE[d][i]=max(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
	}
}
LL QuerySparse(const int l,const int r)
{
	int d=0;
	while((1<<(d+1))<=r-l+1)d++;
	return max(SPARSE[d][l],SPARSE[d][r-(1<<d)+1]);
}
int N,HALF;
LL L,R,W[32],V[32];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lld%lld",&N,&L,&R)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&W[i],&V[i]);
		HALF=N/2;
		vector<pair<LL,LL> >left;
		for(int s=0;s<(1<<HALF);s++)
		{
			pair<LL,LL>p=make_pair(0LL,0LL);
			for(int i=0;i<HALF;i++)if(s&(1<<i))p.first+=W[i],p.second+=V[i];
			left.push_back(p);
		}
		sort(left.begin(),left.end());
		BuildSparse(left,1<<HALF);
		LL ans=0;
		for(int s=0;s<(1<<(N-HALF));s++)
		{
			pair<LL,LL>p=make_pair(0LL,0LL);
			for(int i=HALF;i<N;i++)if(s&(1<<(i-HALF)))p.first+=W[i],p.second+=V[i];
			const auto &itl=lower_bound(left.begin(),left.end(),make_pair(L-p.first,-INF)),
					   &itr=upper_bound(left.begin(),left.end(),make_pair(R-p.first,INF));
			if(itl!=itr)ans=max(ans,QuerySparse((int)(itl-left.begin()),(int)(itr-left.begin())-1)+p.second);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
