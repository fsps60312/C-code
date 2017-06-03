#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int max(const int a,const int b,const int c){return max(a,max(b,c));}
unsigned int MyRand()
{
	static unsigned int seed=20160126;
	seed*=0xdefaced,seed+=154223;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	int v;
	int sz,sum,lmx,mmx,rmx;
	bool tag;
	unsigned int pri;
	Node(const int _v):ch{NULL,NULL},v(_v),sz(1),sum(_v),lmx(_v),mmx(_v),rmx(_v),tag(false),pri(MyRand()){}
	void Modify(const int _v)
	{
		v=_v;
		sum=_v*sz;
		lmx=mmx=rmx=max(_v,sum);
		tag=true;
	}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
int Sum(Node* &o){return o?o->sum:0;}
int Lmx(Node* &o){return o?o->lmx:0;}
int Mmx(Node* &o){return o?o->mmx:0;}
int Rmx(Node* &o){return o?o->rmx:0;}
void PutDown(Node* &o)
{
	if(!(o->tag))return;
	for(int i=0;i<2;i++)if(o->ch[i])o->ch[i]->Modify(o->v);
	(o->tag)=false;
}
void Maintain(Node* &o)
{
	assert(!(o->tag));
	(o->sz)=Sz(o->ch[0])+1+Sz(o->ch[1]);
	(o->sum)=Sum(o->ch[0])+(o->v)+Sum(o->ch[1]);
	(o->lmx)=max(Lmx(o->ch[0]),Sum(o->ch[0])+(o->v),Sum(o->ch[0])+(o->v)+Lmx(o->ch[1]));
	(o->mmx)=max(Mmx(o->ch[0]),max(Rmx(o->ch[0]),0)+(o->v)+max(Lmx(o->ch[1]),0),Mmx(o->ch[1]));
	(o->rmx)=max(Rmx(o->ch[0])+(o->v)+Sum(o->ch[1]),(o->v)+Sum(o->ch[1]),Rmx(o->ch[1]));
}
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;o=NULL;
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if((a->pri)>(b->pri))
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
	if(!o){assert(loc==0);a=b=NULL;return;}
	PutDown(o);
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Insert(const int x,const int k,const int v)
{
	Node *a,*b,*o=NULL;
	for(int i=0;i<k;i++)o=Merge(o,new Node(v));
	Split(ROOT,a,b,x);
	ROOT=Merge(a,Merge(o,b));
}
void Delete(const int x,const int k)
{
	Node *a,*b,*c;
	Split(ROOT,b,c,x+k);
	Split(b,a,b,x);
	assert(Sz(b)==k);
	Delete(b);
	ROOT=Merge(a,c);
}
void Modify(const int x,const int k,const int v)
{
	Node *a,*b,*c;
	Split(ROOT,b,c,x+k);
	Split(b,a,b,x);
	assert(Sz(b)==k);
	b->Modify(v);
	ROOT=Merge(a,Merge(b,c));
}
int QuerySum(const int l,const int r)
{
	Node *a,*b,*c;
	Split(ROOT,b,c,r),Split(b,a,b,l);
	const int ans=Sum(b);
	ROOT=Merge(a,Merge(b,c));
	return ans;
}
int N;
int main()
{
//	freopen("inn.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int opecount;scanf("%d%d",&N,&opecount);
		Delete(ROOT);
		for(int i=0,v;i<N;i++)scanf("%d",&v),ROOT=Merge(ROOT,new Node(v));
		for(int type,x,k,v;opecount--;)
		{
			scanf("%d",&type);
			switch(type)
			{
				case 0://Insert
				{
					scanf("%d%d%d",&x,&k,&v),x--;
					Insert(x+1,k,v);
				}break;
				case 1://Delete
				{
					scanf("%d%d",&x,&k),x--;
					Delete(x,k);
				}break;
				case 2:
				{
					scanf("%d%d%d",&x,&k,&v),x--;
					Modify(x,k,v);
				}break;
				case 3:
				{
					scanf("%d%d",&x,&k),x--;
					printf("%d\n",QuerySum(x,x+k));
				}break;
				case 4:printf("%d\n",Mmx(ROOT));break;
				default:assert(0);break;
			}
		}
	}
	assert(scanf("%d",&testcount)==-1);
	return 0;
}
