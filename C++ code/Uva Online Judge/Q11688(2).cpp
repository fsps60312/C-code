#include<cstdio>
#include<cstdlib>
#include<stack>
using namespace std;
struct nodetype
{
	int f,b,o,idx,ans;
	int r0,r1;
	nodetype *ch[2],*mom;
	void maintain()
	{
		f=1;
		if(ch[0]!=NULL&&ch[0]->f+1>f)f=ch[0]->f+1;
		if(ch[1]!=NULL&&ch[1]->f+1>f)f=ch[1]->f+1;
	}
};
struct pairtype{int x,y;};
nodetype s[100001];
int n;
void shows()
{
	for(int i=1;i<=n;i++)printf("%d:%d %d %d,f=%d,o=%d\n",i,s[i].mom==NULL?0:s[i].mom->idx,s[i].ch[0]==NULL?0:s[i].ch[0]->idx,s[i].ch[1]==NULL?0:s[i].ch[1]->idx,s[i].f,s[i].o);
}
void maintainall(nodetype *a,int b)
{
	if(a->ch[0]!=NULL)maintainall(a->ch[0],b+1);
	if(a->ch[1]!=NULL)maintainall(a->ch[1],b+1);
	a->maintain();a->b=b;
}
void calr(nodetype *a)
{
	nodetype *c0=a->ch[0],*c1=a->ch[1];
	if(c0!=NULL)
	{
		if(c1!=NULL)
		{
			a->r0=c0->f>=c1->f?1:0;
			a->r1=c1->f>=c0->f?1:0;
		}
		else
		{
			a->r0=2147483647;
			a->r1=c0->f==1?0:-1;
		}
	}
	else
	{
		if(c1!=NULL)
		{
			a->r0=c1->f==1?0:-1;
			a->r1=2147483647;
		}
		else
		{
			a->r0=a->r1=2147483647;
		}
	}
	if(c0!=NULL)calr(c0);
	if(c1!=NULL)calr(c1);
}
void calans(nodetype *a,int b)
{
	a->ans=b;
	if(a->ch[0]!=NULL)calans(a->ch[0],b+a->r1);
	if(a->ch[1]!=NULL)calans(a->ch[1],b+a->r0);
}
pairtype newpair(int a,int b){pairtype p;p.x=a,p.y=b;return p;}
int main()
{
	//freopen("in.txt","r",stdin);
	//printf("%d\n",EOF);
	while(scanf("%d",&n)==1&&n)
	{
		for(int i=1;i<=n;i++)
		{
			s[i].ch[0]=s[i].ch[1]=s[i].mom=NULL;
			s[i].idx=i;
		}
		//printf("pass\n");
		for(int i=1,a,b;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			if(a)
			{
				s[i].ch[0]=&s[a];
				s[a].mom=&s[i];
				s[a].o=0;
			}
			if(b)
			{
				s[i].ch[1]=&s[b];
				s[b].mom=&s[i];
				s[b].o=1;
			}
		}
		stack<int> st;
		nodetype *root=&s[1];
		while(root->mom!=NULL)root=root->mom;
		maintainall(root,0);
		calr(root);
		calans(root,0);
		for(int i=1;i<=n;i++)printf("%d\n",root->f+s[i].ans);
	}
	return 0;
}
