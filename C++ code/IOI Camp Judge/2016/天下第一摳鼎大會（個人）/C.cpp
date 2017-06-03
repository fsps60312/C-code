#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Node
{
	Node *ch[2];
	int sz;
	bool zero;
	Node(const int _sz):ch{NULL,NULL},sz(_sz),zero(_sz==0){}
}*ST[100001];
Node *Build(const int l,const int r)
{
	if(l==r)return new Node(0);
	const int mid=(l+r)/2;
	Node *ans=new Node(0);
	ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	return ans;
}
void Maintain(Node* &o)
{
	o->sz=o->ch[0]->sz+o->ch[1]->sz;
	o->zero=(o->ch[0]->zero||o->ch[1]->zero);
}
Node *Add(Node* &o,const int l,const int r,const int loc)
{
	if(l==r)return new Node((o->sz)+1);
	const int mid=(l+r)/2;
	Node *ans=new Node(0);
	if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
	else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	Maintain(ans);
	return ans;
}
int Query(Node* &lo,Node* &ro,const int l,const int r)
{
	if()return r+1;
	if(l==r)return lo->sz<ro->sz?r;
	const int mid=(l+r)/2;
	if(lo->ch[0]->sz<ro->ch[0]->sz)return Query(lo->ch[0],ro->ch[0],l,mid);
	else return Query(lo->ch[1],ro->ch[1],mid+1,r);
}
int N,M,S[100001];
vector<int>V;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d",&N,&querycount);
		V.clear();V.push_back(0);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),V.push_back(S[i]),V.push_back(S[i]+1);
		sort(V.begin(),V.end()),V.resize(unique(V.begin(),V.end())-V.begin());
		for(int i=1;i<=N;i++)S[i]=lower_bound(V.begin(),V.end(),S[i])-V.begin();
		M=V.size();
		ST[0]=Build(0,M-1);
		for(int i=1;i<=N;i++)ST[i]=Add(ST[i-1],0,M-1,S[i]),assert(ST[i]->sz==i);
		for(int l,r;querycount--;)
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",V[Query(ST[l-1],ST[r],0,M-1)]);
		}
	}
	assert(scanf("%d",&testcount)!=1);
	return 0;
}
