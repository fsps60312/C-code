#include<cstdio>
#include<cstdlib>
#include<ctime>
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
struct Node
{
	int h,f,sum,m;
	bool tag;
	Node *ch[2];
	Node(int h):h(h)
	{
		f=rand();
		ch[0]=ch[1]=NULL;
		sum=1;
		m=h;
		tag=false;
	}
	void swapch(){Node *t=ch[0];ch[0]=ch[1],ch[1]=t;}
	void maintain()
	{
		sum=1,m=h;
		if(ch[0]!=NULL)sum+=ch[0]->sum,m=min(m,ch[0]->m);
		if(ch[1]!=NULL)sum+=ch[1]->sum,m=min(m,ch[1]->m);
	}
};
Node *root=NULL;
void putdown(Node *o)
{
	if(!o->tag)return;
	o->tag=false;
	if(o->ch[0]!=NULL){o->ch[0]->tag=true;o->ch[0]->swapch();}
	if(o->ch[1]!=NULL){o->ch[1]->tag=true;o->ch[1]->swapch();}
}
void removetree(Node* &o)
{
	if(o==NULL)return;
	removetree(o->ch[0]);
	removetree(o->ch[1]);
	delete o;
	o=NULL;
}
void rotate(Node* &o,int d)
{
	Node *k=o->ch[d^1];
	putdown(o),putdown(k);
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
void push_back(Node* &o,int h)
{
	//printf("a\n");
	if(o==NULL)
	{
		//printf("b1\n");
		o=new Node(h);
		return;
	}
	//printf("b2\n");
	push_back(o->ch[1],h);
	o->maintain();
	if(o->f<o->ch[1]->f)rotate(o,0);
}
void splay(Node* &o,int r)
{
	putdown(o);
	int tr=1;if(o->ch[0]!=NULL)tr+=o->ch[0]->sum;
	if(r==tr)return;
	int d=0;
	if(r>tr)d=1,r-=tr;
	splay(o->ch[d],r);
	rotate(o,d^1);
}
void sink(Node* &o)
{
	putdown(o);
	int d;
	if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
	{
		d=o->ch[0]->f>o->ch[1]->f?0:1;
	}
	else if(o->ch[0]!=NULL)d=0;
	else if(o->ch[1]!=NULL)d=1;
	else return;
	if(o->ch[d]->f<o->f)return;
	rotate(o,d^1);
	sink(o->ch[d^1]); 
}
int querypos(Node *o)
{
	if(o==NULL)return 0;
	putdown(o);
	int r=1;
	if(o->ch[0]!=NULL)
	{
		if(o->m==o->ch[0]->m)return querypos(o->ch[0]);
		r+=o->ch[0]->sum;
	}
	if(o->h==o->m)return r;
	return r+querypos(o->ch[1]);
}
int findmin(int p)
{
	splay(root,p);
	Node *l=root->ch[0];root->ch[0]=NULL;root->maintain();
	//sink(root);
	int ans=p-1+querypos(root);
	//splay(root,1);
	root->ch[0]=l;root->maintain();
	sink(root);
	return ans;
}
void rev(int lp,int rp)
{
	splay(root,rp);
	putdown(root);
	Node *r=root->ch[1];root->ch[1]=NULL;root->maintain();
	splay(root,lp);
	putdown(root);
	Node *l=root->ch[0];root->ch[0]=NULL;root->maintain();
	root->swapch();root->tag=true;
	if(l==NULL)l=root;
	else
	{
		splay(l,l->sum);
		l->ch[1]=root;l->maintain();sink(l);
	}
	root=l;
	splay(root,root->sum);
	root->ch[1]=r;root->maintain();sink(root);
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(scanf("%d",&N)==1&&N)
	{
		removetree(root);
		for(int p=1,h;p<=N;p++)
		{
			scanf("%d",&h);
			push_back(root,h);
		}
		for(int p=1;p<=N;p++)
		{
			if(p>1)printf(" ");
			int rp=findmin(p);
			printf("%d",rp);
			rev(p,rp);
		}
		printf("\n");
	}
	return 0;
}
