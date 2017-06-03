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
}ID,COMP;
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
//		PutDown();puts("tle");
	}
	void PutDown()
	{
		if(!flip)return;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
		flip^=true;
	}
}*S[100000];
unsigned int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Parent(Node *o){assert(o);if(o->parent==-1)return NULL;return S[ID[o->parent]];}
int GetChId(Node *p,Node *o){assert(p);for(int d=0;d<2;d++)if(p->ch[d]==o)return d;return -1;}
void Rotate(Node *o,const int cu)
{
	assert(o);
	assert(o->ch[cu]);
	o->PutDown(),o->ch[cu]->PutDown();
	Node *u=o;
	o=o->ch[cu];
	if(true)
	{
		Node *p=Parent(u);
		int d;
		if(p&&(d=GetChId(p,u))!=-1)Parent(u)->ch[d]=o;
	}
	o->parent=u->parent,u->parent=o->id;
	if(o->ch[cu^1])o->ch[cu^1]->parent=u->id;
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node *o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[0])<Sz(o->ch[1]))Rotate(o,1);
}
void FlipAll(Node *o)
{
	assert(o);
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
		Rotate(p,d);
		assert(p->parent==o->id);
		Rotate(p);
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
	assert(pre);
	return pre;
}
void MakeRoot(Node *o)
{
	Access(o)->Flip();
}
int Merge(Node* &o,const int id)
{
	if(!o)return 0;
	int ans=1;
	ans+=Merge(o->ch[0],id)+Merge(o->ch[1],id);
	assert(ID.merge(o->id,id));
	const int u=o->id;
	delete S[u];S[u]=NULL;
	return ans;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	for(int i=0;i<100000;i++)S[i]=NULL;
	for(int m;testcount--;)
	{
		scanf("%d%d",&N,&m);
		for(int i=0;i<N;i++)
		{
			if(S[i])delete S[i];
			S[i]=new Node(i);
		}
		ID.clear(N),COMP.clear(N);
		int ans=0;
		bool print=false;
		for(int a,b;;m--)
		{
			assert(m>=0);
			if(m==0)
			{
				if(!print)scanf("%d",&m),print=true;
				if(m==0)break;
			}
			scanf("%d%d",&a,&b),a--,b--;
			a=ID[a],b=ID[b];
			if(a==b);
			else if(COMP[a]!=COMP[b])
			{
				MakeRoot(S[a]);
				Splay(S[a]);
				S[a]->parent=b;
				ans++;
				assert(COMP.merge(a,b));
			}
			else
			{
				Access(S[a]);
				Access(S[b]);
				Splay(S[a]);
				if(Parent(S[a])==S[b])
				{
					ans-=Merge(S[a]->ch[0],b);
					ID.merge(a,b),ans--;
				}
				else
				{
					Access(S[a]);
					Splay(S[b]);
					if(Parent(S[b])==S[a])
					{
						ans-=Merge(S[b]->ch[0],a);
						ID.merge(b,a),ans--;
					}
					else
					{
						assert(S[b]->parent!=-1);
						const int p=ID[S[b]->parent];
						ans-=Merge(S[b]->ch[0],p),ID.merge(b,p),ans--;
						Access(S[p]);
						assert(ID[S[a]->parent]==p);
						Splay(S[a]);
						ans-=Merge(S[a]->ch[0],p),ID.merge(a,p),ans--;
					}
				}
			}
			if(print)printf("%d\n",ans);
		}
	}
	return 0;
}
/*
1
4 0
4
1 2
3 4
2 3
1 4
*/
