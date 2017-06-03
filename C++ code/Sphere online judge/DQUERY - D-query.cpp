#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
struct Node
{
	Node *ch[2];
	int sum;
	Node(const int _sum):ch{NULL,NULL},sum(_sum){}
};
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
Node *Modify(Node *o,const int l,const int r,const int loc,const int val)
{
	Node *ans=new Node((o->sum)+val);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Modify(o->ch[0],l,mid,loc,val),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Modify(o->ch[1],mid+1,r,loc,val);
	}
	return ans;
}
int Query(Node *o,const int l,const int r,const int loc)
{
	if(l>=loc)return o->sum;
	if(r<loc)return 0;
	const int mid=(l+r)/2;
	return Query(o->ch[0],l,mid,loc)+Query(o->ch[1],mid+1,r,loc);
}
int N,S[30001],PRE[30001];
Node *TREE[30001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d",&S[i]);
	map<int,int>pre;
	for(int i=1;i<=N;i++)
	{
		PRE[i]=pre[S[i]];
		pre[S[i]]=i;
	}
	TREE[0]=Build(0,N);
	for(int i=1;i<=N;i++)
	{
		TREE[i]=TREE[i-1];
		TREE[i]=Modify(TREE[i],0,N,PRE[i],1);
	}
	int querycount;scanf("%d",&querycount);
	for(int i,j;querycount--;)
	{
		scanf("%d%d",&i,&j);
		printf("%d\n",(j-i+1)-Query(TREE[j],0,N,i));
	}
	return 0;
}
