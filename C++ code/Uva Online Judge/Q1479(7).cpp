#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<map>
using namespace std;
struct nodetype
{
	int sum,v,f;
	nodetype *ch[2];
	nodetype(int v):v(v)
	{
		ch[0]=ch[1]=NULL;
		sum=1;
		f=rand();
	}
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
	}
	int cmp(int a){return a<v?0:1;}
};
void rotate(nodetype* &a,int d)
{
	nodetype *b=a->ch[d^1];
	a->ch[d^1]=b->ch[d];
	b->ch[d]=a;
	a->maintain();
	b->maintain();
	a=b;
}
void insert(nodetype* &a,int v)
{
	if(a==NULL)a=new nodetype(v);
	else
	{
		int d=a->cmp(v);
		insert(a->ch[d],v);
		a->maintain();
		if(a->ch[d]->f>a->f)rotate(a,d^1);
	}
}
void remove(nodetype* &a,int v)
{
	if(a==NULL)
	{
		printf("error\n");
		return;
	}
	if(a->v==v)
	{
		if(a->ch[0]!=NULL&&a->ch[1]!=NULL)
		{
			int d=a->ch[0]->f>a->ch[1]->f?0:1;
			rotate(a,d^1);
			remove(a->ch[d^1],v);
		}
		else
		{
			nodetype *u=a;
			if(a->ch[0]!=NULL)a=a->ch[0];
			else a=a->ch[1];
			delete u;
		}
		if(a!=NULL)a->maintain();
	}
	else
	{
		remove(a->ch[a->cmp(v)],v);
		a->maintain();
	}
}
void removetree(nodetype* &a)
{
	if(a==NULL)return;
	removetree(a->ch[0]);
	removetree(a->ch[1]);
	delete a;
	a=NULL;
}
void inserttree(nodetype* &destiny,nodetype* &source)
{
	if(source==NULL)return;
	inserttree(destiny,source->ch[0]);
	inserttree(destiny,source->ch[1]);
	insert(destiny,source->v);
	delete source;
	source=NULL;
}
nodetype *root[20001];
int side[60001][3],qv[500000][2],Q,leader[20001];
char qtype[500000];
int findset(int a)
{
	if(leader[a]==a)return a;
	return leader[a]=findset(leader[a]);
}
int qrank(nodetype *a,int rank)
{
	if(a==NULL||rank<=0||rank>a->sum)return 0;
	int d=1;if(a->ch[1]!=NULL)d+=a->ch[1]->sum;
	if(rank==d)return a->v;
	if(rank<d)return qrank(a->ch[1],rank);
	return qrank(a->ch[0],rank-d);
}
int vertex[20001],N,M;
struct pairtype
{
	int x,y;
	bool operator<(pairtype a)const
	{
		return x<a.x||(x==a.x&&y<a.y);
	}
};
pairtype newpair(int a,int b){pairtype z;z.x=a,z.y=b;return z;}
int main()
{
	for(int i=0;i<20001;i++)root[i]=NULL;
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		//printf("%d %d\n",N,M);
		for(int i=1,a;i<=N;i++)
		{
			scanf("%d",&a);
			vertex[i]=a;
			leader[i]=i;
			removetree(root[i]);
			root[i]=new nodetype(a);
		}
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d",&side[i][0],&side[i][1]);
			side[i][2]=0;
		}
		Q=0;
		while(scanf("%c",&qtype[Q])==1&&qtype[Q]!='E')
		{
			switch(qtype[Q])
			{
				case'C':
				{
					scanf("%d",&qv[Q][0]);//if(kase==34)printf("kase%d ",qv[Q][0]);
					int a=qv[Q][0];
					qv[Q][1]=vertex[a];
					scanf("%d",&vertex[a]);//if(kase==34)printf("%d\n",vertex[qv[Q][0]]);
					root[a]->v=vertex[a];
				}break;
				case'Q':
				{
					scanf("%d%d",&qv[Q][0],&qv[Q][1]);
				}break;
				case'D':
				{
					scanf("%d",&qv[Q][0]);
					side[qv[Q][0]][2]=1;
				}break;
				default:
				{
					Q--;
				}break;
			}
			Q++;
		}
		for(int i=1;i<=M;i++)
		{
			if(!side[i][2])
			{
				int l1=findset(side[i][0]),l2=findset(side[i][1]);
				if(root[l1]->sum<root[l2]->sum)l1^=l2^=l1^=l2;
				if(l1!=l2)
				{
					leader[l2]=l1;
					inserttree(root[l1],root[l2]);
				}
			}
		}
		//printf("side:%d %d\n",side[0][2],side[1][2]);
		double ans1=0;
		int ans2=0;
		for(int i=Q-1;i>=0;i--)
		{
			//printf("%dpass\n",i);
			switch(qtype[i])
			{
				case'Q':
				{
					ans2++;
					int a=qrank(root[findset(qv[i][0])],qv[i][1]);
					//printf("a=%d\n",a);
					ans1+=a;
				}break;
				case'D':
				{
					int j=qv[i][0];
					int l1=findset(side[j][0]),l2=findset(side[j][1]);
					if(root[l1]->sum<root[l2]->sum)l1^=l2^=l1^=l2;
					if(l1!=l2)
					{
						leader[l2]=l1;
						inserttree(root[l1],root[l2]);
					}
				}break;
				case'C':
				{
					int j=findset(qv[i][0]);
					//printf("a\n");
					remove(root[j],vertex[qv[i][0]]);
					//printf("b\n");
					vertex[qv[i][0]]=qv[i][1];
					insert(root[j],qv[i][1]);
				}break;
			}
		}
		printf("Case %d: %.6lf\n",kase++,ans1/ans2);
	}
	return 0;
}
/*
4 5
-271482
52143
910150
-826298
4 3
4 3
2 3
1 3
3 1
Q 4 4
Q 4 2
Q 3 2
C 4 89620
E
*/
