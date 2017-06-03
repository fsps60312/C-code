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
	Node *ch[2],*parent;
	const int v;
	unsigned int sz;
	bool flip;
	Node(const int _v):ch{NULL,NULL},parent(NULL),v(_v),sz(1),flip(false){}
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
};
unsigned int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	o->parent=u->parent,u->parent=o,o->ch[cu^1]->parent=u;
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[0])<Sz(o->ch[1]))Rotate(o,1);
}
int GetChId(Node *p,Node *o){for(int d=0;d<2;d++)if(p->ch[d]==o)return d;return -1;}
Node* &GetMe(Node *o){Node *p=o->parent;assert(p);return p->ch[GetChId(p,o)];}
void Splay(Node *o,Node *pre)
{
	Splay(o->parent,o);
	o->PutDown();
	for(int d=0;d<2;d++)if(o->ch[d]==pre)
	{
		o->ch[d]->PutDown();
		Rotate(o,d);
		return;
	}
}
void Splay(Node *o){Splay(o->parent,o);}
Node *Access(Node *o)
{
	Node *pre=NULL;
	for(;o;o=o->parent)
	{
		Splay(o);
		o->ch[1]=pre;
		Maintain(pre=o);
	}
	return pre;
}
Node *S[100000];
int N;
int main()
{
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
			if((a=ID[a])==(b=ID[b]))continue;
			else if(Access(S[a])!=Access(S[b]))
			{
				Splay(S[a]);
				S[a]->ch[1]=NULL;
				Maintain(S[a]);
				S[a]->Flip();
				Splay(S[b]);
				S[b]->ch[1]=S[a],S[a]->parent=S[b];
				Maintain(S[b]);
				ans++;
			}
			else
			{
				
			}
			if(print)printf("%d\n",ans);
		}
	}
	return 0;
}
