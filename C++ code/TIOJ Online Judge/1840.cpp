#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int SZ_LIMIT=223;
int VALUE_RANGE;
struct QueryType{int type,l,r,v;};
struct Node
{
	Node *lnode,*rnode;
	vector<int>SZ,DATA;
	Node():lnode(NULL),rnode(NULL){}
	void Insert(Node *l,Node *r){l->rnode=this,this->rnode=r;r->lnode=this,this->lnode=l;}
	void Extract(){Node *l=this->lnode,*r=this->rnode;l->rnode=r,r->lnode=l;}
	void Split()
	{
		Node *l=new Node(),*r=new Node();
		const int half=DATA.size()/2;
		for(int i=0;i<half;i++)(l->DATA).push_back(DATA[i]);
		for(int i=half;i<(int)DATA.size();i++)(r->DATA).push_back(DATA[i]);
		l->Build(),r->Build();
		l->Insert(this->lnode,r),r->Insert(l,this->rnode);
		delete this;
	}
	int size()const{return SZ[1];}
	void Build()
	{
		int *tmp=new int[VALUE_RANGE];
		for(int i=0;i<VALUE_RANGE;i++)tmp[i]=0;
		for(const int v:DATA)tmp[v]++;
		Build(1,0,VALUE_RANGE-1,tmp);
		delete[]tmp;
	}
	void Build(const int id,const int l,const int r,const int *v)
	{
		while(id>=(int)SZ.size())SZ.push_back(0);
		if(l==r){SZ[id]=(v?v[r]:0);}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,v),Build(id*2+1,mid+1,r,v);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	int Query(const int bl,const int br){return Query(1,0,VALUE_RANGE-1,bl,br);}
	int Query(const int id,const int l,const int r,const int bl,const int br)const
	{
		if(r<bl||br<l)return 0;
		if(bl<=l&&r<=br)return SZ[id];
		const int mid=(l+r)/2;
		return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
	}
	void Insert(const int v,const int loc)
	{
		DATA.push_back(-1);
		for(int i=loc;i+1<(int)DATA.size();i++)DATA[i+1]=DATA[i];
		DATA[loc]=v;
		if((int)DATA.size()<=SZ_LIMIT)Modify(v,1);
		else Split();
	}
	void Modify(const int loc,const int v){Modify(1,0,VALUE_RANGE-1,loc,v);}
	void Modify(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){SZ[id]+=v;return;}
		const int mid=(l+r)/2;
		if(v<=mid)Modify(id*2,l,mid,loc,v);
		else Modify(id*2+1,mid+1,r,loc,v);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
}*BEGIN,*END;
vector<QueryType>QUERY;
int N;
int Discretize(const vector<int>&s,const int val){return lower_bound(s.begin(),s.end(),val)-s.begin();}
void ReadInput()
{
	int querycount;
	vector<int>s,v;
	scanf("%d%d",&N,&querycount);
	for(int i=0,a;i<N;i++)scanf("%d",&a),s.push_back(a),v.push_back(a);
	QUERY.clear();
	for(QueryType q;querycount--;)
	{
		scanf("%d",&q.type);
		if(q.type==1)scanf("%d%d%d",&q.l,&q.r,&q.v);
		else if(q.type==2)scanf("%d%d",&q.l,&q.v),v.push_back(q.v);
		else if(q.type==3)scanf("%d%d",&q.l,&q.v),v.push_back(q.v);
		else assert(0);
		QUERY.push_back(q);
	}
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	VALUE_RANGE=v.size();
	BEGIN=new Node(),END=new Node();
	{Node *tmp=new Node();tmp->Insert(BEGIN,END);}
	for(const int a:s)END->lnode->Insert(Discretize(v,a),END->lnode->size());
	for(QueryType &q:QUERY)if(q.type>=2)q.v=Discretize(v,q.v);
}
void Modify(const int idx,const int v)
{
	Node *cur=BEGIN;
	for(int i=0;;i+=(cur->size()),cur=(cur->rnode))
	{
		assert(cur!=END);
		if(idx<i+(cur->size()))
		{
			cur->Modify(cur->DATA[idx-i],-1);
			cur->Modify(cur->DATA[idx-i]=v,1);
			return;
		}
	}
}
int GetValue(const int bl,const int br,const int rank)
{
	assert(0);return -1;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		ReadInput();
		for(const QueryType &q:QUERY)
		{
			switch(q.type)
			{
				case 1:printf("%d\n",GetValue(q.l-1,q.r-1,q.v));break;
				case 2:Modify(q.l,q.v);break;
				case 3:puts("7122");break;
				default:assert(0);break;
			}
		}
	}
	return 0;
}
