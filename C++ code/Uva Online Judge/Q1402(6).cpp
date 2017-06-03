#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
struct Node
{
	int idx,pri,sz,tospin,pos;
	Node *l,*r,*fa;
	void init(int i)
	{
		idx=i;
		pri=rand();
		sz=1;
		tospin=0;
		l=r=fa=NULL;
	}
	void spin()
	{
		Node *n=l;
		l=r;
		r=n;
		if(l)l->tospin^=1;
		if(r)r->tospin^=1;
	}
	void setfa()
	{
		fa=NULL;
		if(l)l->fa=this;
		if(r)r->fa=this;
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
	a->setfa();
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
	//printf("rotate(%d,%d)\n",l,r);
	//printf("a:");print(a,0);
	//printf("\nb:");print(b,0);
	//printf("\nc:");print(c,0);printf("\n");
	b->tospin^=1;
	//printf("pass\n");
	//printf("rotate(%d,%d)\na:",l,r);print(a,0);printf("\n");
	return merge(a,merge(b,c));
}
void get_pos(Node *n,Node *ch)
{
	if(n->fa==NULL)//root
	{
		push(n);
		n->pos=rank(n);
		if(ch)
		{
			if(ch==n->l)ch->pos=0;
			else ch->pos=n->pos;
		}
		return;
	}
	else
	{
		get_pos(n->fa,n);
		push(n);
		if(ch)
		{
			if(ch==n->l)ch->pos=n->pos;
			else ch->pos=n->pos+rank(n);
		}
		n->pos+=rank(n);
	}
}
int N;
struct Point
{
	int x,y;
}H[100001];
bool cmp_Point_y(Point a,Point b){return a.y<b.y||(a.y==b.y&&a.x<b.x);}
bool cmp_Point_x(Point a,Point b){return a.x<b.x;}
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(scanf("%d",&N)==1&&N)
	{
		Node *root=NULL;
		for(int p=1;p<=N;p++)
		{
			H[p].x=p;
			scanf("%d",&H[p].y);
		}
		sort(H+1,H+N+1,cmp_Point_y);
		for(int h=1;h<=N;h++)H[h].y=h;
		sort(H+1,H+N+1,cmp_Point_x);
		for(int p=1;p<=N;p++)
		{
			int i=H[p].y;
			//printf(" %d",i);
			TUBE[i].init(i);
			root=merge(root,&TUBE[i]);
		}
		//printf("pass\n");
		for(int h=1;h<=N;h++)
		{
			//printf("out %d\n",i);
			//print(root,0);printf("\n");
			//printf("%d\n",TUBE[i].pos);
			get_pos(&TUBE[h],NULL);
			if(h>1)printf(" ");
			printf("%d",TUBE[h].pos);
			root=rotate(root,h,TUBE[h].pos);
			//printf("%d complete\n",i);
		}
		printf("\n");
	}
	return 0;
}
