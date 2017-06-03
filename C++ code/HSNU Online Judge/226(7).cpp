#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cassert>
#include<ctime>
using namespace std;
int MEM;
struct Node
{
	Node *ch[2];
	int sz,pri,ref;
	char c;
	Node(const char &_c):sz(1),pri(rand()),ref(0),c(_c),ch{NULL,NULL}{MEM++;}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
void Pull(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void AddRef(Node* &o){if(!o)return;o->ref++;}
void DelRef(Node* &o){if(!o)return;o->ref--;}
bool Delete(Node* &o)
{
	if(!o)return false;
	if(o->ref>0)return false;
	DelRef(o->ch[0]);
	Delete(o->ch[0]);
	DelRef(o->ch[1]);
	Delete(o->ch[1]);
	delete o;MEM--;
	o=NULL;
	return true;
}
//void Rotate(Node* &o,const int &cu)
//{
//	if(!o->ch[cu]->ch[cu^1])return;
//	if(o->ch[cu]->pri<o->pri)return;
//	if(o->ch[cu]->ch[cu^1]->pri>o->pri)return;
//	Node *u=o;
//	o=o->ch[cu];
//	u->ch[cu]=o->ch[cu^1];
//	o->ch[cu^1]=u;
//	Pull(u),Pull(o);
//}
//void Rotate(Node* &o)
//{
//	if(!o->ch[0]||!o->ch[1])return;
//	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
//	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
//}
void Assign(Node* &o,const int &d,Node* &ch)
{
	assert(o);
	Node *r=o->ch[d];
	DelRef(r);
	AddRef(ch);
	o->ch[d]=ch;
	Delete(r);
	Pull(o);
//	Rotate(o);
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
Node *Merge(Node* &a,Node* &b)
{
	if(!a||!b)
	{
		if(!a&&!b)return NULL;
		Node *o=Copy(a?a:b);
		Delete(a?a:b);
		return o;
	}
	if(a->pri>b->pri||(a->pri==b->pri&&Sz(a)>Sz(b)))
	{
		Node *o=Copy(a);
		Node *ch=Merge(a->ch[1],b);
		Assign(o,1,ch);
		Delete(a);
		return o;
	}
	else
	{
		Node *o=Copy(b);
		Node *ch=Merge(a,b->ch[0]);
		Assign(o,0,ch);
		Delete(b);
		return o;
	}
}
void Split(Node* &o,Node* &a,Node* &b,const int &loc)
{
	Delete(a),Delete(b);assert(a==NULL);assert(b==NULL);
	if(!o)return;
	if(loc>Sz(o->ch[0]))
	{
		Node *n=NULL;
		a=Copy(o);
		Split(o->ch[1],n,b,loc-Sz(o->ch[0])-1);
		Assign(a,1,n);
		Delete(o);
	}
	else
	{
		Node *n=NULL;
		b=Copy(o);
		Split(o->ch[0],a,n,loc);
		Assign(b,0,n);
		Delete(o);
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
}
//void Check(Node* &o,const int &pri,const int &dep=0)
//{
////	printf("dep=%d\n",dep);
//	assert(dep<=10000);
//	if(!o)return;
//	assert(o->pri<=pri);
//	Check(o->ch[0],o->pri,dep+1);
//	Check(o->ch[1],o->pri,dep+1);
//}
int main()
{
	srand(time(NULL));
//	freopen("in.txt","r",stdin);
	scanf("%d%s%d",&M,S,&N);
	Delete(ROOT);
	MEM=0;
	for(int i=0;S[i];i++)
	{
		Node *n=new Node(S[i]);
		ROOT=Merge(ROOT,n);
	}
//	printf("sMEM=%d\n",MEM);
//	printf("sz=%d ",Sz(ROOT));CNT=Sz(ROOT);DfsPrint(ROOT);puts(" s");
	for(int i=0;i<N;i++)
	{
		static int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		static Node *a=NULL,*b=NULL,*c=NULL,*o=NULL;
		static Node *n1=NULL,*n2=NULL;
		assert(a==NULL);assert(b==NULL);assert(c==NULL);assert(o==NULL);assert(n1==NULL);assert(n2==NULL);
		SplitO(ROOT,b,c,r+1);
		SplitO(b,a,b,l);
		Delete(a),Delete(c);
		Split(ROOT,n1,n2,x);assert(ROOT==NULL);
		o=Merge(b,n2);Delete(b),Delete(n2);
		ROOT=Merge(n1,o);Delete(n1),Delete(o);
		if(Sz(ROOT)>M)
		{
			SplitO(ROOT,ROOT,b,M);
			Delete(b);
		}
//		printf("SZ=%d,MEM=%d\n",Sz(ROOT),MEM);
//		Check(ROOT,2147483647);
	}
	CNT=M;
	DfsPrint(ROOT);
	puts("");
	return 0;
}
