#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int Rand()
{
	static unsigned int seed=20160220;
	seed*=0xdefaced,seed+=142928;
	return (int)((seed+=seed>>20)&0x7fffffff);
}
struct Node
{
	Node *ch[2];
	const int h;
	int sz;
	Node(const int _h):ch{NULL,NULL},h(_h),sz(1){}
}*S[100000];
int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
struct Edge{int a,b,cost;};
vector<Edge>EDGE;
struct QueryType{int v,x,k,id;};
vector<QueryType>QUERY;
int N,M,DJ[100000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
void Insert(Node* &o,const int h)
{
	if(!o){o=new Node(h);return;}
	Insert(o->ch[h<(o->h)],h);
	Maintain(o);
	Rotate(o);
}
void Insert(Node *o,Node* &s)
{
	if(!o)return;
	Insert(o->ch[0],s),Insert(o->ch[1],s);
	Insert(s,o->h);
	delete o;o=NULL;
}
int Query(Node *o,const int k)
{
	assert(o);
	if(k<=Sz(o->ch[0]))return Query(o->ch[0],k);
	if(k==Sz(o->ch[0])+1)return o->h;
	return Query(o->ch[1],k-Sz(o->ch[0])-1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d%d%d",&N,&M,&querycount);
	for(int i=0,h;i<N;i++)scanf("%d",&h),S[i]=new Node(h);
	for(int i=0;i<M;i++)
	{
		static Edge e;
		scanf("%d%d%d",&e.a,&e.b,&e.cost),e.a--,e.b--;
		EDGE.push_back(e);
	}
	sort(EDGE.begin(),EDGE.end(),[](const Edge &a,const Edge &b){return a.cost<b.cost;});
	for(int i=0;i<querycount;i++)
	{
		static QueryType q;
		scanf("%d%d%d",&q.v,&q.x,&q.k),q.id=i,q.v--;
		QUERY.push_back(q);
	}
	sort(QUERY.begin(),QUERY.end(),[](const QueryType &a,const QueryType &b){return a.x<b.x;});
	for(int i=0;i<N;i++)DJ[i]=i;
	static int ans[500000];
	int ei=0;
	for(const QueryType &q:QUERY)
	{
		for(;ei<M&&EDGE[ei].cost<=q.x;ei++)
		{
			const Edge &e=EDGE[ei];
//			printf("edge(%d,%d,%d)\n",e.a+1,e.b+1,e.cost);
			if(Find(e.a)!=Find(e.b))
			{
				int a=Find(e.a),b=Find(e.b);
				if(S[a]->sz>S[b]->sz)swap(a,b);
				Insert(S[a],S[b]);
				DJ[a]=b;
			}
		}
		Node *o=S[Find(q.v)];
		if(q.k<1||q.k>(o->sz))ans[q.id]=-1;
		else ans[q.id]=Query(o,q.k);
//		printf("query(v=%d,x=%d,k=%d)=%d\n",q.v+1,q.x,q.k,ans[q.id]);
	}
	for(int i=0;i<querycount;i++)printf("%d\n",ans[i]);
	return 0;
}
