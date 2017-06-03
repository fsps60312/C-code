#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>void getmax(T &a,const T &b){if(b>a)a=b;}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
int N,M;
vector<bool>D;
int HEAD[300000],NEXT[299999*2],VAL[299999*2],NSZ;
void AddEdge(const int a,const int b)
{
	VAL[NSZ]=b;
	NEXT[NSZ]=HEAD[a];
	HEAD[a]=NSZ;
	++NSZ;
}
namespace WeightPoint
{
	void DfsWeightPoint(const int u,const int parent,const bool *vis,int *sums,int *mxszs,int *nodes,int &m)
	{
		int sum=1,mxsz=0;
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(VAL[cur]!=parent&&!vis[VAL[cur]])
		{
			DfsWeightPoint(VAL[cur],u,vis,sums,mxszs,nodes,m);
			sum+=sums[m-1],getmax(mxsz,sums[m-1]);
		}
		sums[m]=sum,mxszs[m]=mxsz,nodes[m]=u;++m;
	}
	int FindWeightPoint(const int u,const bool *vis)
	{
		static int sums[300000],mxszs[300000],nodes[300000];
		int n=0;
		DfsWeightPoint(u,-1,vis,sums,mxszs,nodes,n);
		assert(sums[n-1]==n);
		for(int i=0;i<n;i++)getmax(mxszs[i],n-sums[i]);
		pair<int,int>ans=make_pair(INF,-1);
		for(int i=0;i<n;i++)getmin(ans,make_pair(mxszs[i],nodes[i]));
		assert(ans.second!=-1);
		return ans.second;
	}
	int PARENT[300000];
	void BuildTree(const int u,const int parent,bool *vis)
	{
		const int root=FindWeightPoint(u,vis);
		PARENT[root]=parent;
		vis[root]=true;
		for(int cur=HEAD[root];cur!=-1;cur=NEXT[cur])if(!vis[VAL[cur]])BuildTree(VAL[cur],root,vis);
	}
	int DIST[300000];
	void BuildTree()
	{
		static bool vis[300000];
		for(int i=0;i<N;i++)vis[i]=false;
		BuildTree(0,-1,vis);
	}
}
namespace Depth
{
	int DEPTH[600000],M;
	struct SparseTable
	{
		int S[20][600000];
		int BIT[600000];
		void Build()
		{
			for(int i=0;i<M;i++)S[0][i]=DEPTH[i];
			for(int bit=1;(1<<bit)<=M;bit++)
			{
				for(int i=0;i+(1<<bit)<=M;i++)S[bit][i]=min(S[bit-1][i],S[bit-1][i+(1<<(bit-1))]);
			}
			for(int i=0,ans=0;i<M;i++)
			{
				for(;(1<<(ans+1))<=i+1;ans++);
				BIT[i]=ans;
			}
		}
		int Query(const int a,const int b)
		{
			const int bit=BIT[b-a];
			return min(S[bit][a],S[bit][b-(1<<bit)+1]);
		}
	}ST;
	int LOCS[300000],PARENT[300000];
	void DfsDepth(const int u,const int parent,const int depth)
	{
		DEPTH[LOCS[u]=M++]=depth;
		PARENT[u]=parent;
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(VAL[cur]!=parent)
		{
			DfsDepth(VAL[cur],u,depth+1);
			DEPTH[LOCS[u]=M++]=depth;
		}
	}
	void BuildDepth()
	{
		M=0;
		DfsDepth(0,-1,0);
		ST.Build();
	}
	int QueryLength(const int va,const int vb)
	{
		int a=LOCS[va],b=LOCS[vb];
		return DEPTH[a]+DEPTH[b]-2*ST.Query(min(a,b),max(a,b));
	}
	bool CmpDepth(const int a,const int b){return DEPTH[LOCS[a]]>DEPTH[LOCS[b]];}
}
int QueryMinDist(const int _a)
{
	int ans=INF;
	for(int a=_a;a!=-1;a=WeightPoint::PARENT[a])if(WeightPoint::DIST[a]!=INF)getmin(ans,WeightPoint::DIST[a]+Depth::QueryLength(a,_a));
	return ans;
}
void UpdateMinDist(const int _a)
{
	for(int a=_a;a!=-1;a=WeightPoint::PARENT[a])getmin(WeightPoint::DIST[a],Depth::QueryLength(a,_a));
}
bool Solve(const int len)
{
	for(int i=0;i<N;i++)WeightPoint::DIST[i]=INF;
	static int order[300000];
	int m=0;
	for(int i=0;i<N;i++)if(D[i])order[m++]=i;
	sort(order,order+m,Depth::CmpDepth);
	int ans=0;
	for(int _i=0;_i<m;_i++)
	{
		const int u=order[_i];
//		printf("u=%d,mindist=%d\n",u+1,QueryMinDist(u));
		if(QueryMinDist(u)<=len)continue;
		if(++ans>M)return false;
		int cur=u;
		for(int i=0;i<len&&Depth::PARENT[cur]!=-1;i++,cur=Depth::PARENT[cur]);
		UpdateMinDist(cur);
//		++ans;
//		printf("set on %d\n",cur+1);
	}
//	printf("len=%d,ans=%d\n",len,ans);
//	return ans<=M;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		D.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),D.push_back(v?true:false);
		for(int i=0;i<N;i++)HEAD[i]=-1;
		NSZ=0;
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			AddEdge(a,b),AddEdge(b,a);
		}
		WeightPoint::BuildTree();
		Depth::BuildDepth();
		int l=0,r=N-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		printf("%d\n",r);
	}
	return 0;
}
