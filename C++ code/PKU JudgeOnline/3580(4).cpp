#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Node
{
	Node *ch[2];
	int sz,mn,add,v;
	bool rev;
	Node(){}
	Node(const int &_v):sz(1),mn(_v),add(0),v(_v),rev(false){ch[0]=ch[1]=NULL;}
}*ROOT=NULL;
void Add(Node* &o,const int &v){o->v+=v,o->mn+=v,o->add+=v;}
void PutDown(Node* &o)
{
	if(o->add!=0)
	{
		for(int i=0;i<2;i++)if(o->ch[i])Add(o->ch[i],o->add);
		o->add=0;
	}
	if(o->rev)
	{
		swap(o->ch[0],o->ch[1]);
		for(int i=0;i<2;i++)if(o->ch[i])o->ch[i]->rev^=true;
		o->rev=false;
	}
}
int Sz(Node* &o){return o?o->sz:0;}
int Mn(Node* &o){return o?o->mn:INF;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->mn=min(o->v,min(Mn(o->ch[0]),Mn(o->ch[1])));
}
void Rotate(Node* &o,const int &cu)
{
	PutDown(o),PutDown(o->ch[cu]);
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	PutDown(o);
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Insert(Node* &o,const int &v,const int &loc)
{
	if(!o){o=new Node(v);return;}
	PutDown(o);
	if(loc<Sz(o->ch[0]))Insert(o->ch[0],v,loc);
	else Insert(o->ch[1],v,loc-Sz(o->ch[0])-1);
	Maintain(o),Rotate(o);
}
void Splay(Node* &o,const int &loc)
{
	PutDown(o);
	if(Sz(o->ch[0])==loc)return;
	if(loc<Sz(o->ch[0]))Splay(o->ch[0],loc),Rotate(o,0);
	else Splay(o->ch[1],loc-Sz(o->ch[0])-1),Rotate(o,1);
}
void Delete(Node* &o)
{
	PutDown(o);
	if(o->ch[0]&&o->ch[1])
	{
		int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
		Rotate(o,cu);
		Delete(o->ch[cu^1]);
		Maintain(o);
	}
	else
	{
		int cu=(o->ch[0]?0:1);
		Node *u=o;
		o=o->ch[cu];
		delete u;
	}
}
void Delete(Node* &o,const int &loc)
{
	PutDown(o);
	if(Sz(o->ch[0])==loc){Delete(o);return;}
	else if(loc<Sz(o->ch[0]))Delete(o->ch[0],loc);
	else Delete(o->ch[1],loc-Sz(o->ch[0])-1);
	Maintain(o);
}
void CutCh(Node* &o,const int &loc,const int &d,Node* &u)
{
	Splay(o,loc);
	u=o->ch[d];
	o->ch[d]=NULL,Maintain(o);
}
Node* Merge(Node* &a,Node* &b)
{
	if(!a||!b)return a?a:b;
	if(Sz(a)>Sz(b))
	{
		Splay(a,Sz(a)-1);
		a->ch[1]=b,Maintain(a);
		return a;
	}
	else
	{
		Splay(b,0);
		b->ch[0]=a,Maintain(b);
		return b;
	}
}
void Modify(Node* &o,const int &l,const int &r,const int &v)
{
	Node *a,*b;
	CutCh(o,r,1,b),CutCh(o,l,0,a);
	if(v!=0)Add(o,v);
	else o->rev^=true;
	o=Merge(a,o);
	o=Merge(o,b);
}
int Query(Node* &o,const int &l,const int &r)
{
	Node *a,*b;
	CutCh(o,r,1,b),CutCh(o,l,0,a);
	const int ans=o->mn;
	o=Merge(a,o);
	o=Merge(o,b);
	return ans;
}
void Revolve(Node* &o,const int &l,const int &r,const int &t)
{
	Node *a,*b,*lpart;
	CutCh(o,r,1,b),CutCh(o,l,0,a);
	CutCh(o,Sz(o)-t,0,lpart);
	o=Merge(o,lpart);
	o=Merge(a,o);
	o=Merge(o,b);
}
void Print(Node* &o)
{
	if(!o)return;
	PutDown(o);
	if(o->ch[0]){printf("");Print(o->ch[0]);printf("");}
//	printf("(sz=%d,mn=%d,add=%d,v=%d)",o->sz,o->mn,o->add,o->v);
	printf(" %d",o->v);
	if(o->ch[1]){printf("");Print(o->ch[1]);printf("");}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	assert(scanf("%d",&N)==1);
	for(int i=0;i<N;i++)
	{
		static int v;assert(scanf("%d",&v)==1);
		Insert(ROOT,v,Sz(ROOT)-1);
	}
	scanf("%d",&M);
	while(M--)
	{
		static char tmp[7];assert(scanf("%s",tmp)==1);
//		printf("%s M=%d,sz=%d\n",tmp,M,Sz(ROOT));
		switch(tmp[0])
		{
			case'A':
			{
				static int x,y,d;assert(scanf("%d%d%d",&x,&y,&d)==3);
//				printf("(%d,%d,%d)\n",x,y,d);
				if(d!=0)Modify(ROOT,--x,--y,d);
			}break;
			case'D':
			{
				static int x;assert(scanf("%d",&x)==1);
//				printf("(%d)\n",x);
				Delete(ROOT,--x);
			}break;
			case'I':
			{
				static int x,p;assert(scanf("%d%d",&x,&p)==2);
//				printf("(%d,%d)\n",x,p);
				Insert(ROOT,p,--x);
			}break;
			case'M':
			{
				static int x,y;assert(scanf("%d%d",&x,&y)==2);
//				printf("(%d,%d)\n",x,y);
				printf("%d\n",Query(ROOT,--x,--y));
			}break;
			case'R':
			{
				if(tmp[3]=='E')
				{
					static int x,y;assert(scanf("%d%d",&x,&y)==2);
//					printf("(%d,%d)\n",x,y);
					Modify(ROOT,--x,--y,0);
				}
				else
				{
					static int x,y,t;assert(scanf("%d%d%d",&x,&y,&t)==3);
//					printf("(%d,%d,%d)\n",x,y,t);
					t%=y-x+1;if(t<0)t+=y-x+1;
					if(t!=0)Revolve(ROOT,--x,--y,t);
				}
			}break;
			default:printf("%s",tmp);assert(0);
		}
//		Print(ROOT);puts("");
	}
	return 0;
}
