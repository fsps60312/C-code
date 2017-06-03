#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
struct Node
{
	Node *ch[2];
	int sz,pri;
	char c;
	Node(const char &_c):sz(1),pri(rand()),c(_c),ch{NULL,NULL}{}
}*ROOT;
int Sz(Node* &o){return o?o->sz:0;}
void Pull(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Copy(Node* &o)
{
	Node *ans=new Node(o->c);
	ans->ch[0]=o->ch[0];
	ans->ch[1]=o->ch[1];
	return ans;
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		Node *o=Copy(a);
		o->ch[1]=Merge(o->ch[1],b);
		Pull(o);
		return o;
	}
	else
	{
		Node *o=Copy(b);
		o->ch[0]=Merge(a,o->ch[0]);
		Pull(o);
		return o;
	}
}
void Split(Node* &o,Node* &a,Node* &b,const int &loc)
{
	if(!o){a=b=NULL;return;}
	if(loc>Sz(o->ch[0]))
	{
		a=Copy(o);
		Split(a->ch[1],a->ch[1],b,loc-Sz(a->ch[0])-1);
		Pull(a);
	}
	else
	{
		b=Copy(o);
		Split(b->ch[0],a,b->ch[0],loc);
		Pull(b);
	}
}
int M,N,CNT;
char S[1000001];
void DfsPrint(Node* &o)
{
	if(!o)return;
	if(CNT<M)DfsPrint(o->ch[0]);
	if(CNT<M){CNT++;printf("%c",o->c);}
	if(CNT<M)DfsPrint(o->ch[1]);
}
int main()
{
	scanf("%d%s%d",&M,S,&N);
	ROOT=NULL;
	for(int i=0;S[i];i++)ROOT=Merge(ROOT,new Node(S[i]));
	for(int i=0;i<N;i++)
	{
		static int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		Node *a,*b,*c;
		Node *n1,*n2;
		Split(ROOT,b,c,r+1);
		Split(b,a,b,l);
		Split(ROOT,n1,n2,x);
		ROOT=Merge(n1,Merge(b,n2));
	}
	CNT=0;
	DfsPrint(ROOT);
	return 0;
}
