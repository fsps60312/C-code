#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct QueryType
{
	int l,r,id;
	QueryType(){}
	QueryType(const int _l,const int _r,const int _id):l(_l),r(_r),id(_id){}
	bool operator<(const QueryType &q)const{return r<q.r;}
};
int MN[800001];
void Build(const int id,const int l,const int r)
{
	MN[id]=0;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Maintain(const int id){MN[id]=min(MN[id*2],MN[id*2+1]);}
void Add(const int id,const int l,const int r,const int loc,const int v)
{
	if(l==r){MN[id]=v;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Add(id*2,l,mid,loc,v);
	else Add(id*2+1,mid+1,r,loc,v);
	Maintain(id);
}
int Query(const int id,const int l,const int r,const int bound)
{
	assert(MN[id]<bound);
	if(l==r)return r;
	const int mid=(l+r)/2;
	if(MN[id*2]<bound)return Query(id*2,l,mid,bound);
	else return Query(id*2+1,mid+1,r,bound);
}
int N,M,S[100001],ANS[100000];
vector<int>V;
vector<QueryType>Q;
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
		Build(1,0,M-1);
		Q.clear();
		for(int l,r,i=0;i<querycount;i++)
		{
			scanf("%d%d",&l,&r);
			Q.push_back(QueryType(l,r,i));
		}
		sort(Q.begin(),Q.end());
		int now=0;
		for(const QueryType &q:Q)
		{
			while(now<q.r)now++,Add(1,0,M-1,S[now],now);
			assert(now==q.r);
			ANS[q.id]=Query(1,0,M-1,q.l);
		}
		for(int i=0;i<querycount;i++)printf("%d\n",ANS[i]);
	}
	assert(scanf("%d",&testcount)!=1);
	return 0;
}
