#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	LL sum;
}BUFFER[12000000],*NEW;
Node *NewNode(const LL &_sum)
{
	assert(NEW<BUFFER+12000000);
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->sum=_sum;
	return NEW++;
}
Node *Build(const int l,const int r)
{
	Node *ans=NewNode(0LL);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Modify(Node *o,const int l,const int r,const int loc,const LL &val)
{
	Node *ans=NewNode((o->sum)+val);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Modify(o->ch[0],l,mid,loc,val),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Modify(o->ch[1],mid+1,r,loc,val);
	}
	return ans;
}
LL Query(Node *o,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return 0LL;
	if(bl<=l&&r<=br)return o->sum;
	const int mid=(l+r)/2;
	return Query(o->ch[0],l,mid,bl,br)+Query(o->ch[1],mid+1,r,bl,br);
}
int N,Q;
LL K;
pair<int,int>SEG[300000];
vector<int>ET[300000];
void BuildSEG(const int u,int &clock)
{
	SEG[u].first=clock;
	for(const int nxt:ET[u])BuildSEG(nxt,clock);
	SEG[u].second=clock++;
}
Node *TREE[300001];
int ANS[300002];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
//	freopen("s2.in","r",stdin);
	for(;scanf("%d%d%lld",&N,&Q,&K)==3;)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		NEW=BUFFER;
		for(int i=1,parent;i<N;i++)scanf("%d",&parent),ET[--parent].push_back(i);
		if(true){int clock=0;BuildSEG(0,clock);assert(clock==N);}
		TREE[0]=Build(0,N-1);
		for(int i=1,u;i<=Q;i++)
		{
			static LL x;
			scanf("%d%lld",&u,&x),u--;
			TREE[i]=Modify(TREE[i-1],0,N-1,SEG[u].second,x);
		}
		for(int i=0;i<=Q+1;i++)ANS[i]=0;
		for(int i=0;i<N;i++)
		{
			int l=0,r=Q+1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(Query(TREE[mid],0,N-1,SEG[i].first,SEG[i].second)<K)l=mid+1;
				else r=mid;
			}
			ANS[r]++;
		}
		for(int i=1;i<=Q;i++)ANS[i]+=ANS[i-1];
		for(int i=1;i<=Q;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
