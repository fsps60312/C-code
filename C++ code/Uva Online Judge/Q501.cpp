#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
struct nodetype
{
	int f,v,sum;
	nodetype *ch[2];
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum; 
	}
	int cmp(int a)
	{
		return a<v?0:1;
	}
};
nodetype *root;
void rotate(nodetype* &a,int d)
{
	nodetype *k=a->ch[d^1];
	a->ch[d^1]=k->ch[d];
	k->ch[d]=a;
	a->maintain(),k->maintain();
	a=k;
}
void insert(nodetype* &a,nodetype *b)
{
	int d=a->cmp(b->v);
	if(a->ch[d]==NULL)
	{
		a->ch[d]=b;
		b->maintain();
	}
	else
	{
		insert(a->ch[d],b);
	}
	a->maintain();
	if(a->ch[d]->f>a->f)rotate(a,d^1);
}
int qrank(nodetype *a,int rank)
{
	int b=1+(a->ch[0]==NULL?0:a->ch[0]->sum);
	if(rank==b)return a->v;
	if(rank<b)return qrank(a->ch[0],rank);
	return qrank(a->ch[1],rank-b);
}
nodetype in1[30000];
int in2[30000],K,M,N;
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	scanf("%d",&K);
	while(K--)
	{
		scanf("%d%d",&M,&N);
		root=&in1[0];
		for(int i=0;i<M;i++)
		{
			scanf("%d",&in1[i].v);
			in1[i].f=rand();
			in1[i].ch[0]=in1[i].ch[1]=NULL;
		}
		for(int i=0;i<N;i++)scanf("%d",&in2[i]);
		for(int i=0,j=0;i<M;i++)
		{
			if(i)insert(root,&in1[i]);
			while(i==in2[j]-1)
			{
				j++;
				if(j>N)break;
				printf("%d\n",qrank(root,j));
			}
		}
		if(K)printf("\n");
	}
	return 0;
}
