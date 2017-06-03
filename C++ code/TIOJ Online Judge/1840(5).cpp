#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct QueryType{int type,l,r,v;};
int Node_COUNTER=0;
struct Node
{
	Node *ch[2];
	int sz;
	Node(const int _sz):ch{NULL,NULL},sz(_sz){Node_COUNTER++;}
	~Node(){Node_COUNTER--;}
};
void Assign(Node* &o,Node *ch)
{
	o=ch;
}
void Maintain(Node* &o){(o->sz)=(o->ch[0]->sz)+(o->ch[1]->sz);}
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);
	if(l==r)return ans;
	const int mid=(l+r)/2;
	Assign(ans->ch[0],Build(l,mid));
	Assign(ans->ch[1],Build(mid+1,r));
	Maintain(ans);
	return ans;
}
Node *Modify(Node* &o,const int l,const int r,const int loc,const int v)
{
	if(l==r)return new Node((o->sz)+v);
	const int mid=(l+r)/2;
	Node *ans=new Node(0);
	if(loc<=mid)Assign(ans->ch[0],Modify(o->ch[0],l,mid,loc,v)),Assign(ans->ch[1],o->ch[1]);
	else Assign(ans->ch[0],o->ch[0]),Assign(ans->ch[1],Modify(o->ch[1],mid+1,r,loc,v));
	Maintain(ans);
	return ans;
}
int GetCh0Sum(const vector<Node*>&s){int ans=0;for(const Node *o:s)ans+=(o->ch[0]->sz);return ans;}
void MoveToCh(vector<Node*>&s,const int d){for(Node* &o:s)o=o->ch[d];}
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
		Node *empty=::Build(0,M-1);
		for(int i=1;i<=N;i++)Assign(DATA[i],empty);
	}
	void Add(int i,const int v,const int dis)
	{
		while(i<=N)
		{
			Assign(DATA[i],Modify(DATA[i],0,M-1,v,dis));
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
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;scanf("%d%d",&N,&querycount);
		VALS.clear();
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),VALS.push_back(S[i]);
		QUERY.clear();
		for(QueryType q;querycount--;)
		{
			scanf("%d",&q.type);
			switch(q.type)
			{
				case 1:scanf("%d%d%d",&q.l,&q.r,&q.v);break;
				case 2:scanf("%d%d",&q.l,&q.v),VALS.push_back(q.v);break;
				case 3:scanf("%d%d",&q.l,&q.v);break;
				default:assert(0);break;
			}
			QUERY.push_back(q);
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
//			printf("counter=%d\n",Node_COUNTER);
		}
	}
	return 0;
}
