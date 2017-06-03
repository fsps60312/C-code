#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Node
{
	Node *ch[2];
	int sz;
	Node(const int v):ch{NULL,NULL},sz(-v){}
};
int Sz(Node* &o){return o?(o->sz<=0?1:o->sz):0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+Sz(o->ch[1]);}
int N,A[100001];
void Modify(Node* &o,const int dep,const int v)
{
	if(!o){o=new Node(v);return;}
	if(o->sz<=0)
	{
		const int d=((-o->sz)>>dep)&1;
		o->ch[d]=new Node(-(o->sz));
	}
	const int d=(v>>dep)&1;
	Modify(o->ch[d],dep-1,v);
	Maintain(o);
}
void Remove(Node* &o,const int dep,const int v)
{
	assert(o);
	if(o->sz<=0)
	{
		assert(o->sz==-v);
		delete o;o=NULL;
		return;
	}
	const int d=(v>>dep)&1;
//	const int pre_sz=Sz(o),a=Sz(o->ch[0]),b=Sz(o->ch[1]);
	Remove(o->ch[d],dep-1,v);
	Maintain(o);
	if(o->sz==0){delete o;o=NULL;}
}
int Query(Node* &o,const int dep,const int x)
{
	if(o->sz<=0)return -o->sz;
	int d[2]={1,0};
	if((x>>dep)&1)swap(d[0],d[1]);
	for(int i=0;i<2;i++)if(o->ch[d[i]])return Query(o->ch[d[i]],dep-1,x);
	assert(0);return -1;
}
void Delete(Node* &o)
{
	if(!o)return;
	for(int i=0;i<2;i++)Delete(o->ch[i]);
	delete o;o=NULL;
}
int ANS[100000];
struct QueryType
{
	int l,r,x,i;
	QueryType(){}
	QueryType(const int _l,const int _r,const int _x,const int _i):l(_l),r(_r),x(_x),i(_i){}
	bool operator<(const QueryType &q)const{return r<q.r;}
};
void Solve(const vector<QueryType>querys)
{
	Node *seg=NULL;
	int l=1,r=0;
	for(const QueryType &q:querys)
	{
		while(r<q.r)Modify(seg,30,A[++r]);
		while(l>q.l)Modify(seg,30,A[--l]);
		while(l<q.l)Remove(seg,30,A[l++]);
		assert(l==q.l&&r==q.r);
//		printf("(%d,%d,%d)\n",Sz(seg),l,r);
		assert(Sz(seg)==r-l+1);
		ANS[q.i]=Query(seg,30,q.x)^q.x;
	}
	Delete(seg);
}
vector<QueryType>QUERY[1000];
int M;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int querycount;testcount--;)
	{
		scanf("%d%d",&N,&querycount);
		M=max(N,(int)pow(N,0.6));
		for(int i=1;i<=N;i++)scanf("%d",&A[i]);
		for(int i=0;i<=N/M;i++)QUERY[i].clear();
		for(int l,r,x,i=0;i<querycount;i++)scanf("%d%d%d",&l,&r,&x),QUERY[l/M].push_back(QueryType(l,r,x,i));
		for(int i=0;i<=N/M;i++)
		{
			sort(QUERY[i].begin(),QUERY[i].end());
			Solve(QUERY[i]);
		}
		for(int i=0;i<querycount;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
