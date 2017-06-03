#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct Item
{
	int V,W,L,R;
	Item(){}
	Item(const int _V,const int _W,const int _L):V(_V),W(_W),L(_L),R(35000){}
};
int N,K;
LL ANS[30000];
void Solve(const int l,const int r,const vector<Item>&items,const vector<pair<int,int> >&queries,const LL *pre_dp)
{
	LL *dp=new LL[K+1];
	for(int i=0;i<=K;i++)dp[i]=pre_dp[i];
	const int mid=(l+r)/2;
	vector<Item>left_items,rigt_items;
	for(const Item &item:items)
	{
		if(item.L<=l&&r<=item.R)
		{
			for(int i=K-item.W;i>=0;i--)getmax(dp[i+item.W],dp[i]+item.V);
		}
		else
		{
			if(item.L<=mid)left_items.push_back(item);
			if(mid+1<=item.R)rigt_items.push_back(item);
		}
	}
	if(l==r)
	{
		LL ans=0,p=1;
		for(int m=1;m<=K;m++,(p*=10000000+19)%=MOD)(ans+=dp[m]*p)%=MOD;
		for(const auto &q:queries)assert(q.first==r),ANS[q.second]=ans;
		return;
	}
	vector<pair<int,int> >left_queries,rigt_queries;
	for(const auto &q:queries)(q.first<=mid?left_queries:rigt_queries).push_back(q);
	Solve(l,mid,left_items,left_queries,dp);
	Solve(mid+1,r,rigt_items,rigt_queries,dp);
	delete[]dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		vector<Item>item;
		int tick=0;
		for(int i=0,v,w;i<N;i++)scanf("%d%d",&v,&w),item.push_back(Item(v,w,tick++));
		int querycount;scanf("%d",&querycount);
		vector<pair<int,int> >queries;
		int ans_length=0;
		for(int i=0,type;i<querycount;i++)
		{
			scanf("%d",&type);
			if(type==1)
			{
				int v,w;scanf("%d%d",&v,&w);
				item.push_back(Item(v,w,tick++));
			}
			else if(type==2)
			{
				int x;scanf("%d",&x),--x;
				item[x].R=(tick++)-1;
			}
			else if(type==3)
			{
				queries.push_back(make_pair(tick-1,ans_length++)); 
			}
			else assert(0);
		}
		LL *dp=new LL[K+1];
		for(int i=0;i<=K;i++)dp[i]=0;
		Solve(0,tick-1,item,queries,dp);
		delete[]dp;
		for(int i=0;i<ans_length;i++)printf("%lld\n",ANS[i]);
	}
	return 0;
}
