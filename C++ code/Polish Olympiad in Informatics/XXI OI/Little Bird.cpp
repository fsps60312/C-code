#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	multiset<int>S[4000000];
	void Build(const int id,const int l,const int r)
	{
		S[id].clear();
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Insert(const int id,const int l,const int r,const int loc,const int val)
	{
		S[id].insert(val);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Insert(id*2,l,mid,loc,val);
			else Insert(id*2+1,mid+1,r,loc,val);
		}
	}
	void Remove(const int id,const int l,const int r,const int loc,const int val)
	{
		multiset<int>::iterator it=S[id].find(val);
		assert(it!=S[id].end());
		S[id].erase(it);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Remove(id*2,l,mid,loc,val);
			else Remove(id*2+1,mid+1,r,loc,val);
		}
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return S[id].empty()?INF:*S[id].begin();
		const int mid=(l+r)/2;
		return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
}SEG;
int N,M,H[1000000],K;
void Discretize()
{
	vector<int>v;
	for(int i=0;i<N;i++)v.push_back(H[i]);
	sort(v.begin(),v.end()),v.resize(M=(int)(unique(v.begin(),v.end())-v.begin()));
	for(int i=0;i<N;i++)H[i]=(int)(lower_bound(v.begin(),v.end(),H[i])-v.begin());
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		Discretize();
		int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			scanf("%d",&K);
			static int dp[1000000];
			dp[N-1]=0;
			SEG.Build(1,0,M-1);
			SEG.Insert(1,0,M-1,H[N-1],0);
			for(int i=N-2;i>=0;i--)
			{
				dp[i]=INF;
				const int ansl=SEG.Query(1,0,M-1,0,H[i]-1);
				if(ansl!=INF)getmin(dp[i],ansl);
				const int ansr=SEG.Query(1,0,M-1,H[i],M-1);
				if(ansr!=INF)getmin(dp[i],ansr+1);
				SEG.Insert(1,0,M-1,H[i],dp[i]);
				if(i+K<N)SEG.Remove(1,0,M-1,H[i+K],dp[i+K]);
			}
//			for(int i=0;i<N;i++)printf(" %d",dp[i]);puts("");
			printf("%d\n",dp[0]);
		}
	}
	return 0;
}
