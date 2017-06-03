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
	void Print()
	{
		printf("(id=%d,parent=%d,ch[2]={%d,%d})",id+1,parent+1,ch[0]?ch[0]->id+1:0,ch[1]?ch[1]->id+1:0);
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
	printf("FlipAll:o->id=%d\n",o->id);
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
		puts("pass");
		Rotate(Parent(p)&&GetChId(Parent(p),p)!=-1?GetMe(p):p,d);
	}
}
Node *Access(Node *o)
{
	Node *pre=NULL;
	for(;o;o=Parent(o))
	{
		puts("a");
		printf("id=%d\n",o->id);
		Splay(o);
		puts("b");
		o->ch[1]=pre;
		Maintain(pre=o);
	}
	while(pre->ch[0])pre=pre->ch[0];
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
int Merge(Node* &o,const int id)
{
	if(!o)return 0;
	int ans=1;
	ans+=Merge(o->ch[0],id)+Merge(o->ch[1],id);
	assert(ID.merge(o->id,id));
	return ans;
}
void Check(Node* &o)
{
	if(!o)return;
	assert(o->sz==Sz(o->ch[0])+1+Sz(o->ch[1]));
	Check(o->ch[0]),Check(o->ch[1]);
}
bool VIS[100000];
void Print(Node* &o)
{
	if(!o)return;
	o->PutDown();
	Print(o->ch[0]),o->Print(),Print(o->ch[1]);
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
bool OnSameLink(Node *a,Node *b)
{
	Splay(a);
	while(a->ch[0])a=a->ch[0];
	Splay(b);
	while(b->ch[0])b=b->ch[0];
	return a==b;
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
			a=ID[a],b=ID[b];
			printf("a=%d,b=%d\n",a+1,b+1);
//			printf("root(%d,%d)=(%d,%d)\n",a,b,Access(S[a])->id,Access(S[b])->id);
//			if(true)
//			{
//				Node *p=Access(S[a]),*q=Access(S[b]);
//				printf("(%d,%d)->%d\n",p->id,q->id,p->id==q->id);
//			}
			if(a==b)puts("type(0)");
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
//puts("EEEEEEEEEEEEEEEEEEEEEEEEE");
//			PrintTrees();
//puts("EEEEEEEEEEEEEEEEEEEEEEEEE");
//				printf("root(%d)=%d\n",b+1,Access(S[b])->id+1);
//puts("EEEEEEEEEEEEEEEEEEEEEEEEE");
//			PrintTrees();
//puts("EEEEEEEEEEEEEEEEEEEEEEEEE");
				if(false)
				{
					if(OnSameLink(S[a],S[b]))
					{
						Splay(S[a]);
						const int asz=Sz(S[a]->ch[1]);
						Splay(S[b]);
						const int bsz=Sz(S[b]->ch[1]);
						if(asz<bsz)swap(a,b);
						Splay(S[a]);
						ans-=Merge(S[a]->ch[1],a);
						S[a]->ch[1]=NULL;
						Maintain(S[a]);
					}
					else
					{
						Access(S[b]);
						Splay(S[a]);
						const int p=S[a]->parent;
						assert(p!=-1);
						ans-=Merge(S[a],p);
						Splay(S[p]);
						ans-=Merge(S[p]->ch[1],p);
						S[p]->ch[1]=NULL;
						Maintain(S[p]);
					}
				}
			}
			if(print)printf("ans=%d\n",ans);
			for(int i=0;i<N;i++)Check(S[i]);
//			PrintTrees();
		}
	}
	return 0;
}
