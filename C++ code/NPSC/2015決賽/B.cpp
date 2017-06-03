#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=2147483647;
//void assert(bool valid){if(valid)return;for(;;);putchar('E');}
struct SegTree
{
	vector<LL>mx,mn,tag;
	map<LL,LL>mloc;
	LL n,light;
	void Clear(vector<LL>&nodes)
	{
		n=nodes.size();
		assert(n>=1);
		light=nodes[0];
		mloc.clear();
		for(LL i=0;i<n;i++)mloc[nodes[i]]=i;
		Build(1,0,n-1);
	}
	void Build(const LL id,const LL l,const LL r)
	{
		while((int)mx.size()<=id)mx.push_back(0),mn.push_back(0),tag.push_back(0);
		mx[id]=mn[id]=tag[id]=0;
		if(l==r)return;
		const LL mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r); 
	}
	void Add(const LL node,const LL v)
	{
		auto it=mloc.find(node);
		assert(it!=mloc.end());
		const LL loc=it->second;
		Add(1,0,n-1,loc,v);
	}
	void PutDown(const LL id)
	{
		if(tag[id])
		{
			mx[id*2]+=tag[id],mx[id*2+1]+=tag[id];
			mn[id*2]+=tag[id],mn[id*2+1]+=tag[id];
			tag[id*2]+=tag[id],tag[id*2+1]+=tag[id];
			tag[id]=0;
		}
	}
	void Pull(const LL id)
	{
		mx[id]=max(mx[id*2],mx[id*2+1]);
		mn[id]=min(mn[id*2],mn[id*2+1]);
	}
	void Add(const LL id,const LL l,const LL r,const LL loc,const LL v)
	{
		if(l>loc)return;
		if(r<=loc){mx[id]+=v,mn[id]+=v,tag[id]+=v;return;}
		const LL mid=(l+r)/2;
		PutDown(id);
		Add(id*2,l,mid,loc,v),Add(id*2+1,mid+1,r,loc,v);
		Pull(id);
	}
	LL Query(const LL bound){return Query(1,0,n-1,bound);}
	LL Query(const LL id,const LL l,const LL r,const LL bound)
	{
		if(mx[id]<bound)return 0;
		if(mn[id]>=bound)return r-l+1;
		if(l==r)return 1;
		const LL mid=(l+r)/2;
		PutDown(id);
		return Query(id*2,l,mid,bound)+Query(id*2+1,mid+1,r,bound);
	}
};
vector<SegTree>SEGTREE;
vector<LL>ET[300000];
LL FA[300000],SZ[300000];
struct RCmpLL{bool operator()(const LL a,const LL b){return a>b;}};
void BuildSEGTREE(const LL u,vector<LL>&rec)
{
	rec.push_back(u);
	if(ET[u].empty())
	{
//		for(const auto v:rec)printf(" %lld",v);puts("");
		SegTree seg;
		seg.Clear(rec);
		SEGTREE.push_back(seg);
		rec.clear();
		return;
	}
	multimap<LL,LL,RCmpLL>sortch;
	for(const auto nxt:ET[u])sortch.insert(make_pair(SZ[nxt],nxt));
	for(const auto &it:sortch)BuildSEGTREE(it.second,rec);
}
LL N,Q,K;
LL BuildSZ(const LL u)
{
	LL &ans=SZ[u]=1;
	for(const auto nxt:ET[u])ans+=BuildSZ(nxt);
	return ans;
}
LL TREEIDX[300000];
LL ANS;
void AddSalary(LL u,const LL money)
{
	for(;;)
	{
		LL ti=TREEIDX[u];
		const LL minus=SEGTREE[ti].Query(K);
		ANS-=minus;
//		printf("minus %lld\n",minus);
		SEGTREE[ti].Add(u,money);
		const LL plus=SEGTREE[ti].Query(K);
		ANS+=plus;
//		printf("plus  %lld\n",plus);
		if(SEGTREE[ti].light==0)break;
		u=FA[SEGTREE[ti].light];
	}
}
int main()
{
//	freopen("B.txt","r",stdin);
	while(scanf("%lld%lld%lld",&N,&Q,&K)==3)
	{
		for(LL i=0;i<N;i++)ET[i].clear();
		for(LL i=1;i<N;i++)scanf("%lld",&FA[i]),ET[--FA[i]].push_back(i);
		SEGTREE.clear();
		BuildSZ(0);
		vector<LL>rec;
		BuildSEGTREE(0,rec);
		assert(rec.empty());
		for(LL i=0;i<N;i++)TREEIDX[i]=-1;
		for(LL i=0;i<(int)SEGTREE.size();i++)for(const auto &it:SEGTREE[i].mloc)assert(TREEIDX[it.first]==-1),TREEIDX[it.first]=i;
		for(LL i=0;i<N;i++)assert(TREEIDX[i]!=-1);
		ANS=0;
		while(Q--)
		{
			static LL a,x;scanf("%lld%lld",&a,&x);
			a--;
			AddSalary(a,x);
			printf("%lld\n",ANS);
		}
		SEGTREE.clear();
		break;
	}
	return 0;
}
