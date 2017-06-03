#include"interactive/121.h"
#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
//void Init(int &N,int &M,int x[])
//{
//	N=5,M=5;
//	int xx[]={2,4,1,3,3};
//	for(int i=1;i<=N;i++)x[i]=xx[i-1];
//}
//int getNumQuestions(){return 2;}
//void getQuestion(int &K,int &J)
//{
//	static int kase=0,k[]={3,5},j[]={4,5};
//	K=k[kase],J=j[kase];
//	kase++;
//}
//void answer(int x)
//{
//	static int kase=0,xx[]={1,4};
//	printf("Answer(%d)\n",x);
//	puts(xx[kase++]==x?"AC":"WA");
//}
//////////////////////////////////////////////////
int Rand()
{
	static unsigned int seed=20151103;
	seed=seed*0xdefaced+205354;
	return seed&0x3fffffff;
}
struct Node
{
	Node *ch[2];
	int v,sz;
	Node(const int _v):v(_v),sz(1),ch{NULL,NULL}{}
};
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Copy(Node* &o)
{
	Node *ans=new Node(o->v);
	ans->ch[0]=o->ch[0];
	ans->ch[1]=o->ch[1];
	ans->sz=o->sz;
	return ans;
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->sz>b->sz)
	{
		Node *ans=Copy(a);
		ans->ch[1]=Merge(a->ch[1],b);
		Maintain(ans);
		return ans;
	}
	else
	{
		Node *ans=Copy(b);
		ans->ch[0]=Merge(a,b->ch[0]);
		Maintain(ans);
		return ans; 
	}
}
void Split(Node *o,Node* &a,Node* &b,int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=Copy(o);
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=Copy(o);
		Split(a->ch[1],a->ch[1],b,loc-1-Sz(o->ch[0]));
		Maintain(a);
	}
}
void SwapBead(Node* &o,int x,int y)
{
	if(x>y)swap(x,y);
	assert(x<y);
	Node *a,*b,*c,*d,*e;
	Split(o,d,e,y+1);
	Split(d,c,d,y);
	Split(c,b,c,x+1);
	Split(b,a,b,x);
	o=Merge(Merge(Merge(Merge(a,d),c),b),e);
}
int Query(Node* &o,int loc)
{
	assert(o);
	if(loc<Sz(o->ch[0]))return Query(o->ch[0],loc);
	else if(loc==Sz(o->ch[0]))return o->v;
	else return Query(o->ch[1],loc-Sz(o->ch[0])-1);
}
void Print(Node* &o)
{
	if(!o)return;
	Print(o->ch[0]);
	printf("%d",o->v);
	Print(o->ch[1]);
}
int N,M,Q,K,J,X[300001];
vector<Node*>BEAD,LOC;//column->bead,bead->column
int main()
{
	Init(N,M,X);
	Node *bead=NULL,*loc=NULL;
	for(int i=0;i<N;i++)bead=Merge(bead,new Node(i)),loc=Merge(loc,new Node(i));
	for(int i=1;i<=M;i++)X[i]--;
	BEAD.push_back(bead),LOC.push_back(loc);
	for(int i=1;i<=M;i++)
	{
		int b1=Query(bead,X[i]),b2=Query(bead,X[i]+1);
		SwapBead(bead,X[i],X[i]+1);
		SwapBead(loc,b1,b2);
//		printf("bead: ");Print(bead);puts("");
//		printf("loc : ");Print(loc);puts("");
		BEAD.push_back(bead);
		LOC.push_back(loc);
	}
	Q=getNumQuestions();
	while(Q--)
	{
		getQuestion(K,J);
		K--;
		answer(Query(LOC[J],K)+1);
	}
	return 0;
}
