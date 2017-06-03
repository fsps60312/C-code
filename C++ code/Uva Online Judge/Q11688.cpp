#include<cstdio>
#include<cstdlib>
#include<stack>
using namespace std;
struct nodetype
{
	int f,sum,o,idx;
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
void rotate(nodetype* &r,int d)
{
	//printf("a:\n");shows();
	nodetype *k=r->ch[d^1],*m=r->mom;
	int td=r->o;
	r->ch[d^1]=k->ch[d];
	if(k->ch[d]!=NULL){k->ch[d]->mom=r;k->ch[d]->o=d^1;}
	k->ch[d]=r;r->mom=k;r->o=d;
	r->maintain(),k->maintain();
	r=k;k->mom=m;k->o=td;
	//printf("b:\n");shows();
}
void maintainall(nodetype *a)
{
	if(a->ch[0]!=NULL)maintainall(a->ch[0]);
	if(a->ch[1]!=NULL)maintainall(a->ch[1]);
	a->maintain();
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
		maintainall(root);
		for(int i=1;i<=n;i++)
		{
			//shows();
			while(s[i].mom!=NULL)
			{
				//printf("s[i].o=%d\n",s[i].o);
				st.push(s[i].o);
				nodetype *m=s[i].mom;
				if(m->mom==NULL)rotate(m,s[i].o^1);
				else rotate(m->mom->ch[m->o],s[i].o^1);
				//shows();
			}
			//shows();
			printf("%d\n",s[i].f);
			while(!st.empty())
			{
				nodetype *m=&s[i];
				if(m->mom==NULL)rotate(m,st.top());
				else rotate(m->mom->ch[m->o],st.top());
				st.pop();
			}
		}
	}
	return 0;
}
