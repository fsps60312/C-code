#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Node
{
	Node *ch[2];
	const int val;
	int sz;
	Node(const int _val):ch{NULL,NULL},val(_val),sz(1){}
};
int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void Insert(Node* &o,const int val)
{
	if(!o){o=new Node(val);return;}
	if(val<=(o->val))Insert(o->ch[0],val);
	else Insert(o->ch[1],val);
	Maintain(o),Rotate(o);
}
void Erase(Node* &o)
{
	if(!o->ch[0]||!o->ch[1])
	{
		Node *u=o;
		o=(o->ch[0]?o->ch[0]:o->ch[1]);
		delete u;return;
	}
	const int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
	Rotate(o,cu);
	Erase(o->ch[cu^1]);
	Maintain(o);
}
void Erase(Node* &o,const int val)
{
	assert(o);
	if((o->val)==val){Erase(o);return;}
	if(val<(o->val))Erase(o->ch[0],val);
	else Erase(o->ch[1],val);
	Maintain(o);
}
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;o=NULL;
}
Node *ST[200000];
void Build(const int id,const int l,const int r)
{
	Delete(ST[id]);
	if(l<r)
	{
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
}
void Modify(const int id,const int l,const int r,const int loc,const int val,bool is_plus)
{
	if(is_plus)Insert(ST[id],val);
	else Erase(ST[id],val);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,val,is_plus);
		else Modify(id*2+1,mid+1,r,loc,val,is_plus);
	}
}
struct QueryType{int l,r,v;};
vector<QueryType>QUERY;
int N,M,S[50000];
vector<int>RANGE;
int GetRank(Node *o,const int val)
{
	if(!o)return 0;
	if((o->val)<=val)return Sz(o->ch[0])+1+GetRank(o->ch[1],val);
	else return GetRank(o->ch[0],val);
}
int GetRank(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return 0;
	if(bl<=l&&r<=br)return GetRank(ST[id],val);
	const int mid=(l+r)/2;
	return GetRank(id*2,l,mid,bl,br,val)+GetRank(id*2+1,mid+1,r,bl,br,val);
}
int Solve(const int bl,const int br,const int rank)
{
	int l=0,r=M-1;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(GetRank(1,0,N-1,bl,br,mid)<rank)l=mid+1;
		else r=mid;
	}
	return r;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int i=0;i<200000;i++)ST[i]=NULL;
	for(int querycount;scanf("%d%d",&N,&querycount)==2;)
	{
		RANGE.clear();
		for(int i=0;i<N;i++)scanf("%d",&S[i]),RANGE.push_back(S[i]);
		QUERY.clear();
		for(int i=0;i<querycount;i++)
		{
			static QueryType q;
			static char type[2];
			scanf("%s",type);
			if(type[0]=='Q')scanf("%d%d%d",&q.l,&q.r,&q.v),q.l--,q.r--;
			else if(type[0]=='C')q.l=-1,scanf("%d%d",&q.r,&q.v),q.r--,RANGE.push_back(q.v);
			else assert(0);
			QUERY.push_back(q);
		}
		if(true)
		{
			vector<int>&v=RANGE;
			sort(v.begin(),v.end()),v.resize(M=unique(v.begin(),v.end())-v.begin());
			for(int i=0;i<N;i++)S[i]=lower_bound(v.begin(),v.end(),S[i])-v.begin();
			for(QueryType &q:QUERY)if(q.l==-1)q.v=lower_bound(v.begin(),v.end(),q.v)-v.begin();
		}
		Build(1,0,N-1);
		for(int i=0;i<N;i++)Modify(1,0,N-1,i,S[i],true);
		for(const QueryType &q:QUERY)
		{
			if(q.l==-1)
			{
				Modify(1,0,N-1,q.r,S[q.r],false);
				Modify(1,0,N-1,q.r,S[q.r]=q.v,true);
			}
			else printf("%d\n",RANGE[Solve(q.l,q.r,q.v)]);
		}
	}
	return 0;
}
