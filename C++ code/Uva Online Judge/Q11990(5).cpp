#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
LL N,M;
struct Node
{
	Node *l,*r;
	LL v,sz,inuse;
	Node(LL _v):l(NULL),r(NULL),sz(1),v(_v),inuse(1){}
}*V[200001];
LL Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->l)+Sz(o->r)+o->inuse;}
LL QueryU(Node* &o,LL v)
{
	if(!o)return 0;
	if(v>o->v)return QueryU(o->r,v);
	else if(v==o->v)return o->inuse+Sz(o->r);
	else return QueryU(o->l,v)+o->inuse+Sz(o->r);
}
LL QueryD(Node* &o,LL v)
{
	if(!o)return 0;
	if(v<o->v)return QueryD(o->l,v);
	else if(v==o->v)return Sz(o->l)+o->inuse;
	else return Sz(o->l)+o->inuse+QueryD(o->r,v);
}
void Build(Node* &o,vector<LL>&v,LL l,LL r)
{
	LL mid=(l+r)/2;
	o=new Node(v[mid]);
	if(l<=mid-1)Build(o->l,v,l,mid-1);
	if(mid+1<=r)Build(o->r,v,mid+1,r);
	Maintain(o);
}
void Remove(Node* &o,LL v)
{
	if(o->v==v)
	{
		assert(o->inuse);
		o->inuse=0;
	}
	else if(o->v>v)Remove(o->l,v);
	else Remove(o->r,v);
	Maintain(o);
}
struct Bit
{
	vector<LL>vec[200001];
	void Clear()
	{
		for(LL i=1;i<=N;i++)
		{
			V[i]=NULL;
			vec[i].clear();
		}
	}
	void Buil()
	{
		for(LL i=1;i<=N;i++)
		{
			sort(vec[i].begin(),vec[i].end());
			Build(V[i],vec[i],0,vec[i].size()-1);
			assert(V[i]->sz==vec[i].size());
		}
	}
	LL lowbit(LL i){return i&(-i);}
	void Add(LL i,LL v)
	{
		while(i<=N)
		{
			vec[i].push_back(v);
			i+=lowbit(i);
		}
	}
	void Remov(LL i,LL v)
	{
		while(i<=N)
		{
			LL sz=V[i]->sz;
			Remove(V[i],v);
			assert(V[i]->sz==sz-1);
			i+=lowbit(i);
		}
	}
	LL QuerU(LL i,LL v)
	{
		LL ans=0;
		while(i)
		{
			ans+=QueryU(V[i],v);
			i-=lowbit(i);
		}
		return ans;
	}
	LL QuerD(LL i,LL v)
	{
		LL ans=0;
		while(i)
		{
			ans+=QueryD(V[i],v);
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
struct Bt
{
	LL v[200001];
	void Clear(){for(LL i=1;i<=N;i++)v[i]=0;}
	LL lowbit(LL i){return i&(-i);}
	void Add(LL i)
	{
		while(i<=N)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	LL Query(LL i)
	{
		LL ans=0;
		while(i)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BT;
LL LOC[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld",&N,&M)==2)
	{
		BIT.Clear();
		BT.Clear();
		LL ans=0;
		for(LL i=1;i<=N;i++)
		{
			static LL v;
			scanf("%lld",&v);
			LOC[v]=i;
			BIT.Add(i,v);
			BT.Add(v);
			ans+=BT.Query(N)-BT.Query(v);
		}
		BIT.Buil();
		for(LL i=1;i<=M;i++)
		{
			printf("%lld\n",ans);
			static LL v;
			scanf("%lld",&v);
			ans-=BIT.QuerU(LOC[v]-1,v+1);
			ans-=BIT.QuerD(N,v-1)-BIT.QuerD(LOC[v],v-1);
			BIT.Remov(LOC[v],v);
		}
	}
	return 0;
}
