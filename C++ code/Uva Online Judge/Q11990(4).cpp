#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int N,M;
struct Node
{
	Node *l,*r;
	int v,sz,inuse;
	Node(int _v):l(NULL),r(NULL),sz(1),v(_v),inuse(1){}
}*V[200001];
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->l)+Sz(o->r)+o->inuse;}
int QueryU(Node* &o,int v)
{
	if(!o)return 0;
	if(v>o->v)return QueryU(o->r,v);
	else if(v==o->v)return o->inuse+Sz(o->r);
	else return QueryU(o->l,v)+o->inuse+Sz(o->r);
}
int QueryD(Node* &o,int v)
{
	if(!o)return 0;
	if(v<o->v)return QueryD(o->l,v);
	else if(v==o->v)return Sz(o->l)+o->inuse;
	else return Sz(o->l)+o->inuse+QueryD(o->r,v);
}
void Build(Node* &o,vector<int>&v,int l,int r)
{
	int mid=(l+r)/2;
	o=new Node(v[mid]);
	if(l<=mid-1)Build(o->l,v,l,mid-1);
	if(mid+1<=r)Build(o->r,v,mid+1,r);
	Maintain(o);
}
void Remove(Node* &o,int v)
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
	vector<int>vec[200001];
	void Clear()
	{
		for(int i=1;i<=N;i++)
		{
			V[i]=NULL;
			vec[i].clear();
		}
	}
	void Buil()
	{
		for(int i=1;i<=N;i++)
		{
			sort(vec[i].begin(),vec[i].end());
			Build(V[i],vec[i],0,vec[i].size()-1);
			assert(V[i]->sz==vec[i].size());
		}
	}
	int lowbit(int i){return i&(-i);}
	void Add(int i,int v)
	{
		while(i<=N)
		{
			vec[i].push_back(v);
			i+=lowbit(i);
		}
	}
	void Remov(int i,int v)
	{
		while(i<=N)
		{
			int sz=V[i]->sz;
			Remove(V[i],v);
			assert(V[i]->sz==sz-1);
			i+=lowbit(i);
		}
	}
	int QuerU(int i,int v)
	{
		int ans=0;
		while(i)
		{
			ans+=QueryU(V[i],v);
			i-=lowbit(i);
		}
		return ans;
	}
	int QuerD(int i,int v)
	{
		int ans=0;
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
	int v[200001];
	void Clear(){for(int i=1;i<=N;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i)
	{
		while(i<=N)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	int Query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BT;
int LOC[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		BIT.Clear();
		BT.Clear();
		int ans=0;
		for(int i=1;i<=N;i++)
		{
			static int v;
			scanf("%d",&v);
			LOC[v]=i;
			BIT.Add(i,v);
			BT.Add(v);
			ans+=BT.Query(N)-BT.Query(v);
		}
		BIT.Buil();
		for(int i=1;i<=M;i++)
		{
			printf("%d\n",ans);
			static int v;
			scanf("%d",&v);
			ans-=BIT.QuerU(LOC[v]-1,v+1);
			ans-=BIT.QuerD(N,v-1)-BIT.QuerD(LOC[v],v-1);
			BIT.Remov(LOC[v],v);
		}
	}
	return 0;
}
