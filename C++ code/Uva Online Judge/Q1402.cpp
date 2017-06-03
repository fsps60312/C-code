#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct Node
{
	int f,sum,idx;
	bool tag;
	Node *mom;
	Node *ch[2];
	void swapch(){Node *t=ch[0];ch[0]=ch[1];ch[1]=t;}
	void init(){ch[0]=ch[1]=mom=NULL;tag=false;sum=1;}
	void maintain(){sum=1;if(ch[0]!=NULL)sum+=ch[0]->sum;if(ch[1]!=NULL)sum+=ch[1]->sum;}
}S[100001];
Node *root;
void putdown(Node *o)
{
	if(!o->tag)return;
	o->tag=false;
	if(o->ch[0]!=NULL){o->ch[0]->tag^=1;o->ch[0]->swapch();}
	if(o->ch[1]!=NULL){o->ch[1]->tag^=1;o->ch[1]->swapch();}
}
void changemom(Node *o,Node *mom)
{
	if(o==NULL)return;
	o->mom=mom;
}
void rotate(Node* &o,int d)
{
	Node* k=o->ch[d^1];
	//if(k==NULL)printf("NULL\n");else printf("NOT\n"); 
	putdown(o),putdown(k);
	changemom(k->ch[d],o);o->ch[d^1]=k->ch[d];
	Node *omom=o->mom;
	changemom(o,k);
	//if(k==NULL)printf("NULL\n");else printf("NOT\n"); 
	k->ch[d]=o;
	o->maintain(),k->maintain();
	changemom(k,omom);o=k;
}
void push_back(Node* &o,int i)
{
	if(o==NULL)
	{
		S[i].init();
		o=&S[i];
		return;
	}
	push_back(o->ch[1],i);
	if(o->ch[1]->mom!=o)o->ch[1]->mom=o;
	if(o->f<o->ch[1]->f)rotate(o,0);
}
void splay(Node* &o,int r)
{
	putdown(o);
	int s=1;if(o->ch[0]!=NULL)s+=o->ch[0]->sum;
	if(r==s)return;
	int d=0;
	if(r>s)r-=s,d=1;
	splay(o->ch[d],r);
	rotate(o,d^1);
}
void putalldown(Node *o)
{
	if(o==NULL)return;
	putdown(o);
	putalldown(o->mom);
}
int querypos(Node *o)
{
	putalldown(o);
	int ans=1;
	if(o->ch[0]!=NULL)ans+=o->ch[0]->sum;
	while(o->mom!=NULL)
	{
		if(o->mom->ch[1]==o)
		{
			ans++;
			if(o->mom->ch[0]!=NULL)ans+=o->mom->ch[0]->sum;
		}
		o=o->mom;
	}
	return ans;
}
void sink(Node* &o)
{
	int d;
	if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
	{
		d=o->ch[0]->f>o->ch[1]->f?0:1;
	}
	else if(o->ch[0]!=NULL)d=0;
	else if(o->ch[1]!=NULL)d=1;
	else return;
	if(o->f>o->ch[d]->f)return;
	rotate(o,d^1);
	sink(o->ch[d^1]);
}
void inv(int lp,int rp)
{
	splay(root,rp);
	Node *r=root->ch[1];changemom(r,NULL);
	root->ch[1]=NULL;root->maintain();sink(root);
	splay(root,lp);
	Node *l=root->ch[0];changemom(l,NULL);
	root->ch[0]=NULL;root->maintain();sink(root);
	root->swapch();root->tag=true;
	if(l==NULL)l=root;
	else
	{
		splay(l,l->sum);
		l->ch[1]=root;changemom(root,l);l->maintain();sink(l);
	}
	root=l;
	splay(root,root->sum);
	root->ch[1]=r;changemom(r,root);root->maintain();sink(root);
}
int N;
void shownodes()
{
	for(int i=1;i<=N;i++)printf("Node[%d]:%d,%d %d,pos=%d\n",i,S[i].mom!=NULL?S[i].mom->idx:0
	,S[i].ch[0]!=NULL?S[i].ch[0]->idx:0,S[i].ch[1]!=NULL?S[i].ch[1]->idx:0
	,1+(S[i].ch[0]!=NULL?S[i].ch[0]->sum:0));
}
int main()
{
	freopen("in.txt","r",stdin);
	srand(time(NULL));
	for(int i=1;i<=100000;i++)S[i].f=rand(),S[i].idx=i;
	while(scanf("%d",&N)==1&&N)
	{
		root=NULL;
		for(int p=1,i;p<=N;p++)
		{
			scanf("%d",&i);
			printf("i=%d\n",i);
			push_back(root,i);
			printf("pass\n");
		}//,S[i].ch[0]!=NULL?S[i].ch[0]->idx:0
		shownodes();
		for(int i=1;;i++)
		{
			int p=querypos(&S[i]);
			printf("%d\n",p);
			if(i==N)break;
			int lp=i,rp=querypos(&S[i]);
			if(lp>rp)lp^=rp^=lp^=rp;
			inv(lp,rp);
			shownodes();
		}
	}
	return 0;
}
