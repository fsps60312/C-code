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
	LL sum,h,v,sz;
	Node(LL v):h(rand()),v(v),sum(v),sz(1LL){ch[0]=ch[1]=NULL;}
};
void show(Node *o)
{
	if(!o)return;
	show(o->ch[0]);
	printf(" %lld",o->v);
	show(o->ch[1]);
}
char LINE[7];
LL C;
LL Sz(Node* &o){return o?o->sz:0LL;}
LL Sum(Node* &o){return o?o->sum:0LL;}
LL H(Node* &o){return o->h;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
void Rotate(Node* &o,LL chup)
{
	Node *ro=o;
	o=o->ch[chup];
	ro->ch[chup]=o->ch[chup^1LL];
	o->ch[chup^1LL]=ro;
	Maintain(ro),Maintain(o);
}
LL Rotate(Node* &o)
{
	LL h0=H(o->ch[0]),h1=H(o->ch[1]);
	if(o->h>=h0&&o->h>=h1)return -1;
	if(h0>h1){Rotate(o,0LL);return 0LL;}
	else{Rotate(o,1LL);return 1LL;}
}
void Splay(Node* &o,LL loc)
{
	if(loc<Sz(o->ch[0]))
	{
		Splay(o->ch[0],loc);
		Rotate(o,0LL);
	}
	else if(loc==Sz(o->ch[0]))return;
	else
	{
		Splay(o->ch[1],loc-Sz(o->ch[0])-1);
		Rotate(o,1LL);
	}
}
void Sink(Node* &o)
{
	LL d=Rotate(o);
	if(d==-1LL)return;
	Sink(o->ch[d^1LL]);
}
void Insert(Node* &o,LL v,LL loc)
{
	if(!o){o=new Node(v);return;}
	if(loc<=Sz(o->ch[0]))Insert(o->ch[0],v,loc);
	else Insert(o->ch[1],v,loc-Sz(o->ch[0])-1LL);
	Maintain(o);
	Rotate(o);
}
void Delete(Node* &o,LL i,LL j)
{
	Node *r,*l;
	if(j+1==Sz(o))l=o,r=NULL;
	else
	{
		Splay(o,j+1);
		r=o;
		l=r->ch[0];
		r->ch[0]=NULL;
	}
	Splay(l,i);
	l=l->ch[0];
	r->ch[0]=l;
	Sink(r);
	o=r;
}
LL Query(Node* &o,LL l,LL r)
{
	if(!o)return 0LL;
	if(l<=0&&Sz(o)-1<=r)return Sum(o);
	if(r<0||l>=Sz(o))return 0LL;
	LL sz=Sz(o->ch[0]),dis=sz+1LL,ans;
	if(l<=sz&&sz<=r)ans=o->v;
	else ans=0LL;
	return ans+Query(o->ch[0],l,r)+Query(o->ch[1],l-dis,r-dis);
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
					Delete(root,i,j);
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
					for(LL i=0;i<v.size();i++)Insert(root,v[i],loc++);
				}break;
				case's':
				{
					LL i,j;scanf("%lld%lld",&i,&j);
					printf("%lld\n",Query(root,i,j));
				}break;
				default:termin("can't handle %c\n",LINE[0]);
			}
//			printf("all:");show(root);puts("");
		}
		puts("");
	}
	return 0;
}
