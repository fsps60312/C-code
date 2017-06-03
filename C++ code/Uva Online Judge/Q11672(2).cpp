#include<cstdio>
#include<vector>
#include<algorithm>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
struct Node
{
	Node *ch[2];
	int h,sum,v,sz;
	Node(int v):h(1),v(v),sum(v),sz(1){ch[0]=ch[1]=NULL;}
};
void show(Node *o)
{
	if(!o)return;
	show(o->ch[0]);
	printf(" %d",o->v);
	show(o->ch[1]);
}
char LINE[7];
int C;
int Sz(Node* &o){return o?o->sz:0;}
int H(Node* &o){return o?o->h:0;}
int Sum(Node* &o){return o?o->sum:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->h=1+max(H(o->ch[0]),H(o->ch[1]));
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
Node* Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->h>b->h)
	{
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		b->ch[0]=Merge(a,b->ch[0]);
		Maintain(b);
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(o->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(o->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Insert(Node* &o,int v,int loc)
{
//	printf("ins %d @ %d:",v,loc);show(o);puts("");
	Node *a,*b;
//	puts("a");
	Split(o,a,b,loc);
//	puts("b");
	o=Merge(Merge(a,new Node(v)),b);
//	puts("c");
}
int main()
{
//	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&C)==1&&C)
	{
		Node *root=NULL;
		printf("Scenario %d:\n",kase++);
		while(C--)
		{
			scanf("%s",LINE);
			switch(LINE[0])
			{
				case'd':
				{
					int i,j;scanf("%d%d",&i,&j);
					Node *a,*b,*c;
					Split(root,b,c,j+1);
					Split(b,a,b,i);
					root=Merge(a,c);
				}break;
				case'i':
				{
					int loc,n,r,m,a,c;
					scanf("%d%d%d%d%d%d",&loc,&n,&r,&m,&a,&c);
					vector<int>v;
					for(int i=0,b;i<r;i++)
					{
						scanf("%d",&b);
						v.push_back(b);
					}
					for(int i=r;i<n;i++)
					{
						v.push_back((v[i-r]*a+c)%m);
						c=(v[i-r]*a+c)/m%m;
					}
					Node *ins=NULL;
					for(int i=0;i<v.size();i++)ins=Merge(ins,new Node(v[i]));
					Node *n1,*n2;
					Split(root,n1,n2,loc);
					root=Merge(Merge(n1,ins),n2);
				}break;
				case's':
				{
					int i,j;scanf("%d%d",&i,&j);
					Node *a,*b,*c;
					Split(root,b,c,j+1);
					Split(b,a,b,i);
					printf("%d\n",Sum(b));
					root=Merge(Merge(a,b),c);
				}break;
				default:termin("can't handle %c\n",LINE[0]);
			}
//			printf("all:");show(root);puts("");
		}
		puts("");
	}
	return 0;
}
