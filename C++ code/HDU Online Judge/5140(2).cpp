#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
typedef long long LL;
int Rand()
{
	static unsigned int seed=20160221;
	seed*=0xdefaced,seed+=180755;
	return (seed+=seed>>20)&0x7fffffff;
}
struct Staff
{
	int salary,level,age;
	bool operator<(const Staff &s)const{return level<s.level;}
}STAFF[100000];
struct Node
{
	Node *ch[2];
	int key,val;
	int sz;
	LL sum;
}BUFFER[2000000],*NEW,*S[100001];
Node *NewNode(const int _key,const int _val)
{
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->key=_key,NEW->val=_val;
	NEW->sz=1,NEW->sum=_val;
	return NEW++;
}
Node *NewNode(Node *o)
{
	NEW->ch[0]=o->ch[0],NEW->ch[1]=o->ch[1];
	NEW->key=o->key,NEW->val=o->val;
	NEW->sz=o->sz,NEW->sum=o->sum;
	return NEW++;
}
int Sz(Node *o){return o?o->sz:0;}
LL Sum(Node *o){return o?o->sum:0;}
void Maintain(Node *o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+(LL)(o->val)+Sum(o->ch[1]);
}
Node *Merge(Node *a,Node *b)
{
	if(a)a=NewNode(a);
	if(b)b=NewNode(b);
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<(a->sz))
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
void Split(Node *o,Node* &a,Node* &b,const int key)
{
	if(o)o=NewNode(o);
	if(!o){a=b=NULL;return;}
	if((o->key)<=key)
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,key);
		Maintain(a);
	}
	else
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],key);
		Maintain(b);
	}
}
LL QuerySum(Node* &o,const int l,const int r)
{
	Node *a,*b,*c;
	Split(o,b,c,r);
	Split(b,a,b,l-1);
	const LL ans=Sum(b);
	o=Merge(a,Merge(b,c));
	return ans;
}
int N,M;
vector<LL>RANGE;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		NEW=BUFFER;
		for(int i=0;i<N;i++)
		{
			Staff &s=STAFF[i];
			scanf("%d%d%d",&s.salary,&s.level,&s.age);
		}
		sort(STAFF,STAFF+N);
		S[0]=NULL;
		RANGE.clear(),RANGE.push_back(-INF);
		for(int i=1,j=0;j<N;i++)
		{
			const int level=STAFF[j].level;
//			printf("level=%d\n",level);
			RANGE.push_back(level);
			S[i]=S[i-1];
			for(;j<N&&STAFF[j].level==level;j++)
			{
				const Staff &s=STAFF[j];
				Node *a,*b;
				Split(S[i],a,b,s.age);
				S[i]=Merge(a,Merge(NewNode(s.age,s.salary),b));
			}
		}
		int querycount;scanf("%d",&querycount);
		const vector<LL>&v=RANGE;
		for(LL l1,l2,a1,a2,k=0LL;querycount--;)
		{
			scanf("%lld%lld%lld%lld",&l1,&l2,&a1,&a2);
			l1+=k,l2-=k,a1+=k,a2-=k;
			if(l1>l2)swap(l1,l2);
			if(a1>a2)swap(a1,a2);
			const int l=lower_bound(v.begin(),v.end(),l1)-v.begin();
			const int r=upper_bound(v.begin(),v.end(),l2)-v.begin()-1;
			printf("%lld\n",k=QuerySum(S[r],a1,a2)-QuerySum(S[l-1],a1,a2));
		}
	}
	return 0;
}
