#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
int rand()
{
	static int seed=95312;
	seed*=0xdefaced,seed+=20151028;seed+=seed>>7;
	return seed;
}
struct Node
{
	Node *ch[2];
	int pri;
	int v,sz,sum,ls,ms,rs;
	bool flip,makesame;
	Node(){}
	Node(const int _v):ch{NULL,NULL},pri(rand()),v(_v),sz(1),sum(_v),ms(_v),ls(max(0,_v)),rs(max(0,_v)),flip(false),makesame(false){}
	void Flip()
	{
		swap(ls,rs);
		swap(ch[0],ch[1]);
	}
	void MakeSame(const int _v)
	{
		v=_v;
		sum=sz*_v;
		ls=rs=max(0,sum);
		ms=max(_v,sum);
	}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
int Sum(Node* &o){return o?o->sum:0;}
int Ms(Node* &o){return o?o->ms:-INF;}
int Ls(Node* &o){return o?o->ls:0;}
int Rs(Node* &o){return o?o->rs:0;}
int max(const int a,const int b,const int c){return max(a,max(b,c));}
void PutDown(Node* &o)
{
	if(o->flip)
	{
		if(o->ch[0])o->ch[0]->Flip(),o->ch[0]->flip^=true;
		if(o->ch[1])o->ch[1]->Flip(),o->ch[1]->flip^=true;
		o->flip=false;
	}
	if(o->makesame)
	{
		if(o->ch[0])o->ch[0]->MakeSame(o->v),o->ch[0]->makesame=true;
		if(o->ch[1])o->ch[1]->MakeSame(o->v),o->ch[1]->makesame=true;
		o->makesame=false; 
	}
}
void Maintain(Node* &o)
{
	assert(!o->flip&&!o->makesame);
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
	o->ms=max(Ms(o->ch[0]),Ms(o->ch[1]),Rs(o->ch[0])+o->v+Ls(o->ch[1]));
	o->ls=max(Ls(o->ch[0]),Sum(o->ch[0])+o->v+Ls(o->ch[1]));
	o->rs=max(Rs(o->ch[1]),Rs(o->ch[0])+o->v+Sum(o->ch[1]));
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri||(a->pri==b->pri&&Sz(a)>Sz(b)))
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
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	PutDown(o);
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(o->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(o->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;
	o=NULL;
}
void Print(Node* &o)
{
	if(!o)return;
	PutDown(o);
	Print(o->ch[0]);
	printf(" %d",o->v);
	Print(o->ch[1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0,v;i<N;i++)
	{
		scanf("%d",&v);
		ROOT=Merge(ROOT,new Node(v));
	}
//	Print(ROOT);puts("");
	while(M--)
	{
		static char cmd[10];
		scanf("%s",cmd);
		switch(cmd[2])
		{
			case'S'://INSERT
			{
				static int p,k;
				Node *s=NULL;
				scanf("%d%d",&p,&k);
				for(int i=0;i<k;i++)
				{
					static int v;
					scanf("%d",&v);
					s=Merge(s,new Node(v));
				}
				Node *a,*b;
				Split(ROOT,a,b,p);
				ROOT=Merge(a,Merge(s,b));
			}break;
			case'L'://DELETE
			{
				static int p,k;
				scanf("%d%d",&p,&k);
				p--;
				Node *a,*b,*c;
				Split(ROOT,a,b,p);
				Split(b,b,c,k);
				ROOT=Merge(a,c);
				Delete(b);
			}break;
			case'K'://MAKE-SAME
			{
				static int p,k,l;
				scanf("%d%d%d",&p,&k,&l);
				p--;
				Node *a,*b,*c;
				Split(ROOT,a,b,p);
				Split(b,b,c,k);
				b->MakeSame(l),b->makesame=true;
				ROOT=Merge(a,Merge(b,c));
			}break;
			case'V'://REVERSE
			{
				static int p,k;
				scanf("%d%d",&p,&k);
				p--;
				Node *a,*b,*c;
				Split(ROOT,a,b,p);
				Split(b,b,c,k);
				b->Flip(),b->flip=true;
				ROOT=Merge(a,Merge(b,c));
			}break;
			case'T'://GET-SUM
			{
				static int p,k;
				scanf("%d%d",&p,&k);
				p--;
				Node *a,*b,*c;
				Split(ROOT,a,b,p);
				Split(b,b,c,k);
//				printf("SUM:b=");Print(b);puts("");
				printf("%d\n",Sum(b));
				ROOT=Merge(a,Merge(b,c));
			}break;
			case'X'://MAX-SUM
			{
				printf("%d\n",Ms(ROOT));
			}break;
			default:assert(0);
		}
//		Print(ROOT);puts("");
	}
	return 0;
}
