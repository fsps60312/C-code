#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
struct SegTree
{
	int N;
	LL SUM[300000*4];
	void Build(const int id,const int l,const int r)
	{
		SUM[id]=0LL;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N;Build(1,0,N-1);}
	void Modify(const int id,const int l,const int r,const int loc,const LL &val)
	{
		SUM[id]+=val;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,val);
			else Modify(id*2+1,mid+1,r,loc,val);
		}
	}
	void Modify(const int loc,const LL &val){Modify(1,0,N-1,loc,val);}
	LL Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0LL;
		if(bl<=l&&r<=br)return SUM[id];
		const int mid=(l+r)/2;
		return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
	}
	LL Query(const int bl,const int br){return Query(1,0,N-1,bl,br);}
}SEG_TREE;
struct QueryType
{
	int u;
	LL x;
};
vector<QueryType>QUERY;
pair<int,int>SEG[300000];//not related to SEG_TREE
vector<int>ET[300000];
void BuildSEG(const int u,int &clock)
{
	SEG[u].first=clock;
	for(const int nxt:ET[u])BuildSEG(nxt,clock);
	SEG[u].second=clock++;
}
int ANS[300001];
LL K;
void Solve(const int l,const int r,const vector<int>&staffs)
{
	if(staffs.empty())return;
	if(l==r){ANS[r]+=staffs.size();return;}
	const int mid=(l+r)/2;
	for(int i=l;i<=mid;i++)
	{
		const QueryType &q=QUERY[i];
		SEG_TREE.Modify(SEG[q.u].second,q.x);
	}
	vector<int>left_staffs,right_staffs;
	for(const int s:staffs)
	{
		if(SEG_TREE.Query(SEG[s].first,SEG[s].second)<K)right_staffs.push_back(s);
		else left_staffs.push_back(s);
	}
	Solve(mid+1,r,right_staffs);
	for(int i=mid;i>=l;i--)
	{
		const QueryType &q=QUERY[i];
		SEG_TREE.Modify(SEG[q.u].second,-q.x);
	}
	Solve(l,mid,left_staffs);
	vector<int>().swap(left_staffs);
	vector<int>().swap(right_staffs);
}
int N,Q;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
//	freopen("s2.in","r",stdin);
	for(;scanf("%d%d%lld",&N,&Q,&K)==3;)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,parent;i<N;i++)scanf("%d",&parent),ET[--parent].push_back(i);
		if(true){int clock=0;BuildSEG(0,clock);assert(clock==N);}
		QUERY.clear();
		for(int i=0;i<Q;i++)
		{
			static QueryType q;
			scanf("%d%lld",&q.u,&q.x),q.u--;
			QUERY.push_back(q);
		}
		vector<int>staffs;
		for(int i=0;i<N;i++)staffs.push_back(i);
		for(int i=0;i<Q;i++)ANS[i]=0;
		SEG_TREE.Build(N);
		Solve(0,Q,staffs);
		for(int i=1;i<Q;i++)ANS[i]+=ANS[i-1];
		for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
