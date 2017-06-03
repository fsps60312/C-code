#include<cstdio>
#include<cstdlib>
#include<ctime>
#define ULL unsigned long long
using namespace std;
ULL X[400001];
char tstr[200001];
struct nodetype
{
	int f,v,sum,tag;
	ULL hash,rhash;
	nodetype *ch[2];
	nodetype(int v):v(v)
	{
		f=rand();
		sum=1;
		hash=rhash=v;
		tag=0;
		ch[0]=ch[1]=NULL;
	}
	void maintain()
	{
		sum=1;
		hash=rhash=v;
		if(ch[0]!=NULL)
		{
			hash=hash+X[1]*ch[0]->hash;
			rhash=ch[0]->rhash+X[ch[0]->sum]*rhash;
			sum+=ch[0]->sum;
		}
		if(ch[1]!=NULL)
		{
			hash=ch[1]->hash+X[ch[1]->sum]*hash;
			rhash=rhash+X[sum]*ch[1]->rhash;
			sum+=ch[1]->sum;
		}
		//printf("m%d\n",sum);
	}
	void exchangehash()
	{
		int thash=hash;
		hash=rhash;
		rhash=thash;
	}
	void putdown()
	{
		if(!tag)return;
		tag^=1;
		nodetype *a=ch[0];
		ch[0]=ch[1];
		ch[1]=a;
		if(ch[0]!=NULL)
		{
			ch[0]->exchangehash();
			ch[0]->tag^=1;
		}
		if(ch[1]!=NULL)
		{
			ch[1]->exchangehash();
			ch[1]->tag^=1; 
		}
		maintain();
	}
};
void dfsprint(nodetype* &o,int pdown)
{
	if(o==NULL)return;
	if(pdown)o->putdown();
	dfsprint(o->ch[0],pdown);
	printf("%d",o->v);
	dfsprint(o->ch[1],pdown);
}
void rotate(nodetype* &o,int d)
{
	if(o->tag)
	{
		o->putdown();
		d^=1;
	}
	nodetype *k=o->ch[d^1];
	k->putdown();
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
void push_back(nodetype* &o,int v)
{
	if(o==NULL)
	{
		o=new nodetype(v);
		return;
	}
	//printf("a\n");
	o->putdown();
	//printf("b\n");
	push_back(o->ch[1],v);
	//printf("c\n");
	o->maintain();
	//printf("d\n");
	if(o->ch[1]->f>o->f)rotate(o,0);
}
void removetree(nodetype* &o)
{
	if(o==NULL)return;
	removetree(o->ch[0]);
	removetree(o->ch[1]);
	delete o;
	o=NULL;
}
void splay(nodetype* &o,int r)
{
	o->putdown();
	int tr=1;if(o->ch[0]!=NULL)tr+=o->ch[0]->sum;
	if(r==tr)return;
	int d=r<tr?0:1;
	if(d==1)r-=tr;
	splay(o->ch[d],r);
	rotate(o,d^1);
}
void sink(nodetype* &o)
{
	o->putdown();
	int d;
	if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
	{
		d=o->ch[0]->f>o->ch[1]->f?0:1;
	}
	else if(o->ch[0]!=NULL)d=0;
	else if(o->ch[1]!=NULL)d=1;
	else return;
	if(o->f>=o->ch[d]->f)return;
	rotate(o,d^1);
}
nodetype *root=NULL;
void insertone(int p,int v)
{
	//printf("%d %d\n",p,v);
	if(p==0)
	{
		//printf("a\n");
		nodetype *l=root;
		//printf("b\n");
		root=new nodetype(v);
		//printf("c\n");
		root->ch[1]=l;
		//printf("d\n");
		root->maintain();
		//printf("e\n");
		sink(root);
		//printf("f\n");
		return;
	}
	splay(root,p);
	nodetype *r=root->ch[1];
	root->ch[1]=NULL;
	root->maintain();
	sink(root);
	push_back(root,v);
	splay(root,root->sum);
	root->ch[1]=r;
	root->maintain();
	sink(root);
}
void removeone(int p)
{
	//printf("a%d %d\n",root->sum,p);
	splay(root,p);
	//printf("b\n");
	nodetype *r=root->ch[1];
	nodetype *l=root->ch[0];
	delete root;
	//printf("c\n");
	if(l==NULL)root=r;
	else
	{
		root=l;
		sink(root);
		splay(root,root->sum);
		root->ch[1]=r;
		root->maintain();
	}
	//printf("d\n");
	if(root==NULL)return;
	sink(root);
}
void reverse(int p1,int p2)
{
	//printf("\tr%d\n",root->sum);
	splay(root,p2);
	nodetype *r=root->ch[1];
	root->ch[1]=NULL;
	root->maintain();
	sink(root);
	//printf("\tr%d+%d\n",root->sum,r->sum);
	splay(root,p1);
	nodetype *l=root->ch[0];
	root->ch[0]=NULL;
	root->maintain();
	sink(root);
	//printf("\tr%d+%d+%d\n",l->sum,root->sum,r->sum);
	root->tag^=1;
	root->exchangehash();
	//printf("\tr%d+%d+%d\n",l->sum,root->sum,r->sum);
	if(l==NULL)l=root;
	else
	{
		splay(l,l->sum);
		l->ch[1]=root;
		l->maintain();
		sink(l);
	}
	//printf("\tr%d+%d\n",l->sum,r->sum);
	splay(l,l->sum);
	//printf("\tr%d+%d\n",l->sum,r->sum);
	//l->maintain();
	l->ch[1]=r;
	//printf("\tr%d+%d\n",l->sum,r->sum);
	l->maintain();//error
	//printf("\tr%d+%d\n",l->sum,r->sum);
	sink(l);
	root=l; 
}
ULL gethash(int p1,int p2)
{
	splay(root,p2);
	nodetype *r=root->ch[1];
	root->ch[1]=NULL;
	root->maintain();
	sink(root);
	splay(root,p1);
	nodetype *l=root->ch[0];
	root->ch[0]=NULL;
	root->maintain();
	//sink(root);
	ULL ans=root->hash;
	root->ch[0]=l;
	root->maintain();
	sink(root);
	splay(root,p2);
	root->ch[1]=r;
	root->maintain();
	sink(root);
	return ans;
}
bool samehash(int p1,int p2,int l)
{
	if(l==0)return true;
	int hash1=gethash(p1,p1+l-1);
	int hash2=gethash(p2,p2+l-1);
	return hash1==hash2;
}
int bnysearch(int p1,int p2)
{
	int Max=root->sum-p2+1,Min=0;
	while(Min<Max)
	{
		int mid=(Min+Max+1)/2;
		if(samehash(p1,p2,mid))Min=mid;
		else Max=mid-1;
	}
	return Min;
}
int n,m;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	X[0]=1;for(int i=1;i<=400000;i++)X[i]=X[i-1]*97;
	srand(time(NULL));
	while(scanf("%d%d",&n,&m)==2)
	{
		removetree(root);
		scanf("%s",tstr);
		for(int i=0;i<n;i++)
		{
			//printf("%d\n",i);
			if(tstr[i]=='0')push_back(root,0);
			else push_back(root,1);
		}
		while(m--)
		{
			int type;scanf("%d",&type);
			switch(type)
			{
				case 1:
				{
					//printf("1a%d\n",root->sum);
					int p,c;scanf("%d%d",&p,&c);
					//printf("%d %d\n",p,c);
					insertone(p,c);
					//printf("1b%d\n",root->sum);
				}break;
				case 2:
				{
					//printf("2a%d\n",root->sum);
					int p;scanf("%d",&p);
					removeone(p);
					//printf("pass\n");
					//printf("2b%d\n",root->sum);
				}break;
				case 3:
				{
					//printf("3a%d\n",root->sum);
					int p1,p2;scanf("%d%d",&p1,&p2);
					reverse(p1,p2);
					//printf("3b%d\n",root->sum);
				}break;
				case 4:
				{
					int p1,p2;scanf("%d%d",&p1,&p2);
					//printf("4a%d\n",root->sum);
					printf("%d\n",bnysearch(p1,p2));
					//printf("4b%d\n",root->sum);
				}break;
			}
		}
	}
	return 0;
}
