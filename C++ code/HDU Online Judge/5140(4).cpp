#include<stdio.h>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void bssert(bool valid){if(valid)return;int a=0,b=0;a/=b;}
typedef long long LL;
const LL INF=9223372036854775807LL;
const int MAX_DEP=200;
int Rand()
{
	static unsigned int seed=20160221;
	seed*=0xdefaced,seed+=185243;
	return (seed+=seed>>20)&0x7fffffff;
}
struct Staff
{
	int salary,level,age;
	inline bool operator<(const Staff &s)const{return level<s.level;}
}STAFF[100000];
struct Node
{
	Node *ch[2];
	int key;
	LL val;
	int sz;
	LL sum;
}BUFFER[2000000],*NEW,*S[100001];
inline Node *NewNode(const int _key,const LL &_val)
{
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->key=_key,NEW->val=_val;
	NEW->sz=1,NEW->sum=_val;
	return NEW++;
}
inline Node *NewNode(Node *o)
{
	NEW->ch[0]=o->ch[0],NEW->ch[1]=o->ch[1];
	NEW->key=o->key,NEW->val=o->val;
	NEW->sz=o->sz,NEW->sum=o->sum;
	return NEW++;
}
inline int Sz(Node *o){return o?o->sz:0;}
inline LL Sum(Node *o){return o?o->sum:0;}
inline void Maintain(Node *o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+(o->val)+Sum(o->ch[1]);
}
inline Node *Merge(Node *_a,Node *_b)
{
	static Node *as[MAX_DEP],*bs[MAX_DEP],*return_value;
	static int states[MAX_DEP],dep;dep=0;
	as[0]=_a,bs[0]=_b,states[0]=0;
	while(dep>=0)
	{
		bssert(dep+1<MAX_DEP);
		Node *&a=as[dep],*&b=bs[dep];
		int &state=states[dep];
		dep--;
		if(state==0)
		{
			if(a)a=NewNode(a);
			if(b)b=NewNode(b);
			if(!a||!b){return_value=(a?a:b);continue;}
			if(Rand()%(a->sz+b->sz)<(a->sz))
			{
				dep++,state=1,dep++;
				as[dep]=a->ch[1],bs[dep]=b,states[dep]=0;
			}
			else
			{
				dep++,state=2,dep++;
				as[dep]=a,bs[dep]=b->ch[0],states[dep]=0;
			}
		}
		else if(state==1)
		{
			a->ch[1]=return_value;
			Maintain(a);
			return_value=a;
		}
		else
		{
			b->ch[0]=return_value;
			Maintain(b);
			return_value=b;
		}
	}
	return return_value;
}
inline void Split(Node *_o,Node* &_a,Node* &_b,const int key)
{
	static Node *os[MAX_DEP];
	static Node **as[MAX_DEP],**bs[MAX_DEP];
	static int states[MAX_DEP],dep;dep=0;
	os[0]=_o,as[0]=&_a,bs[0]=&_b,states[0]=0;
	while(dep>=0)
	{
		bssert(dep+1<MAX_DEP);
		Node *&o=os[dep],*&a=*as[dep],*&b=*bs[dep];
		int &state=states[dep];
		dep--;
		if(state==0)
		{
			if(o)o=NewNode(o);
			if(!o){a=b=NULL;continue;}
			if((o->key)<=key)
			{
				a=o;
				dep++,state=1,dep++;
				os[dep]=a->ch[1],as[dep]=&a->ch[1],bs[dep]=&b,states[dep]=0;
			}
			else
			{
				b=o;
				dep++,state=2,dep++;
				os[dep]=b->ch[0],as[dep]=&a,bs[dep]=&b->ch[0],states[dep]=0;
			}
		}
		else if(state==1)Maintain(a);
		else Maintain(b);
	}
}
inline LL QuerySum(Node* &o,const int l,const int r)
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
//	bssert(0);return 0;
//	freopen("in.txt","r",stdin);
	RANGE.reserve(100001);
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
