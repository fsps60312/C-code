#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
static int Node_COUNTER=0;
struct Node
{
	Node *ch[2];
	int sum,ref;
	Node(const int _sum):ch{NULL,NULL},sum(_sum),ref(0){Node_COUNTER++;}
	~Node(){Node_COUNTER--;}
};
void Assign(Node* &o,Node *val)
{
	if(o)
	{
		if(!--(o->ref))
		{
			for(int d=0;d<2;d++)if(o->ch[d])Assign(o->ch[d],NULL);
			delete o;
		}
		o=NULL;
	}
	if(val)o=val,val->ref++;
}
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);//local value, lose reference after leave scope
	if(l<r)
	{
		const int mid=(l+r)/2;
		Assign(ans->ch[0],Build(l,mid));
		Assign(ans->ch[1],Build(mid+1,r));
	}
	return ans;
}
Node *Modify(Node *o,const int l,const int r,const int loc,const int val)
{
	Node *ans=new Node((o->sum)+val);//local value, lose reference after leave scope
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)
		{
			Assign(ans->ch[0],Modify(o->ch[0],l,mid,loc,val));
			Assign(ans->ch[1],o->ch[1]);
		}
		else
		{
			Assign(ans->ch[0],o->ch[0]);
			Assign(ans->ch[1],Modify(o->ch[1],mid+1,r,loc,val));
		}
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
	Node *data[50001];
	int n,m;
	Bit(){for(int i=0;i<=50000;i++)data[i]=NULL;}
	void Clear(const int _n,const int _m)
	{
		n=_n,m=_m;
		Assign(data[0],Build(0,m-1));
		for(int i=1;i<=n;i++)Assign(data[i],data[i-1]);
	}
	void Add(int i,const int val,const int coda)
	{
		for(;i<=n;i+=(i&(-i)))Assign(data[i],Modify(data[i],0,m-1,val,coda));
	}
	void Query(int i,vector<Node*>&ans)
	{
		for(;i;i-=(i&(-i)))ans.push_back(data[i]);
	}
	int Query(const int l,const int r,const int rank)
	{
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
	freopen("in.txt","r",stdin);
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
			}
			else printf("%d\n",RANGE[BIT.Query(q.l,q.r,q.v)]);
		}
		printf("Node_COUNTER=%d\n",Node_COUNTER);
		for(int i=0;i<=50000;i++)Assign(BIT.data[i],NULL);
		printf("Node_COUNTER=%d\n",Node_COUNTER);//should be zero
		assert(Node_COUNTER==0);
	}
	return 0;
}
