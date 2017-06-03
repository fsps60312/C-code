#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
struct Worm
{
	LL carbon,endure;
}WORM[300000];
bool CmpEndure(const Worm &a,const Worm &b){return a.endure<b.endure;}
struct Node
{
	Node *ch[2];
	int sz;
	LL v,sum;
	Node(const LL &_v):v(_v),sum(_v),sz(1),ch{NULL,NULL}{}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
LL Sum(Node* &o){return o?o->sum:0LL;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
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
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void Insert(Node* &o,const LL &v)
{
	if(!o){o=new Node(v);return;}
	if(v<o->v)Insert(o->ch[0],v);
	else Insert(o->ch[1],v);
	Maintain(o),Rotate(o);
}
void Query(Node* &o,LL &cnt,LL &sum,const LL &average)
{
	if(!o)return;
	if(sum+Sum(o->ch[0])>average*(cnt+Sz(o->ch[0])))Query(o->ch[0],cnt,sum,average);
	else
	{
		sum+=Sum(o->ch[0]),cnt+=Sz(o->ch[0]);
		if(sum+o->v<=average*(cnt+1LL))
		{
			sum+=o->v,cnt++;
			Query(o->ch[1],cnt,sum,average);
		}
		else return;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Worm &w=WORM[i];
		scanf("%lld%lld",&w.carbon,&w.endure);
	}
	sort(WORM,WORM+N,CmpEndure);
	LL ans=0LL;
	for(int i=N-1;i>=0;i--)
	{
		const Worm &w=WORM[i];
		Insert(ROOT,w.carbon);
		LL cnt=0LL,sum=0LL;
		Query(ROOT,cnt,sum,w.endure);
		ans=max(ans,cnt);
	}
	printf("%lld\n",ans);
	return 0;
}
