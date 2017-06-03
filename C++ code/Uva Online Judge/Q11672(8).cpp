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
	LL sum,v,sz;
	int pri;
	Node(LL v):v(v),sum(v),sz(1LL),pri(rand()){ch[0]=ch[1]=NULL;}
};
char LINE[7];
LL C;
LL Sz(Node* &o){return o?o->sz:0LL;}
LL Sum(Node* &o){return o?o->sum:0LL;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
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
void Split(Node* &o,Node* &a,Node* &b,LL loc)
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
LL Query(Node* &o,LL l,LL r)
{
	if(!o)return 0LL;
	if(l<=0LL&&Sz(o)-1LL<=r)return Sum(o);
	if(r<0LL||l>=Sz(o))return 0LL;
	LL sz=Sz(o->ch[0]);
	return ((l<=sz&&sz<=r)?o->v:0LL)+Query(o->ch[0],l,r)+Query(o->ch[1],l-sz-1LL,r-sz-1LL);
}
int main()
{
	srand(7122);
//	freopen("in.txt","r",stdin);
	LL kase=1LL;
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
					for(LL i=0LL,b;i<r;i++)
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
					for(LL i=0LL;i<v.size();i++)ins=Merge(ins,new Node(v[i]));
					Node *n1,*n2;
					Split(root,n1,n2,loc);
					root=Merge(Merge(n1,ins),n2);
				}break;
				case's':
				{
					LL i,j;scanf("%lld%lld",&i,&j);
					printf("%lld\n",Query(root,i,j));
				}break;
				default:termin("can't handle %c\n",LINE[0]);
			}
		}
		puts("");
	}
	return 0;
}
