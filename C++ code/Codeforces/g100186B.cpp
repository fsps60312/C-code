#include<cstdio>
#include<cassert>
#include<map>
#include<set>
#include<cmath>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=20160220;
	seed*=0xdefaced,seed+=84033;
	return seed+=seed>>20; 
}
struct Node
{
	Node *ch[2];
	const int val;
	unsigned int sz;
	Node(const int _val):ch{NULL,NULL},val(_val),sz(1){}
}*S[300000];
unsigned int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%((a->sz)+(b->sz))<(a->sz))
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
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<(o->val))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc);
		Maintain(a);
	}
}
Node *Split(Node* &o,const int l,const int r)
{
	Node *a,*b,*c;
	Split(o,b,c,r);
	Split(b,a,b,l-1);
	o=Merge(a,c);
	return b;
}
bool Contains(Node *o,const int loc)
{
	if(!o)return false;
	if((o->val)==loc)return true;
	if(loc<(o->val))return Contains(o->ch[0],loc);
	else return Contains(o->ch[1],loc);
}
void RemoveTag(Node* &o,map<int,int>&look_up)
{
	if(!o)return;
	const auto it=look_up.find(o->val);
	assert(it!=look_up.end());
	look_up.erase(it);
	for(int d=0;d<2;d++)RemoveTag(o->ch[d],look_up);
}
void AddTag(Node* &o,map<int,int>&look_up,const int tag)
{
	if(!o)return;
	assert(look_up.find(o->val)==look_up.end());
	look_up[o->val]=tag;
	for(int d=0;d<2;d++)AddTag(o->ch[d],look_up,tag);
}
set<int>UNREAD,LARGE;
map<int,int>LOOK_UP;
int N;
unsigned int SQ;
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int querycount;scanf("%d%d",&N,&querycount);
	SQ=sqrt(N)+1;
	UNREAD.clear();
	for(int i=1;i<=N;i++)UNREAD.insert(i);
	LARGE.clear(),LOOK_UP.clear();
	long long ans=0LL;
	for(int l,r,i=0;i<querycount;i++)
	{
		scanf("%d%d",&l,&r);
		if(UNREAD.find(l)!=UNREAD.end())S[i]=NULL;
		else
		{
			const auto it=LOOK_UP.find(l);
			if(it!=LOOK_UP.end())
			{
				S[i]=Split(S[it->second],l,r);
				RemoveTag(S[i],LOOK_UP);
			}
			else
			{
				bool found=false;
				for(const int v:LARGE)if(Contains(S[v],l))
				{
					S[i]=Split(S[v],l,r);
					if(Sz(S[v])<=SQ)LARGE.erase(v),AddTag(S[v],LOOK_UP,v);
					found=true;
					break;
				}
				assert(found);
			}
		}
		auto it=UNREAD.lower_bound(l);
		while(it!=UNREAD.end()&&(*it)<=r)
		{
			Node *a,*b;
			Split(S[i],a,b,*it);
			S[i]=Merge(a,Merge(new Node(*it),b));
			UNREAD.erase(it++);
		}
		ans+=Sz(S[i]);
		if(Sz(S[i])<=SQ)AddTag(S[i],LOOK_UP,i);
		else LARGE.insert(i);
	}
	printf("%I64d\n",ans);
	return 0;
}