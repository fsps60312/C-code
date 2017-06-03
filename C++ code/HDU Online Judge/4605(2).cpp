#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
const int INF=2147483647;
int Rand()
{
	static unsigned int seed=20160221;
	seed*=0xdefaced,seed+=115216;
	return (seed+=seed>>20)&0x7fffffff;
}
static int Node_COUNTER=0;
struct Node
{
	Node *ch[2];
	const int x;
	int sz;
	int cnt7,cnt2;
	int tag7,tag2;
	int ref;
	Node(const int _x):ch{NULL,NULL},x(_x),sz(1),cnt7(),cnt2(),tag7(),tag2(),ref(0)
	{
		Node_COUNTER++;
	}
	Node(Node *o):ch{o->ch[0],o->ch[1]},x(o->x),sz(o->sz),cnt7(o->cnt7),cnt2(o->cnt2),tag7(o->tag7),tag2(o->tag2),ref(0)
	{
		Node_COUNTER++;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->ref++;
	}
	~Node(){Node_COUNTER--;}
	void Add(const int v7,const int v2)
	{
		if(cnt7==-1)return;
		cnt7+=v7,cnt2+=v2;
		tag7+=v7,tag2+=v2;
	}
};
void Assign(Node* &o,Node *v)
{
	if(v)v->ref++;
	if(o&&!--o->ref)
	{
		for(int d=0;d<2;d++)Assign(o->ch[d],NULL);
		delete o;
	}
	o=v;
}
void PutDown(Node *o)
{
	assert(o);
	if(!o->tag7&&!o->tag2)return;
	for(int d=0;d<2;d++)if(o->ch[d])
	{
		Assign(o->ch[d],new Node(o->ch[d]));
		o->ch[d]->Add(o->tag7,o->tag2);
	}
	o->tag7=o->tag2=0;
}
int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Merge(Node* &o,Node *a,Node *b)
{
	if(a)a=new Node(a),a->ref++;
	if(b)b=new Node(b),b->ref++;
	if(!a||!b)Assign(o,a?a:b);
	else if(Rand()%(a->sz+b->sz)<a->sz)
	{
		Assign(o,a);
		PutDown(o);
		Merge(o->ch[1],o->ch[1],b);
		Maintain(o);
	}
	else
	{
		Assign(o,b);
		PutDown(o);
		Merge(o->ch[0],a,o->ch[0]);
		Maintain(o);
	}
	Assign(a,NULL),Assign(b,NULL);
}
void Split(Node *o,Node* &a,Node* &b,const int x)
{
	if(o)o=new Node(o),o->ref++;
	if(!o)Assign(a,NULL),Assign(b,NULL);
	else if((o->x)<=x)
	{
		Assign(a,o);
		PutDown(a);
		Split(a->ch[1],a->ch[1],b,x);
		Maintain(a);
	}
	else
	{
		Assign(b,o);
		PutDown(b);
		Split(b->ch[0],a,b->ch[0],x);
		Maintain(b);
	}
	Assign(o,NULL);
}
void Query(Node *o,const int x,int &cnt7,int &cnt2)
{
	if(!o)return;
	PutDown(o);
	if(x<=(o->x))
	{
		cnt7=o->cnt7,cnt2=o->cnt2;
		Query(o->ch[0],x,cnt7,cnt2);
	}
	else Query(o->ch[1],x,cnt7,cnt2);
}
Node *S[100000];
int N,W[100000];
vector<int>ET[100000];
void BuildTree(const int u)
{
//	printf("u=%d\n",u);
	if(ET[u].empty())return;
	assert((int)ET[u].size()==2);
	for(int d=0;d<2;d++)
	{
		Node *a=NULL,*b=NULL,*c=NULL;
		Split(S[u],b,c,W[u]);
		Split(b,a,b,W[u]-1);
		assert(a&&c);
		a->Add(0,1),b->cnt7=-1,c->Add(d,3);
		Merge(b,b,c);
		Merge(S[ET[u][d]],a,b);
		Assign(a,NULL),Assign(b,NULL),Assign(c,NULL);
		BuildTree(ET[u][d]);
	}
}
void Merge(Node* &o,const int x)
{
	Node *n=NULL;
	Assign(n,new Node(x));
	Merge(o,o,n);
	Assign(n,NULL);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<100000;i++)S[i]=NULL;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&W[i]);
		if(true)
		{
			int m;scanf("%d",&m);
			for(int u,a,b;m--;)
			{
				scanf("%d%d%d",&u,&a,&b),u--,a--,b--;
				ET[u].push_back(a),ET[u].push_back(b);
			}
		}
		if(true)
		{
			set<int>tmp;
			for(int i=0;i<N;i++)tmp.insert(W[i]-1),tmp.insert(W[i]);
			Assign(S[0],NULL);
			for(const int v:tmp)Merge(S[0],v);
			Merge(S[0],INF);
		}
		BuildTree(0);
		int querycount;scanf("%d",&querycount);
		for(int v,x,cnt7,cnt2;querycount--;)
		{
			scanf("%d%d",&v,&x),v--;
			Query(S[v],x,cnt7,cnt2);
			if(cnt7==-1)puts("0");
			else printf("%d %d\n",cnt7,cnt2);
		}
	}
//	printf("Node_COUNTER=%d\n",Node_COUNTER);
//	for(int i=0;i<100000;i++)Assign(S[i],NULL);
//	printf("Node_COUNTER=%d\n",Node_COUNTER);
//	assert(Node_COUNTER==0);
	return 0;
}
