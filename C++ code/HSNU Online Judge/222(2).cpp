#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int N;
LL S[250000],DP[250000];
struct Node
{
	Node *ch[2];
	LL cnt,sum;
	int sz,v;
	Node(const int &_v,const int &_cnt):ch{NULL,NULL},sz(1),v(_v),cnt(_cnt),sum(_cnt){}
}*NODE[250000];
int Sz(Node* &o){return o?o->sz:0;}
LL Sum(Node* &o){return o?o->sum:0LL;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]),o->sum=(Sum(o->ch[0])+o->cnt+Sum(o->ch[1]))%MOD;}
void Rotate(Node* &o,const int &cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Insert(Node* &o,const int &v,const LL &cnt)
{
	if(!o){o=new Node(v,cnt);return;}
	if(v<o->v)Insert(o->ch[0],v,cnt);
	else Insert(o->ch[1],v,cnt);
	Maintain(o),Rotate(o);
}
LL Query(Node* &o,const int &v)
{
	if(!o)return 0LL;
	if(v<o->v)return Query(o->ch[0],v);
	else return (Sum(o->ch[0])+o->cnt+Query(o->ch[1],v))%MOD;
}
LL Solve()
{
	for(int i=0;i<N;i++)NODE[i]=NULL;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=ans,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(DP[mid]<S[i])l=mid+1;
			else r=mid;
		}
		DP[l]=S[i];
		LL cnt;
		if(l==0)cnt=1LL;
		else cnt=Query(NODE[l-1],S[i]-1);
//		printf("%d:ans=%d,l=%d,cnt=%lld\n",i,ans,l,cnt);
		Insert(NODE[l],S[i],cnt);
		if(l==ans)ans++;
	}
	return Sum(NODE[ans-1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		printf("%lld\n",Solve());
	}
	return 0;
}
