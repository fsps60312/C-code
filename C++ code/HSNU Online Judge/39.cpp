#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
struct Node
{
	Node *l,*r;
	LL sz;
	Node():l(NULL),r(NULL),sz(1LL){}
}*ROOT;
LL Sz(Node* &o){return o?o->sz:0LL;}
void Maintain(Node* &o){o->sz=Sz(o->l)+Sz(o->r);}
void Add(Node* &o,LL l,LL r,LL v)
{
	if(!o)o=new Node();
	if(l==r)return;
	LL mid=(l+r)/2LL;
	if(v<=mid)Add(o->l,l,mid);
	else Add(o->r,mid+1LL,r);
	Maintain(o);
}
LL L,R;
LL Query(Node* &o,LL l,LL r)
{
	if(!o||l>R||r<L)return 0LL;
	if(L<=l&&r<=R)return o->sz;
	LL mid=(l+r)/2LL;
	return Query(o->l,l,mid)+Query(o->r,mid+1LL,r);
}
vector<LL>A,B;
int main()
{
	while(scanf("%lld%lld",&K,&M)==2)
	{
		ROOT=NULL;
		A.clear(),B.clear();
		for(LL i=0LL,a;i<K;i++){scanf("%lld",&a);A.push_back(a);}
		for(LL i=0LL,b;i<K;i++){scanf("%lld",&b);B.push_back(b);}
		LL ans=0LL;
		for(LL i=0LL;i<K;i++)
		{
			//all k: A[k]>A[i]&&B[k]<B[i]
			//all k: A[k]<A[i]&&B[k]>B[i]
			L=,R=;
			ans+=Query(ROOT,-M,M);
			Add(ROOT,-M,M,A[i]-B[i]);
		}
	}
	return 0;
}
