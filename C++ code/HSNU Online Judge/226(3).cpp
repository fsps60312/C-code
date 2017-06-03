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
void DelRef(Node* &o){if(!o)return;puts("DelRef");printf("c=%c\n",o->c);o->ref--;}
bool Delete(Node* &o)
{
	if(!o)return false;
	if(o->ref>0)return false;
	puts("a");
	printf("c=%c\n",o->c);
	DelRef(o->ch[0]);
	puts("b");
	Delete(o->ch[0]);
	puts("c");
	DelRef(o->ch[1]);
	puts("d");
	Delete(o->ch[1]);
	delete o;
	o=NULL;
	return true;
}
void Assign(Node* &o,const int &d,Node* &ch)
{
	assert(o);
	Node *r=o->ch[d];
	DelRef(r);
	AddRef(ch);
	o->ch[d]=ch;
	Delete(r);
	Pull(o);
}
Node *Copy(Node* &o)
{
	assert(o);
	Node *ans=new Node(o->c);
	ans->pri=o->pri;
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
		Node *ch=Merge(a->ch[1],b);
		Assign(o,1,ch);
		return o;
	}
	else
	{
		Node *o=Copy(b);
		Node *ch=Merge(a,b->ch[0]);
		Assign(o,0,ch);
		return o;
	}
}
void Split(Node* &o,Node* &a,Node* &b,const int &loc)
{
	Delete(a),Delete(b);assert(a==NULL);assert(b==NULL);
	if(!o){return;}
	if(loc>Sz(o->ch[0]))
	{
//		Delete(a);assert(a==NULL);
		Node *n=NULL;
		a=Copy(o);
		Split(o->ch[1],n,b,loc-Sz(o->ch[0])-1);
		Assign(a,1,n);
	}
	else
	{
//		Delete(b);assert(b==NULL);
		Node *n=NULL;
		b=Copy(o);
		Split(o->ch[0],a,n,loc);
		Assign(b,0,n);
	}
}
int M,N,CNT;
char S[1000001];
void DfsPrint(Node* &o)
{
	if(!o)return;
	if(CNT>0)DfsPrint(o->ch[0]);
	if(CNT>0){CNT--;printf("%c",o->c);}
	if(CNT>0)DfsPrint(o->ch[1]);
}
void SplitO(Node* &u,Node* &a,Node* &b,const int &loc)
{
	Node *o=Copy(u);
	Split(o,a,b,loc);
	Delete(o);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%s%d",&M,S,&N);
	Delete(ROOT);
	for(int i=0;S[i];i++)ROOT=Merge(ROOT,new Node(S[i]));
	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" s");
	for(int i=0;i<N;i++)
	{
		static int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		static Node *a=NULL,*b=NULL,*c=NULL,*o=NULL;
		static Node *n1=NULL,*n2=NULL;
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" 0");
		Delete(a);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" a");
		Delete(b);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" b");
		Delete(c);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" c");
		Delete(n1);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" d");
		Delete(n2);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" e");
		Delete(o);
//	CNT=Sz(ROOT);DfsPrint(ROOT);puts(" f");
		SplitO(ROOT,b,c,r+1);
		SplitO(b,a,b,l);
		SplitO(ROOT,n1,n2,x);
		assert(Delete(ROOT));
		Delete(a),Delete(c);
		o=Merge(b,n2);Delete(b),Delete(n2);
		ROOT=Merge(n1,o);Delete(n1),Delete(a);
//	CNT=Sz(o);DfsPrint(o);puts(" g");
		Delete(o);
//		if(Sz(ROOT)>M)
//		{
//			SplitO(ROOT,ROOT,b,M);
//			Delete(b);
//		}
	}
	CNT=M;
	DfsPrint(ROOT);
	return 0;
}
