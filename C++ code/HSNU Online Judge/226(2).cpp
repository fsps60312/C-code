#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cassert>
using namespace std;
struct Node
{
	Node *ch[2];
	int sz,pri,ref;
	char c;
	Node(const char &_c):sz(1),pri(rand()),ref(0),c(_c),ch{NULL,NULL}{}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
void Pull(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void AddRef(Node* &o){if(!o)return;o->ref++;}
void DelRef(Node* &o){if(!o)return;o->ref--;}
void Delete(Node* &o)
{
	if(!o)return;
	if(o->ref>0)return;
	DelRef(o->ch[0]);Delete(o->ch[0]);
	DelRef(o->ch[1]);Delete(o->ch[1]);
	delete o;
	o=NULL;
	return;
}
void Remove(Node* &o,const int &d){DelRef(o->ch[d]);Delete(o->ch[d]);}
void Assign(Node* &o,const int &d,Node* &ch)
{
	Remove(o,d);
	AddRef(ch);
	o->ch[d]=ch;
}
Node *Copy(Node* &o)
{
	Node *ans=new Node(o->c);
	Assign(ans,0,o->ch[0]);
	Assign(ans,1,o->ch[1]);
	return ans;
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		Node *o=Copy(a);
		Node *ch=Merge(o->ch[1],b);
		Assign(o,1,ch);
		Pull(o);
		return o;
	}
	else
	{
		Node *o=Copy(b);
		Node *ch=Merge(a,o->ch[0]);
		Assign(o,0,ch);
		Pull(o->ch[0]);
		return o;
	}
}
void Split(Node* &o,Node* &a,Node* &b,const int &loc)
{
	Delete(a),Delete(b);
	if(!o){return;}
	if(loc>Sz(o->ch[0]))
	{
		a=Copy(o);
		Node *n=NULL;
		Split(a->ch[1],n,b,loc-Sz(a->ch[0])-1);
		Assign(a,1,n);
		Pull(a);
	}
	else
	{
		b=Copy(o);
		Node *n=NULL;
		Split(b->ch[0],a,n,loc);
		Assign(b,0,n);
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
	Delete(ROOT);
	for(int i=0;S[i];i++)ROOT=Merge(ROOT,new Node(S[i]));
	for(int i=0;i<N;i++)
	{
		static int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		static Node *a=NULL,*b=NULL,*c=NULL,*rb=NULL;
		static Node *n1=NULL,*n2=NULL;
		Delete(a),Delete(b),Delete(c),Delete(rb),Delete(n1),Delete(n2);
		Split(ROOT,b,c,r+1);
		Split(rb=Copy(b),a,b,l);
		Split(ROOT,n1,n2,x);
		ROOT=Merge(n1,Merge(b,n2));
	}
	CNT=0;
	DfsPrint(ROOT);
	return 0;
}
