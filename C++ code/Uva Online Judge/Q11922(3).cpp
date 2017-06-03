#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct nodetype
{
	int v,f,sum;
	bool tag;
	nodetype *ch[2];
	nodetype(int v):v(v)
	{
		ch[0]=ch[1]=NULL;
		sum=1;
		tag=false;
		f=rand();
	}
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
	}
	void putdown()
	{
		if(!tag)return;
		tag^=1;
		nodetype *a=ch[0];
		ch[0]=ch[1];
		ch[1]=a;
		if(ch[0]!=NULL)ch[0]->tag^=1;
		if(ch[1]!=NULL)ch[1]->tag^=1;
	}
};
void rotate(nodetype* &o,int d)
{
	nodetype *k=o->ch[d^1];
	k->putdown();
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void insert(nodetype* &o,int v)
{
	if(o==NULL)
	{
		o=new nodetype(v);
		return;
	}
	int d=v<o->v?0:1;
	insert(o->ch[d],v);
	o->maintain();
	if(o->ch[d]->f>o->f)rotate(o,d^1);
}
void splay(nodetype* &o,int r)
{
	o->putdown();
	int tr=1;if(o->ch[0]!=NULL)tr+=o->ch[0]->sum;
	if(tr==r)return;
	int d=r<tr?0:1;
	if(r>tr)r-=tr;
	splay(o->ch[d],r);
	rotate(o,d^1);
}
nodetype *root;
int n,m;
void dfsprint(nodetype* &o)
{
	if(o==NULL)return;
	o->putdown();
	dfsprint(o->ch[0]);
	printf("%d\n",o->v);
	dfsprint(o->ch[1]);
}
void dfsprint(nodetype* &o,int dep)
{
	if(o==NULL)return;
	o->putdown();
	dfsprint(o->ch[0],dep+1);
	for(int i=0;i<dep;i++)printf(" ");
	printf("%d\tsum=%d\n",o->v,o->sum);
	dfsprint(o->ch[1],dep+1);
}
void sink(nodetype* &o)
{
	int d;
	o->putdown();
	if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
	{
		d=o->ch[0]->f>o->ch[1]->f?0:1;
	}
	else
	{
		if(o->ch[0]!=NULL)d=0;
		else if(o->ch[1]!=NULL)d=1;
		else return;
	}
	if(o->f>=o->ch[d]->f)return;
	rotate(o,d^1);
	sink(o->ch[d^1]);
}
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	root=NULL;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)insert(root,i);
	//printf("%d\n",root->sum);
	//dfsprint(root);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		//printf(" root:a=%d b=%d\n %d\n",a,b,m);dfsprint(root,0);
		splay(root,b);
		nodetype *r=root->ch[1];
		//printf(" r   :a=%d b=%d\n %d\n",a,b,m);dfsprint(r,0);
		root->ch[1]=NULL;
		root->maintain();
		sink(root);
		splay(root,a);
		nodetype *l=root->ch[0];
		//printf(" l   :a=%d b=%d\n %d\n",a,b,m);dfsprint(l,0);
		root->ch[0]=NULL;
		root->maintain();
		//printf(" root:a=%d b=%d\n %d\n",a,b,m);dfsprint(root,0);
		if(l==NULL)l=r;
		else
		{
			splay(l,l->sum);
			l->ch[1]=r;
			l->maintain();
			sink(l);
		}
		//printf(" l   :a=%d b=%d\n %d\n",a,b,m);dfsprint(l,0);
		root->tag^=1;
		if(l==NULL)l=root;
		else
		{
			splay(l,l->sum);
			l->ch[1]=root;
			l->maintain();
			sink(l);
		}
		root=l;
	}
	dfsprint(root);
	return 0;
}
