#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<vector>
using namespace std;
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
int N,T;
struct Node
{
	Node *ch[2];
	int pri,sz;
	char c;
	Node(char c):c(c),pri(rand()),sz(1),ch{NULL,NULL}{}
};
void show(Node *o)
{
	if(!o)return;
	show(o->ch[0]);
	printf("%c",o->c);
	show(o->ch[1]);
}
vector<Node*>V;
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
Node *Copy(Node* &o)
{
	if(!o)return NULL;
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
		a=Copy(a);
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		b=Copy(b);
		b->ch[0]=Merge(a,b->ch[0]);
		Maintain(b);
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=Copy(o);
		Split(o->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=Copy(o);
		Split(o->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Print(Node* &o,int l,int r,int &cprinted)
{
	if(!o||l>=Sz(o)||r<0)return;
	Print(o->ch[0],l,r,cprinted);
	int sz=Sz(o->ch[0]);
	if(l<=sz&&sz<=r)
	{
		printf("%c",o->c);
		if(o->c=='c')cprinted++;
	}
	Print(o->ch[1],l-sz-1,r-sz-1,cprinted);
}
int main()
{
//	freopen("in.txt","r",stdin);
	srand(7122);
	scanf("%d",&N);
	V.push_back(NULL);
	int vnow=0,cprinted=0;
	while(N--)
	{
		scanf("%d",&T);
		if(T<=2)V.push_back(Copy(V[vnow++]));
		Node* &root=V[vnow];
		switch(T)
		{
			case 1:
			{
				static char LINE[101];
				static int p;
				static Node *a,*b;
				scanf("%d%s",&p,LINE);
				p-=cprinted;
				Split(root,a,b,p);
				for(int i=0;LINE[i];i++)a=Merge(a,new Node(LINE[i]));
				root=Merge(a,b);
			}break;
			case 2:
			{
				static int p,c;
				static Node *l,*m,*r;
				scanf("%d%d",&p,&c);
				p-=cprinted,c-=cprinted;
				p--;
				Split(root,m,r,p+c);
				Split(m,l,m,p);
				root=Merge(l,r);
			}break;
			case 3:
			{
				static int v,p,c;
				scanf("%d%d%d",&v,&p,&c);
				v-=cprinted,p-=cprinted,c-=cprinted;
				p--;
				if(c>0)Print(V[v],p,p+c-1,cprinted);
				puts("");
			}break;
			default:termin("can't handle T:%d\n",T);
		}
//		printf("all:");show(V[vnow]);puts("");
	}
	return 0;
}
