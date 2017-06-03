#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
struct Node
{
	Node *ch[2];
	int sz;
	Node(const int _v):ch{NULL,NULL},sz(_v){}
};
int Sz(Node* &o){return o?o->sz:0;}
Node *Maintain(Node* &o){o->sz=Sz(o->ch[0])+Sz(o->ch[1]);return o;}
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);
	if(l==r)return ans;
	const int mid=(l+r)/2;
	ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	return ans;
}
Node *Add(Node* &o,const int l,const int r,const int loc)
{
	if(l==r)return new Node((o->sz)+1);
	const int mid=(l+r)/2;
	Node *ans=new Node(0);
	if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
	else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	return Maintain(ans);
}
int Query(Node* &o1,Node* &o2,const int l,const int r,const int rank)
{
	if(l==r){assert(rank==0);return r;}
	const int mid=(l+r)/2;
	if(Sz(o2->ch[0])-Sz(o1->ch[0])<=rank)return Query(o1->ch[1],o2->ch[1],mid+1,r,rank-(Sz(o2->ch[0])-Sz(o1->ch[0])));
	return Query(o1->ch[0],o2->ch[0],l,mid,rank);
}
int S[1000001];
map<int,int>IDX;
vector<int>RI;
void ReIndex()
{
	RI.clear();
	int cnt=0;
	for(auto &it:IDX)it.second=cnt++,RI.push_back(it.first);
}
Node *ROOT[1000001];
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	static int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		IDX.clear();
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),IDX[S[i]]=-1;
		ReIndex();
		ROOT[0]=Build(0,(M=IDX.size())-1);
		for(int i=1;i<=N;i++)ROOT[i]=Add(ROOT[i-1],0,M-1,IDX[S[i]]);
		for(int bl,br,rank;querycount--;)
		{
			scanf("%d%d%d",&bl,&br,&rank);
			printf("%d\n",RI[Query(ROOT[bl-1],ROOT[br],0,M-1,rank-1)]);
		}
	}
	return 0;
}
