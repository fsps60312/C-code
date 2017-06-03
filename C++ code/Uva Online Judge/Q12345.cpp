#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
//void assert(const bool valid){if(valid)return;for(;;)putchar('E');}
struct Query
{
	char type;
	int x,y;
};
struct Node
{
	Node *ch[2];
	int cnt,sz;
	Node(const int _cnt):ch{NULL,NULL},cnt(_cnt),sz(_cnt==0?0:1){}
	Node(Node *a,Node *b):ch{a,b},cnt(-1),sz((a->sz)+(b->sz)){}
};
Node *Build(const int l,const int r)
{
	if(l==r)return new Node(0);
	const int mid=(l+r)/2;
	return new Node(Build(l,mid),Build(mid+1,r));
}
Node *Modify(Node *o,const int l,const int r,const int loc,const int v)
{
	if(l==r){/*if(r!=loc)printf("(%d,%d)\n",r,loc);*/assert(r==loc);return new Node((o->cnt)+v);}
	const int mid=(l+r)/2;
	if(loc<=mid)return new Node(Modify(o->ch[0],l,mid,loc,v),o->ch[1]);
	else return new Node(o->ch[0],Modify(o->ch[1],mid+1,r,loc,v));
}
int N,M,GAP,A[50000];
Node *S[1357][1357];
vector<Query>QUERY;
void Initialize()
{
	int querycount;scanf("%d%d",&N,&querycount);
	GAP=min(N,(int)pow(N,2.0/3.0)+1);
	vector<int>v;
	for(int i=0;i<N;i++)scanf("%d",&A[i]),v.push_back(A[i]);
	QUERY.clear();
	while(querycount--)
	{
		static char type[2];
		static Query q;
		scanf("%s%d%d",type,&q.x,&q.y);
		q.type=type[0];
		if(q.type=='M')v.push_back(q.y);
		else assert(q.type=='Q');
		QUERY.push_back(q);
	}
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	M=v.size();
	for(int i=0;i<N;i++)A[i]=lower_bound(v.begin(),v.end(),A[i])-v.begin();
	for(auto &q:QUERY)
	{
		if(q.type=='M')q.y=lower_bound(v.begin(),v.end(),q.y)-v.begin();
		else assert(q.type=='Q'),q.y--;
	}
	v.clear(),vector<int>().swap(v);
}
//void Print(Node* &o,const int l,const int r)
//{
//	if(l==r){if(o->cnt)printf("[%d]=%d\n",r,o->cnt);return;}
//	const int mid=(l+r)/2;
//	Print(o->ch[0],l,mid),Print(o->ch[1],mid+1,r);
//}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	Initialize();
	Node *empty=Build(0,M-1);
	for(int l=0;l<=(N-1)/GAP;l++)
	{
		int now=GAP*l;
		Node *root=empty;
		for(int r=l;r<=(N-1)/GAP;r++)
		{
			while(now<N&&now/GAP==r)root=Modify(root,0,M-1,A[now++],1);
			S[l][r]=root;
		}
	}
	for(const Query &q:QUERY)
	{
//		printf("N=%d,M=%d %c %d %d\n",N,M,q.type,q.x,q.y);
		if(q.type=='M')
		{
			const int mid=q.x/GAP;
			for(int l=0;l<=mid;l++)for(int r=mid;r<=(N-1)/GAP;r++)
			{
				Node* &o=S[l][r];
				o=Modify(o,0,M-1,A[q.x],-1);
				o=Modify(o,0,M-1,q.y,1);
			}
			A[q.x]=q.y;
		}
		else if(q.type=='Q')
		{
			const int l=(q.x+GAP-1)/GAP,r=(q.y+1)/GAP-1;
			assert((l-1)*GAP<q.x&&q.x<=l*GAP);
			assert((r+1)*GAP-1<=q.y&&q.y<(r+2)*GAP-1);
			Node *o=(l<=r?S[l][r]:empty);
			for(int i=q.x;i<l*GAP;i++)o=Modify(o,0,M-1,A[i],1);
			for(int i=(r+1)*GAP;i<=q.y;i++)o=Modify(o,0,M-1,A[i],1);
//			Print(o,0,M-1);
			printf("%d\n",o->sz);
		}
		else assert(0);
	}
	return 0;
}
