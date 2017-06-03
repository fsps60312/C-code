#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int N,M,K,S,A[200000],B[200000];
vector<pair<int,int> >ANS,I,J;
bool Solve(const int days)
{
	int dd=0,pd=0;
	for(int i=0;i<days;i++)
	{
		if(A[i]<A[dd])dd=i;
		if(B[i]<B[pd])pd=i;
	}
	int budget=S;
	ANS.clear();
	for(int i=0,j=0;(int)ANS.size()<K;)
	{
		if(j==(int)J.size()||(i<(int)I.size()&&I[i].first*A[dd]<J[j].first*B[pd]))
		{
			ANS.push_back(make_pair(I[i].second,dd+1));
			if((budget-=I[i++].first*A[dd])<0)return false;
		}
		else
		{
			ANS.push_back(make_pair(J[j].second,pd+1));
			if((budget-=J[j++].first*B[pd])<0)return false;
		}
	}
	return true;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld%lld",&N,&M,&K,&S)==4)
	{
		for(int i=0;i<N;i++)scanf("%lld",&A[i]);
		for(int i=0;i<N;i++)scanf("%lld",&B[i]);
		I.clear(),J.clear();
		for(int i=1,t,c;i<=M;i++)
		{
			scanf("%lld%lld",&t,&c);
			(t==1?I:J).push_back(make_pair(c,i));
		}
		sort(I.begin(),I.end()),sort(J.begin(),J.end());
		int l=1,r=N+1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		if(r==N+1)puts("-1");
		else
		{
			Solve(r);
			printf("%lld\n",r);
			for(const auto &p:ANS)printf("%lld %lld\n",p.first,p.second);
		}
	}
	return 0;
}
