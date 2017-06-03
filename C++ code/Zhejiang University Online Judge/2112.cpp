#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
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
void MoveToCh(vector<Node*>&s,const int d){for(Node* &v:s)v=v->ch[d];}
int GetLeftSum(vector<Node*>&s){int a=0;for(Node *v:s)a+=(v->ch[0]?v->ch[0]->sum:0);return a;}
int Query(vector<Node*>&los,vector<Node*>&ros,const int l,const int r,const int rank)
{
	if(l==r)return r;
	const int dis=GetLeftSum(ros)-GetLeftSum(los);
	const int mid=(l+r)/2;
	if(rank<=dis)
	{
		MoveToCh(los,0),MoveToCh(ros,0);
		return Query(los,ros,l,mid,rank);
	}
	else
	{
		MoveToCh(los,1),MoveToCh(ros,1);
		return Query(los,ros,mid+1,r,rank-dis);
	}
}
struct Bit
{
	Node *data[500001];
	int n,m;
	void Clear(const int _n,const int _m)
	{
		n=_n,m=_m;
		data[0]=Build(0,m-1);
		for(int i=1;i<=n;i++)data[i]=data[i-1];
	}
	void Add(int i,const int val,const int coda)
	{
		for(;i<=n;i+=(i&(-i)))data[i]=Modify(data[i],0,m-1,val,coda);
	}
	void Query(int i,vector<Node*>&ans)
	{
		for(;i;i-=(i&(-i)))ans.push_back(data[i]);
	}
	int Query(const int l,const int r,const int rank)
	{
//		printf("l=%d,r=%d,rank=%d\n",l,r,rank);
		vector<Node*>los,ros;
		Query(l-1,los),Query(r,ros);
		return ::Query(los,ros,0,m-1,rank);
	}
}BIT;
struct QueryType{int l,r,v;};
vector<QueryType>QUERY;
int N,M,S[50001];
vector<int>RANGE;
void Discretize()
{
	vector<int>&v=RANGE;v.clear();
	for(int i=1;i<=N;i++)v.push_back(S[i]);
	for(const QueryType &q:QUERY)if(q.l==-1)v.push_back(q.v);
	sort(v.begin(),v.end()),v.resize(M=unique(v.begin(),v.end())-v.begin());
	for(int i=1;i<=N;i++)S[i]=lower_bound(v.begin(),v.end(),S[i])-v.begin();
	for(QueryType &q:QUERY)if(q.l==-1)q.v=lower_bound(v.begin(),v.end(),q.v)-v.begin();
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;scanf("%d%d",&N,&querycount);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		QUERY.clear();
		for(int i=0;i<querycount;i++)
		{
			static QueryType q;
			static char type[2];
			scanf("%s",type);
			if(type[0]=='Q')scanf("%d%d%d",&q.l,&q.r,&q.v);
			else if(type[0]=='C')q.l=-1,scanf("%d%d",&q.r,&q.v);
			else assert(0);
			QUERY.push_back(q);
		}
		Discretize();
		BIT.Clear(N,M);
		for(int i=1;i<=N;i++)BIT.Add(i,S[i],1);
		for(const QueryType &q:QUERY)
		{
			if(q.l==-1)
			{
				BIT.Add(q.r,S[q.r],-1);
				BIT.Add(q.r,S[q.r]=q.v,1);
//				for(int i=0;i<=N;i++)assert(BIT.data[i]->sum==(i&(-i)));
			}
			else printf("%d\n",RANGE[BIT.Query(q.l,q.r,q.v)]);
		}
	}
	return 0;
}
