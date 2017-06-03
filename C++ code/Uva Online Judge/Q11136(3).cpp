#include<cstdio>
#include<cstdlib>
#include<ctime>
#define LL long long
using namespace std;
struct nodetype
{
	LL f,v;
	nodetype *ch[2];
	nodetype(LL v):v(v)
	{
		ch[0]=ch[1]=NULL;
		f=rand();
	}
};
void rotate(nodetype* &o,LL d)
{
	nodetype *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o=k;
}
void insert(nodetype* &o,LL v)
{
	if(o==NULL)
	{
		o=new nodetype(v);
		return;
	}
	LL d=v<o->v?0:1;
	insert(o->ch[d],v);
	if(o->ch[d]->f>o->f)rotate(o,d^1);
}
void removetree(nodetype* &o)
{
	if(o==NULL)return;
	removetree(o->ch[0]);
	removetree(o->ch[1]);
	delete o;
	o=NULL;
}
void remove(nodetype* &o)
{
	if(o->ch[1]!=NULL&&o->ch[0]!=NULL)
	{
		LL d=o->ch[0]->f>o->ch[1]->f?0:1;
		rotate(o,d^1);
		remove(o->ch[d^1]);
	}
	else
	{
		nodetype *k=o;
		if(o->ch[1]!=NULL)o=o->ch[1];
		else o=o->ch[0];
		delete k;
	}
}
LL getremovemax(nodetype* &o)
{
	if(o->ch[1]==NULL)
	{
		LL ans=o->v;//printf("max%lld\n",ans);
		remove(o);
		return ans;
	}
	return getremovemax(o->ch[1]);
}
LL getremovemin(nodetype* &o)
{
	if(o->ch[0]==NULL)
	{
		LL ans=o->v;
		remove(o);
		return ans;
	}
	return getremovemin(o->ch[0]);
}
LL n;
nodetype *root;
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(scanf("%lld",&n)==1&&n)
	{
		removetree(root);
		LL ans=0;
		for(LL i=0,j,k;i<n;i++)
		{
			scanf("%lld",&k);
			while(k--)
			{
				scanf("%lld",&j);
				//printf("a\n");
				insert(root,j);
				//printf("b\n");
				//printf("c\n");
			}
			LL addv=getremovemax(root)-getremovemin(root);
			//if(addv!=999999)printf("addv=%lld\n",addv);
			ans+=addv;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
