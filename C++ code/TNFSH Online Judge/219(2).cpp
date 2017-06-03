#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
unsigned int Random()
{
	static unsigned int seed=20151211;
	seed*=0xdefaced;seed+=200227;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	char v;
	int sz;
	bool flip;
	unsigned int pri;
	Node(const char _v):ch{NULL,NULL},v(_v),sz(1),flip(false),pri(Random()){}
	Node(const Node *o):ch{o->ch[0],o->ch[1]},v(o->v),sz(o->sz),flip(o->flip),pri(o->pri){}
};
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Flip(Node* &o)
{
	if(!o)return;
	o=new Node(o);
	o->flip^=true;
	swap(o->ch[0],o->ch[1]);
}
void PutDown(Node* &o)
{
	if(o->flip)
	{
		Flip(o->ch[0]),Flip(o->ch[1]);
		o->flip^=true;
	}
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri||(a->pri==b->pri&&Sz(a)>Sz(b)))
	{
		Node *ans=new Node(a);
		PutDown(ans);
		ans->ch[1]=Merge(ans->ch[1],b);
		Maintain(ans);
		return ans;
	}
	else
	{
		Node *ans=new Node(b);
		PutDown(ans);
		ans->ch[0]=Merge(a,ans->ch[0]);
		Maintain(ans);
		return ans;
	}
}
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){assert(loc==0),a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=new Node(o);
		PutDown(b);
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=new Node(o);
		PutDown(a);
		Split(a->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Print(Node* &o)
{
	if(!o)return;
	PutDown(o);
	Print(o->ch[0]);
	putchar(o->v);
	Print(o->ch[1]);
}
int main()
{
//	freopen("pd.in","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		static int n,m;
		static char tmp[10001];
		assert(scanf("%d%d%s",&n,&m,tmp)==3);
		assert(n>=1&&n<=10000);
		Node *root=NULL;
		for(int i=0;i<n;i++)
		{
			assert(tmp[i]>='a'&&tmp[i]<='z');
			root=Merge(root,new Node(tmp[i]));
		}
		for(int e,l,r;m--;)
		{
			assert(scanf("%d%d%d",&e,&l,&r)==3);
			static Node *a,*b,*c,*t;
//			Print(root);puts("");
//			printf("(%d,%d,%d)\n",e,l,r);
			Split(root,t,c,r);
			Split(t,a,b,l-1);
//			Print(a),putchar(' '),Print(b),putchar(' '),Print(c),puts("");
			if(e==1)Print(b),puts("");
			else if(e==2)root=Merge(Merge(a,b),Merge(b,c)),n+=r-l+1;
			else if(e==3)Flip(b),root=Merge(a,Merge(b,c));
			else assert(0);
			assert(n==Sz(root)&&n>=1&&n<=1000000000);
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
