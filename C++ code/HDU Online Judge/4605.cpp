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
struct Node
{
	Node *ch[2];
	const int x;
	int sz;
	int cnt7,cnt2;
	int tag7,tag2;
	Node(const int _x):ch{NULL,NULL},x(_x),sz(1),cnt7(),cnt2(),tag7(),tag2(){}
	Node(Node *o):ch{o->ch[0],o->ch[1]},x(o->x),sz(o->sz),cnt7(o->cnt7),cnt2(o->cnt2),tag7(o->tag7),tag2(o->tag2){}
	void Add(const int v7,const int v2)
	{
		if(cnt7==-1)return;
		cnt7+=v7,cnt2+=v2;
		tag7+=v7,tag2+=v2;
	}
};
void PutDown(Node *o)
{
	assert(o);
	if(!o->tag7&&!o->tag2)return;
	for(int d=0;d<2;d++)if(o->ch[d])
	{
		o->ch[d]=new Node(o->ch[d]);
		o->ch[d]->Add(o->tag7,o->tag2);
	}
	o->tag7=o->tag2=0;
}
int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<a->sz)
	{
		PutDown(a=new Node(a));
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		PutDown(b=new Node(b));
		b->ch[0]=Merge(a,b->ch[0]);
		Maintain(b);
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,const int x)
{
	if(!o){a=b=NULL;return;}
	if((o->x)<=x)
	{
		PutDown(a=new Node(o));
		Split(a->ch[1],a->ch[1],b,x);
		Maintain(a);
	}
	else
	{
		PutDown(b=new Node(o));
		Split(b->ch[0],a,b->ch[0],x);
		Maintain(b);
	}
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
		Node *a,*b,*c;
		Split(S[u],b,c,W[u]);
		Split(b,a,b,W[u]-1);
//		printf("%d %d %d\n",Sz(a),Sz(b),Sz(c));
		assert(a),assert(c);
		a->Add(0,1),b->cnt7=-1,c->Add(d,3);
		S[ET[u][d]]=Merge(a,Merge(b,c));
		BuildTree(ET[u][d]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
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
			S[0]=NULL;
			for(const int v:tmp)S[0]=Merge(S[0],new Node(v));//,printf("%d ",v);puts("");
			S[0]=Merge(S[0],new Node(INF));
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
	return 0;
}
