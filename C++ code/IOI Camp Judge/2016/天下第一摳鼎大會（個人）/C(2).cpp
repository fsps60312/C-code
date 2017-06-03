#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Node
{
	Node *ch[2];
	int mn;
	Node(const int _mn):ch{NULL,NULL},mn(_mn){}
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
	o->mn=min(o->ch[0]->mn,o->ch[1]->mn);
}
Node *Add(Node* &o,const int l,const int r,const int loc,const int v)
{
	if(l==r)return new Node(v);
	const int mid=(l+r)/2;
	Node *ans=new Node(0);
	if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc,v),ans->ch[1]=o->ch[1];
	else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc,v);
	Maintain(ans);
	return ans;
}
int Query(Node* &o,const int l,const int r,const int bound)
{
	assert(o->mn<bound);
	if(l==r)return r;
	const int mid=(l+r)/2;
	if(o->ch[0]->mn<bound)return Query(o->ch[0],l,mid,bound);
	else return Query(o->ch[1],mid+1,r,bound);
}
int N,M,S[100001];
vector<int>V;
int main()
{
//	freopen("in.txt","r",stdin);
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
		for(int i=1;i<=N;i++)ST[i]=Add(ST[i-1],0,M-1,S[i],i);
		for(int l,r;querycount--;)
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",V[Query(ST[r],0,M-1,l)]);
		}
		static int cnt=0;
		if(cnt++>10)assert(0);
	}
	assert(scanf("%d",&testcount)!=1);
	return 0;
}
