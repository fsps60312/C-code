#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	const LL val;
	Node(const LL &_val):val(_val){ch[0]=ch[1]=NULL;}
	Node(Node *o,const LL &dis):val((o->val)+dis){ch[0]=o->ch[0],ch[1]=o->ch[1];}
}*TREE[300001];
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Modify(Node *o,const int l,const int r,const int bl,const int br,const LL &val)
{
	if(r<bl||br<l)return o;
	if(bl<=l&&r<=br)return new Node(o,val);
	const int mid=(l+r)/2;
	Node *ans=new Node(o->val);
	ans->ch[0]=Modify(o->ch[0],l,mid,bl,br,val);
	ans->ch[1]=Modify(o->ch[1],mid+1,r,bl,br,val);
	return ans;
}
LL Query(Node *o,const int l,const int r,const int loc)
{
	if(!o)return 0;
	const int mid=(l+r)/2;
	if(loc<=mid)return (o->val)+Query(o->ch[0],l,mid,loc);
	else return (o->val)+Query(o->ch[1],mid+1,r,loc);
}
int N,M,K,OWNER[300000];
LL GOAL[300000];
vector<int>FARM[300000];
int Solve(const int l,const int r,const int p,const LL &goal)
{
	if(l==r)return r;
	const int mid=(l+r+1)/2;
	LL sum=0;
	for(int i=0;i<(int)FARM[p].size();i++)sum+=Query(TREE[mid],0,M-1,FARM[p][i]);
	if(sum>=goal)return Solve(l,mid-1,p,goal);
	else return Solve(mid,r,p,goal);
}
int main()
{
//	freopen("met8a.in","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)FARM[i].clear();
		for(int i=0;i<M;i++)scanf("%d",&OWNER[i]),FARM[--OWNER[i]].push_back(i);
		for(int i=0;i<N;i++)scanf("%lld",&GOAL[i]);
		scanf("%d",&K);
		TREE[0]=Build(0,M-1);
		for(int i=1,l,r,a;i<=K;i++)
		{
			scanf("%d%d%d",&l,&r,&a),l--,r--;
			if(l<=r)TREE[i]=Modify(TREE[i-1],0,M-1,l,r,a);
			else
			{
				TREE[i]=TREE[i-1];
				TREE[i]=Modify(TREE[i],0,M-1,l,M-1,a);
				TREE[i]=Modify(TREE[i],0,M-1,0,r,a);
			}
		}
		for(int i=0;i<N;i++)
		{
			const int ans=Solve(0,K,i,GOAL[i]);
			if(ans==K)puts("NIE");
			else printf("%d\n",ans+1);
		}
	}
	return 0;
}
