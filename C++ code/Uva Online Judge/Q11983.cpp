#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
const LL BOUND=1000000000LL;
int T,N,K;
struct Node2D
{
	Node2D *l,*r;
	vector<LL>cnt;
	int tag;
	Node2D(const LL _v):l(NULL),r(NULL),tag(0){for(int i=0;i<=K;i++)cnt.push_back(0LL);cnt[0]=_v;}
};
void Add(Node2D* &o,const int v)
{
	assert(v);
	vector<LL>&cnt=o->cnt;
	for(int i=0;i<v;i++)cnt[K]+=cnt[K-i],cnt[K-i]=0LL;
	for(int i=K-v;i>=0;i--)cnt[i+v]+=cnt[i],cnt[i]=0LL;
	o->tag+=v;
	if(o->tag>K)o->tag=K;
}
void PutDown(Node2D* &o,const LL l,const LL r,const LL mid)
{
	if(!o->l)o->l=new Node2D(mid-l+1LL);
	if(!o->r)o->r=new Node2D(r-mid);
	if(!o->tag)return;
	Add(o->l,o->tag),Add(o->r,o->tag);
	o->tag=0;
}
void Maintain(Node2D* &o)
{
	assert(o&&o->l&&o->r);
	assert(o->tag==0);
	for(int i=0;i<=K;i++)o->cnt[i]=(o->l->cnt[i])+(o->r->cnt[i]);
}
struct Node1D
{
	Node1D *l,*r;
	Node2D *ch;
	Node1D(const LL _v):l(NULL),r(NULL),ch(new Node2D(_v)){}
};
void Add2D(Node2D* &o,const int l,const int r,const int y1,const int y2)
{
	assert(o&&"Add2D");
	if(r<y1||y2<l)return;
	if(y1<=l&&r<=y2){Add(o,1);return;}
	const int mid=(l+r)/2;
	PutDown(o,l,r,mid);
	Add2D(o->l,l,mid,y1,y2),Add2D(o->r,mid+1,r,y1,y2);
	Maintain(o); 
}
void Add1D(Node1D* &o,const int l,const int r,const int x1,const int x2,const int y1,const int y2)
{
	if(!o)o=new Node1D();
	
	const int mid=(l+r)/2;
	
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&K);
	}
	return 0;
}
