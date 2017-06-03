#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct QueryType
{
	unsigned short type,l,r;
	int v;
	QueryType(){}
	QueryType(const int _t,const int _l,const int _r,const int _v):type(_t),l(_l),r(_r),v(_v){}
};
struct Node
{
	Node *ch[2];
	unsigned short sz;
	Node(){}
	Node(const int _sz):ch{NULL,NULL},sz(_sz){}
}Node_POOL[20000000];
int Node_PTR=0;
Node *NewNode(const int _sz){assert(Node_PTR<20000000);Node_POOL[Node_PTR]=Node(_sz);return &Node_POOL[Node_PTR++];}
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){(o->sz)=Sz(o->ch[0])+Sz(o->ch[1]);}
Node *Ch(Node *o,const int d){return o?o->ch[d]:NULL;}
void Modify(Node* &o,const int l,const int r,const int loc,const int v)
{
	if(!o)o=NewNode(0);
	if(l==r)o->sz+=v;
	else
	{
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(o->ch[0],l,mid,loc,v);
		else Modify(o->ch[1],mid+1,r,loc,v);
		Maintain(o);
	}
}
int GetCh0Sum(const vector<Node*>&s)
{
	int ans=0;
	for(Node *o:s)ans+=(o?Sz(o->ch[0]):0);
	return ans;
}
void MoveToCh(vector<Node*>&s,const int d){for(Node* &o:s)o=Ch(o,d);}
int QueryLoc(vector<Node*>&sp,vector<Node*>&sm,const int l,const int r,const int rank)
{
	if(l==r)return r;
	const int sum=GetCh0Sum(sp)-GetCh0Sum(sm);
	const int mid=(l+r)/2;
	if(rank<=sum)
	{
		MoveToCh(sp,0),MoveToCh(sm,0);
		return QueryLoc(sp,sm,l,mid,rank);
	}
	else
	{
		MoveToCh(sp,1),MoveToCh(sm,1);
		return QueryLoc(sp,sm,mid+1,r,rank-sum);
	}
}
int N,M,S[50001];
struct Bit
{
	Node *DATA[50001];
	Bit(){for(int i=0;i<=50000;i++)DATA[i]=NULL;}
	void Build()
	{
		for(int i=1;i<=N;i++)DATA[i]=NULL;
	}
	void Add(int i,const int v,const int dis)
	{
		while(i<=N)
		{
			Modify(DATA[i],0,M-1,v,dis);
			i+=(i&(-i));
		}
	}
	void Query(int i,vector<Node*>&ans){while(i)ans.push_back(DATA[i]),i-=(i&(-i));}
	int Query(const int bl,const int br,const int rank)
	{
		vector<Node*>sp,sm;
		Query(br,sp),Query(bl-1,sm);
		const int ans=QueryLoc(sp,sm,0,M-1,rank);
		sp.clear(),vector<Node*>().swap(sp);
		sm.clear(),vector<Node*>().swap(sm);
		return ans;
	}
}BIT=Bit();
vector<QueryType>QUERY;
vector<int>VALS;
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;scanf("%d%d",&N,&querycount);
		Node_PTR=0;
		VALS.clear();
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),VALS.push_back(S[i]);
		QUERY.clear();
		for(int type,l,r,v;querycount--;)
		{
			scanf("%d",&type);
			switch(type)
			{
				case 1:scanf("%d%d%d",&l,&r,&v);break;
				case 2:scanf("%d%d",&l,&v),VALS.push_back(v);break;
				case 3:scanf("%d%d",&l,&v);break;
				default:assert(0);break;
			}
			QUERY.push_back(QueryType(type,l,r,v));
		}
		if(true)
		{
			vector<int>&v=VALS;
			sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
			M=v.size();
			for(int i=1;i<=N;i++)S[i]=lower_bound(v.begin(),v.end(),S[i])-v.begin();
			for(QueryType &q:QUERY)if(q.type==2)q.v=lower_bound(v.begin(),v.end(),q.v)-v.begin();
		}
		BIT.Build();
		for(int i=1;i<=N;i++)BIT.Add(i,S[i],1);
		for(const QueryType &q:QUERY)
		{
			switch(q.type)
			{
				case 1:printf("%d\n",VALS[BIT.Query(q.l,q.r,q.v)]);break;
				case 2:BIT.Add(q.l,S[q.l],-1),BIT.Add(q.l,S[q.l]=q.v,1);break;
				case 3:puts("7122");break;
				default:assert(0);break;
			}
		}
	}
	return 0;
}
