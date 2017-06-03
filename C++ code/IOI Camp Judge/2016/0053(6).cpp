#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Djset
{
	int s[100000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	int operator[](const int i){return find(i);}
	bool merge(int a,int b)
	{
		if((a=find(a))==(b=find(b)))return false;
		s[a]=b;
		return true;
	}
}ID;
unsigned int Rand()
{
	static unsigned int seed=20160204;
	seed*=0xdefaced;
	seed+=124454;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	int parent;
	const int id;
	unsigned int sz;
	bool flip;
	Node(const int _id):ch{NULL,NULL},parent(-1),id(_id),sz(1),flip(false){}
	void Flip()
	{
		swap(ch[0],ch[1]);
		flip^=true;
	}
	void PutDown()
	{
		if(!flip)return;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
	}
}*S[100000];
unsigned int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	assert(o);
	assert(o->ch[cu]);
	Node *u=o;
	o=o->ch[cu];
	o->parent=u->parent,u->parent=o->id;
	if(o->ch[cu^1])o->ch[cu^1]->parent=u->id;
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
//void Rotate(Node* &o)
//{
//	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
//	else if(Sz(o->ch[0])<Sz(o->ch[1]))Rotate(o,1);
//}
Node *Parent(Node* &o){if(o->parent==-1)return NULL;return S[ID[o->parent]];}
int GetChId(Node *p,Node *o){for(int d=0;d<2;d++)if(p->ch[d]==o)return d;return -1;}
Node* &GetMe(Node *o){Node *p=Parent(o);assert(p);return p->ch[GetChId(p,o)];}
void FlipAll(Node *o)
{
	if(!o)return;
	Node *p=Parent(o);
	if(p&&GetChId(p,o)!=-1)FlipAll(p);
	o->PutDown();
}
void Splay(Node *o)
{
	FlipAll(o);
	Node *p;
	for(int d;(p=Parent(o))&&(d=GetChId(p,o))!=-1;)
	{
		Rotate(Parent(p)&&GetChId(Parent(p),p)!=-1?GetMe(p):p,d);
	}
}
Node *Access(Node *o)
{
	Node *pre=NULL;
	for(;o;o=Parent(o))
	{
		Splay(o);
		o->ch[1]=pre;
		Maintain(pre=o);
	}
	return pre;
}
void MakeRoot(Node *o)
{
	Access(o);
	Splay(o);//auto putdown
	o->ch[1]=NULL;
	Maintain(o);
	o->Flip();
}
void Merge(Node* &o,const int id)
{
	if(!o)return;
	Merge(o->ch[0],id),Merge(o->ch[1],id);
	ID.merge(o->id,id);
}
//void Check(Node* &o)
//{
//	if(!o)return;
//	assert(o->sz==Sz(o->ch[0])+1+Sz(o->ch[1]));
//	Check(o->ch[0]),Check(o->ch[1]);
//}
bool VIS[100000];
void Print(Node* &o)
{
	if(!o)return;
	o->PutDown();
	Print(o->ch[0]),printf("(%d,%d)",o->id,o->parent),Print(o->ch[1]);
	VIS[o->id]=true;
}
int N;
void PrintTrees()
{
	puts("begin");
	for(int i=0;i<N;i++)VIS[i]=false;
	for(int i=0;i<N;i++)if(!VIS[ID[i]])
	{
		Node *u=S[ID[i]];
		while(Parent(u)&&GetChId(Parent(u),u)!=-1)u=Parent(u);
		Print(u);puts("");
	}
	puts("end");
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int i=0;i<100000;i++)S[i]=new Node(i);
	for(int m;testcount--;)
	{
		scanf("%d%d",&N,&m);
		for(int i=0;i<N;i++){delete S[i];S[i]=new Node(i);}
		ID.clear(N);
		int ans=0;
		bool print=false;
		for(int a,b;;m--)
		{
			if(m==0)
			{
				if(!print)scanf("%d",&m),print=true;
				else break;
			}
			scanf("%d%d",&a,&b),a--,b--;
			if((a=ID[a])==(b=ID[b]))puts("type(0)");
			else if(Access(S[a])!=Access(S[b]))
			{
				puts("type(1)");
				MakeRoot(S[a]);
				Splay(S[b]);//auto putdown
				S[b]->ch[1]=S[a],S[a]->parent=b;
				Maintain(S[b]);
				ans++;
			}
			else
			{
				puts("type(2)");
				Access(S[b]);
				Splay(S[a]);
				const int p=S[a]->parent;
				Splay(S[p]);
				ans-=Sz(S[a])+Sz(S[p]->ch[1])+1;
				Merge(S[a],p);
				Merge(S[p]->ch[1],p);
				S[p]->ch[1]=NULL,Maintain(S[p]);
			}
			if(print)printf("%d\n",ans);
//			for(int i=0;i<N;i++)Check(S[i]);
			PrintTrees();
		}
	}
	return 0;
}
