#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct nodetype
{
	int v,f,s;
	nodetype *ch[2];
	nodetype(int v):v(v)
	{
		f=rand();
		s=1;
		ch[0]=ch[1]=NULL;
	}
	void maintain()
	{
		s=1;
		if(ch[0]!=NULL)s+=ch[0]->s;
		if(ch[1]!=NULL)s+=ch[1]->s;
	}
	int cmp(int a){return a<v?0:1;}
};
nodetype *root;
void rotate(nodetype* &o,int d)
{
	nodetype *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
void insert(nodetype* &o,int v)
{
	//printf("pass %d\n",v);
	if(o==NULL){o=new nodetype(v);return;}
	//printf("now %d at %d\n",v,o->v);
	int d=o->cmp(v);
	insert(o->ch[d],v);
	o->maintain();
	if(o->ch[d]->f>o->f)rotate(o,d^1);
	o->maintain();
}
int n,m;
int main()
{
	freopen("in11922.txt","r",stdin);
	root=NULL;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		insert(root,i);
		printf("%d\n",root->s);
	}
	
	return 0;
}
