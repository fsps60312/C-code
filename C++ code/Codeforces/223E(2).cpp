#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL &_x,const LL &_y):x(_x),y(_y){} 
	Point operator-(const Point &a)const{return Point(x-a.x,y-a.y);}
	int Quantarium()const
	{
		if(y>=0LL&&x>0LL)return 1;
		if(y>0LL&&x<=0LL)return 2;
		if(y<=0LL&&x<0LL)return 3;
		if(y<0LL&&x>=0LL)return 4;
		assert(!(x==0LL&&y==0LL));
		assert(0);return -1;
	}
	bool operator<(const Point &b)const
	{
		const int qa=Quantarium(),qb=b.Quantarium();
		if(qa!=qb)return qa<qb;
		switch(qa)
		{
			case 1:return y*b.x<b.y*x;//y/x<b.y/b.x
			case 2:return y*(-b.x)>b.y*(-x);//y/-x>b.y/-b.x
			case 3:return (-y)*(-b.x)<(-b.y)*(-x);//-y/-x<-b.y/-b.x
			case 4:return (-y)*b.x>(-b.y)*x;//-y/x>-b.y/b.x
			default:assert(0);return true;
		}
	}
}P[100001];
struct Edge
{
	const int a,b;
	int flow;
	Edge():a(),b(){}
	Edge(const int _a,const int _b,const int _flow):a(_a),b(_b),flow(_flow){}
	bool operator<(const Edge &e)const
	{
		assert(a==e.a);
		return P[b]-P[a]<P[e.b]-P[a];
	}
};
vector<Edge>EDGE;
vector<int>ET[100001],SUM[100000];
map<int,int>IDX[100000];
int Dfs(const int u,bool *vis)
{
	if(vis[u])return 0;
	vis[u]=true;
	int ans=1;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int flow=Dfs(e.b,vis);
		ans+=flow;
		EDGE[ei].flow+=flow,EDGE[ei^1].flow-=flow;
	}
	return ans;
}
int N,M;
void CreateFlow()
{
	static bool vis[100001];
	for(int i=0;i<=N;i++)vis[i]=false;
	assert(Dfs(N,vis)==N+1);
}
void AddEdge(const int a,const int b)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,0));
	ET[a].push_back(sz);
}
int GetSum(const int a,const int o,const int b,const bool type)
{
	const vector<int>&sum=SUM[o];
	const auto ita=IDX[o].find(a),itb=IDX[o].find(b);
	assert(ita!=IDX[o].end()&&itb!=IDX[o].end());
	const int ia=(type?itb:ita)->second;
	const int ib=(type?ita:itb)->second;
	assert(ia!=ib);
	if(ia<ib)return sum[ib-1]-sum[ia];
	else return sum[(int)sum.size()-1]-(sum[ia]-(ib?sum[ib-1]:0));
}
bool CmpEdgeIdx(const int a,const int b){if(a==b)return false;return EDGE[a]<EDGE[b];}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			AddEdge(a,b),AddEdge(b,a);
		}
		for(int i=0;i<N;i++)scanf("%I64d%I64d",&P[i].x,&P[i].y);
		if(true)
		{
			LL mn=INF;
			int left=-1;
			for(int i=0;i<N;i++)if(P[i].x<mn)mn=P[i].x,left=i;
			assert(left!=-1);
			AddEdge(left,N),AddEdge(N,left);
			P[N].x=-1e9-1,P[N].y=P[left].y;
		}
		CreateFlow();
		for(int i=0;i<N;i++)
		{
			sort(ET[i].begin(),ET[i].end(),CmpEdgeIdx);
			IDX[i].clear();
			for(int j=0;j<(int)ET[i].size();j++)IDX[i][EDGE[ET[i][j]].b]=j;
			SUM[i].clear();
			int sum=0;
			for(const int ei:ET[i])SUM[i].push_back(sum+=EDGE[ei].flow);
			assert(IDX[i].size()==ET[i].size()&&SUM[i].size()==ET[i].size());
		}
		int querycount;scanf("%d",&querycount);
		for(int k;querycount--;)
		{
			scanf("%d",&k);
			vector<int>a;
			for(int i=0,v;i<k;i++)scanf("%d",&v),a.push_back(--v);
			assert(k==(int)a.size()&&k>=3);
			int ans1=0,ans2=0;
			for(int i=0;i<k;i++)
			{
				ans1+=GetSum(a[i],a[(i+1)%k],a[(i+2)%k],false);
				ans2+=GetSum(a[i],a[(i+1)%k],a[(i+2)%k],true);
			}
			printf("%d\n",-min(ans1,ans2));
		}
	}
	return 0;
}
