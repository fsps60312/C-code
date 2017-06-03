#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	LL sum,v,sz,pri;
	Node(LL v):v(v),sum(v),sz(1),pri(rand()){ch[0]=ch[1]=NULL;}
};
int ran()
{
	static unsigned int x=20150816;
	return x=x*0xdefaced+17;
}
void show(Node *o)
{
	if(!o)return;
	show(o->ch[0]);
	printf(" %lld",o->v);
	show(o->ch[1]);
}
char LINE[7];
LL C;
LL Sz(Node* &o){return o?o->sz:0;}
LL Sum(Node* &o){return o?o->sum:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
Node* Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(ran()%(a->sz+b->sz)<=a->sz)
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
void Split(Node *o,Node* &a,Node* &b,LL loc)
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
void Insert(Node* &o,LL v,LL loc)
{
//	printf("ins %lld @ %lld:",v,loc);show(o);puts("");
	Node *a,*b;
//	puts("a");
	Split(o,a,b,loc);
//	puts("b");
	o=Merge(Merge(a,new Node(v)),b);
//	puts("c");
}
int main()
{
//	printf("%u %u %u\n",ran(),ran(),ran());
	srand(7122);
//	freopen("in.txt","r",stdin);
	LL kase=1;
	while(scanf("%lld",&C)==1&&C)
	{
		Node *root=NULL;
		printf("Scenario %lld:\n",kase++);
		while(C--)
		{
			scanf("%s",LINE);
			switch(LINE[0])
			{
				case'd':
				{
					LL i,j;scanf("%lld%lld",&i,&j);
					Node *a,*b,*c;
					Split(root,b,c,j+1);
					Split(b,a,b,i);
					root=Merge(a,c);
				}break;
				case'i':
				{
					LL loc,n,r,m,a,c;
					scanf("%lld%lld%lld%lld%lld%lld",&loc,&n,&r,&m,&a,&c);
					vector<LL>v;
					for(LL i=0,b;i<r;i++)
					{
						scanf("%lld",&b);
						v.push_back(b);
					}
					for(LL i=r;i<n;i++)
					{
						v.push_back((v[i-r]*a+c)%m);
						c=(v[i-r]*a+c)/m%m;
					}
					Node *ins=NULL;
					for(LL i=0;i<v.size();i++)ins=Merge(ins,new Node(v[i]));
					Node *n1,*n2;
					Split(root,n1,n2,loc);
					root=Merge(Merge(n1,ins),n2);
				}break;
				case's':
				{
					LL i,j;scanf("%lld%lld",&i,&j);
					Node *a,*b,*c;
					Split(root,b,c,j+1);
					Split(b,a,b,i);
					printf("%lld\n",Sum(b));
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
