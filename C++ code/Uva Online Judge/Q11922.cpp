#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int n,m;
struct nodetype
{
	int f,r,sum,tag;
	nodetype *ch[2];
	int cmp(int a){return a<r?0:1;}
	void maintain()
	{
		printf("ma\n");
		sum=1;
		printf("mb\n");
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
	}
	void putdown()
	{
		if(!tag)return;
		if(ch[0]!=NULL)ch[0]->tag^=1;
		if(ch[1]!=NULL)ch[1]->tag^=1;
		nodetype *a=ch[0];
		ch[0]=ch[1];
		ch[1]=a;
	}
};
struct treaptype
{
	nodetype *root;
	void clear(){root=NULL;}
	void rotate(nodetype* &a,int d)
	{
		if(a->tag)
		{
			a->putdown();
			d^=1;
		}
		nodetype *b=a->ch[d^1];
		b->putdown();
		printf("ra\n");
		if(a==NULL)printf("anull\n");
		a->ch[d^1]=b->ch[d];
		if(a==NULL)printf("bnull\n");
		b->ch[d]=a;
		a->maintain();
		printf("rb\n");
		b->maintain();
		a=b;
	}
	void insert(nodetype* &a,nodetype *b)
	{
		int d=a->cmp(b->r);
		if(a->ch[d]==NULL)
		{
			b->maintain();
			a->ch[d]=b;
		}
		//printf("a\n");
		else insert(a->ch[d],b);
		//printf("b\n");
		a->maintain();
		if(a->ch[d]->f>a->f)rotate(a,d^1);
		//a->maintain();
	}
	void insert(nodetype *b)
	{
		if(root==NULL){root=b;b->maintain();}
		else insert(root,b);
	}
	//
	void splay(nodetype* &o,int r)
	{
		int d;
		int tr=1;if(o->ch[0]!=NULL)tr+=o->ch[0]->sum;
		if(r==tr)return;
		if(r<tr)splay(o->ch[d=0],r);
		else splay(o->ch[d=1],r-tr);
		printf("sa\n");
		rotate(o,d^1);
		printf("sb\n");
	}
}T;
void showans(nodetype* &a)
{
	a->putdown();
	if(a->ch[0]!=NULL)showans(a->ch[0]);
	printf("%d\n",a->r);
	if(a->ch[1]!=NULL)showans(a->ch[1]);
}
void shown(nodetype *a)
{
	printf("%d:sum=%d",a->r,a->sum);
	if(a->ch[0]!=NULL)printf("\t0-%d",a->ch[0]->r);
	if(a->ch[1]!=NULL)printf("\t1-%d",a->ch[1]->r);
	printf("\n");
	if(a->ch[0]!=NULL)shown(a->ch[0]);
	if(a->ch[1]!=NULL)shown(a->ch[1]);
}
int main()
{
	freopen("in11922.txt","r",stdin);
	srand(time(NULL));
	scanf("%d%d",&n,&m);
	T.clear();
	for(int i=1;i<=n;i++)
	{
		//printf("%d\n",i);
		nodetype a;
		a.tag=0;
		a.r=i;
		a.f=rand();
		a.ch[0]=a.ch[1]=NULL;
		T.insert(&a);
		printf("%d\n",T.root->sum);
		//shown(T.root);
	}
	printf("pass\n");return 0;
		//shown(T.root);
	for(int i=0,a,b;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		printf("a%d %d\n",a,b);
		T.splay(T.root,b);
		printf("b\n");
		treaptype t1;
		t1.root=T.root->ch[1];
		T.root->ch[1]=NULL;
		T.root->maintain();
		T.splay(T.root,a);
		treaptype t2;
		t2.root=T.root->ch[1];
		T.root->ch[1]=t1.root;
		T.root->maintain();
		t2.root->tag^=1;
		T.splay(T.root,T.root->sum);
		T.root->ch[1]=t2.root;
		T.root->maintain();
	}
	showans(T.root);
	return 0;
}
