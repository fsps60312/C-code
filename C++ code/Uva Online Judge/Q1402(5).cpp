#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct Node
{
	int idx,pri,sz,tospin,pos;
	Node *l,*r;
	void init(int i)
	{
		idx=i;
		pri=rand();
		sz=1;
		tospin=0;
		l=r=NULL;
	}
	void spin()
	{
		Node *n=l;
		l=r;
		r=n;
		if(l)l->tospin^=1;
		if(r)r->tospin^=1;
	}
}TUBE[100001];
void push(Node *a)
{
	if(!a->tospin)return;
	//printf("a\n");
	a->spin();
	a->tospin^=1;
	//printf("b\n");
}
int sz(Node *a){return a?a->sz:0;}
void print(Node *n,int r)
{
	if(!n)return;
	push(n);
	print(n->l,r);
	n->pos=r+sz(n->l)+1;
	printf(" %d(%d)",n->idx,n->pos);
	print(n->r,r+sz(n->l)+1);
}
void pull(Node *a)
{
	a->sz=sz(a->l)+1+sz(a->r);
}
Node *merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	//printf("merge(%d)\n",a->idx);
	if(a->pri>b->pri)
	{
		push(a);
		a->r=merge(a->r,b);
		pull(a);
		return a;
	}
	else
	{
		push(b);
		b->l=merge(a,b->l);
		pull(b);
		return b;
	}
}
int rank(Node *a){return a?(a->tospin?sz(a->r)+1:sz(a->l)+1):0;}
void split(Node *n,Node* &a,Node* &b,int r)
{
	if(!n){a=b=NULL;return;}
	if(r>=rank(n))//n is on a
	{
		a=n;
		push(a);
		split(n->r,a->r,b,r-rank(n));
		pull(a);
	}
	else
	{
		b=n;
		push(b);
		split(n->l,a,b->l,r);
		pull(b);
	}
}
Node *rotate(Node *n,int l,int r)
{
	Node *a,*b,*c;
	split(n,b,c,r);
	split(b,a,b,l-1);
	printf("rotate(%d,%d)\n",l,r);
	//printf("a:");print(a,0);
	//printf("\nb:");print(b,0);
	//printf("\nc:");print(c,0);printf("\n");
	b->tospin^=1;
	//printf("pass\n");
	//printf("rotate(%d,%d)\na:",l,r);print(a,0);printf("\n");
	return merge(a,merge(b,c));
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(scanf("%d",&N)==1)
	{
		Node *root=NULL;
		for(int p=1;p<=N;p++)
		{
			int i;scanf("%d",&i);
			TUBE[i].init(i);
			root=merge(root,&TUBE[i]);
		}
		printf("pass\n");
		for(int i=1;i<=N;i++)
		{
			printf("out %d\n",i);
			print(root,0);printf("\n");
			root=rotate(root,i,TUBE[i].pos);
			//printf("%d complete\n",i);
		}
	}
	return 0;
}
