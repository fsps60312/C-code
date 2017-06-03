#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<utility>
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
	bool exist;
	Node(const int _x):ch{NULL,NULL},x(_x),sz(1),cnt7(),cnt2(),tag7(),tag2(),exist(true){}
	void Add(const int v7,const int v2)
	{
		cnt7+=v7,cnt2+=v2;
		tag7+=v7,tag2+=v2;
	}
};
void PutDown(Node *o)
{
	assert(o);
	if(!o->tag7&&!o->tag2)return;
	for(int d=0;d<2;d++)if(o->ch[d])o->ch[d]->Add(o->tag7,o->tag2);
	o->tag7=o->tag2=0;
}
int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o)
{
	assert(!o->tag7&&!o->tag2);
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<(a->sz))
	{
		PutDown(a);
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		PutDown(b);
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
		PutDown(a=o);
		Split(a->ch[1],a->ch[1],b,x);
		Maintain(a);
	}
	else
	{
		PutDown(b=o);
		Split(b->ch[0],a,b->ch[0],x);
		Maintain(b);
	}
}
void Query(Node *o,const int x,int &cnt7,int &cnt2,int &min_dist)
{//find the node closest to x by keep updating answer
	if(!o)return;
	PutDown(o);
	if(x<=(o->x))
	{
		if((o->x)-x<min_dist)min_dist=(o->x)-x,cnt7=(o->exist?o->cnt7:-1),cnt2=o->cnt2;
		Query(o->ch[0],x,cnt7,cnt2,min_dist);
	}
	else Query(o->ch[1],x,cnt7,cnt2,min_dist);
}
void Delete(Node *o)
{
	if(!o)return;
	for(int d=0;d<2;d++)Delete(o->ch[d]);
	delete o;o=NULL;
}
int N,W[100000],ANS7[100000],ANS2[100000];
vector<int>ET[100000];
vector<pair<int,int> >QUERY[100000];
void AnswerQuery(const int u,Node* &o)//reference of "o" is necessary
{
	static int min_dist;
	for(const pair<int,int>&p:QUERY[u])Query(o,p.first,ANS7[p.second],ANS2[p.second],min_dist=INF),assert(min_dist!=INF);
	if(ET[u].empty())return;
	assert((int)ET[u].size()==2);
	for(int d=0;d<2;d++)
	{
		Node *a,*b,*c;
		Split(o,b,c,W[u]);
		Split(b,a,b,W[u]-1);
		assert(a),assert(c),assert(Sz(b)==1);
		a->Add(0,1),b->exist=false,c->Add(d,3);
		AnswerQuery(ET[u][d],o=Merge(a,Merge(b,c)));
		//reference of "o" is necessary, or "o" might not be the root now
		Split(o,b,c,W[u]);
		Split(b,a,b,W[u]-1);
		assert(a),assert(c),assert(Sz(b)==1);
		a->Add(0,-1),b->exist=true,c->Add(-d,-3);
		o=Merge(a,Merge(b,c));
	}
}
void CheckValidify(Node *o)
{
	if(!o)return;
	PutDown(o);
	CheckValidify(o->ch[0]),CheckValidify(o->ch[1]);
	assert(o->cnt7==0&&o->cnt2==0);
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
		int querycount;scanf("%d",&querycount);
		for(int i=0;i<N;i++)QUERY[i].clear();
		for(int i=0,v,x;i<querycount;i++)
		{
			scanf("%d%d",&v,&x),v--;
			QUERY[v].push_back(make_pair(x,i));
		}
		if(true)
		{
			set<int>tmp;
			for(int i=0;i<N;i++)tmp.insert(W[i]-1),tmp.insert(W[i]);
			tmp.insert(INF);
			Node *o=NULL;
			for(const int v:tmp)o=Merge(o,new Node(v));//,printf("%d ",v);puts("");
			assert(Sz(o)==(int)tmp.size());
			AnswerQuery(0,o);
			assert(Sz(o)==(int)tmp.size());
			CheckValidify(o);
			Delete(o);
		}
		for(int i=0;i<querycount;i++)
		{
			if(ANS7[i]==-1)puts("0");
			else printf("%d %d\n",ANS7[i],ANS2[i]);
		}
	}
	return 0;
}
