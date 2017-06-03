#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct SegTree
{
	set<int>remain[400000];
	void Build(const int id,const int l,const int r)
	{
		remain[id].clear();
		for(int i=l;i<=r;i++)remain[id].insert(i);
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Cover(const int id,const int l,const int r,const int bl,const int br,vector<int>&removed)
	{
		removed.clear();
		if(remain[id].empty())return;
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			for(const auto v:remain[id])removed.push_back(v);
			remain[id].clear();
			return;
		}
		const int mid=(l+r)/2;
		vector<int>tmp;
		Cover(id*2,l,mid,bl,br,tmp);
		for(const auto v:tmp)removed.push_back(v);
		tmp.clear();
		Cover(id*2+1,mid+1,r,bl,br,tmp);
		for(const auto v:tmp)removed.push_back(v);
		tmp.clear();
		for(const auto v:removed)
		{
			auto it=remain[id].find(v);
			assert(it!=remain[id].end());
			remain[id].erase(it);
		}
	}
}SEGTREE;
struct Pair
{
	int l,r;
	Pair(){}
	Pair(const int _l,const int _r):l(_l),r(_r){}
	bool operator<(const Pair &p)const{return l!=p.l?l<p.l:r<p.r;}
};
vector<Pair>FORBID[100000];
vector<Pair>AVAIL[100000];
int N,K,S,T,DIST[100000];
int Solve()
{
	for(int i=0;i<N;i++)DIST[i]=-1;
	queue<int>q;
	SEGTREE.Build(1,0,N-1);
	vector<int>removed;
	SEGTREE.Cover(1,0,N-1,S,S,removed);
	assert(removed.size()==1);
	for(const auto v:removed)assert(DIST[v]==-1),DIST[v]=0,q.push(v);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
//		printf("%d: %d\n",u,DIST[u]);
		if(u==T)return DIST[u];
		for(const Pair &p:AVAIL[u])
		{
			SEGTREE.Cover(1,0,N-1,p.l,p.r,removed);
			for(const auto v:removed)assert(DIST[v]==-1),DIST[v]=DIST[u]+1,q.push(v);
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)FORBID[i].clear(),AVAIL[i].clear();
		for(int i=0,u,v1,v2;i<K;i++)
		{
			assert(scanf("%d%d-%d",&u,&v1,&v2)==3);
			FORBID[u].push_back(Pair(v1,v2));
		}
		for(int i=0;i<N;i++)
		{
			sort(FORBID[i].begin(),FORBID[i].end());
			AVAIL[i].clear();
			int now=0;
			for(int j=0;j<FORBID[i].size();j++)
			{
				const Pair &f=FORBID[i][j];
				if(now<f.l)AVAIL[i].push_back(Pair(now,f.l-1));
				getmax(now,f.r+1);
			}
			if(now<N)AVAIL[i].push_back(Pair(now,N-1));
		}
		scanf("%d%d",&S,&T);
		int ans=Solve();
		static int kase=1;
		printf("Case #%d: ",kase++);
		if(ans==-1)puts("Impossible");
		else printf("%d\n",ans);
	}
	return 0;
}
