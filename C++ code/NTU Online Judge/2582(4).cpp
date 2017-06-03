#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
struct SegTree
{
	int ROOT,ROOT_W;
	vector<int>MX;
	int N;
	void Maintain(const int id){MX[id]=max(MX[id*2],MX[id*2+1]);}
	void Build(const int id,const int l,const int r,const vector<int>&data)
	{
		if(l==r)
		{
			MX[id]=data[r];
			return;
		}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,data),Build(id*2+1,mid+1,r,data);
		Maintain(id);
	}
	void Build(const vector<int>&data)
	{
		N=(int)data.size();
		MX.resize(N*4);
		if(N)Build(1,0,N-1,data);
	}
	void PutDown(const int id)
	{
		getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
	}
	void LimitMX(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmin(MX[id],val);return;}
		const int mid=(l+r)/2;
		PutDown(id);
		LimitMX(id*2,l,mid,bl,br,val),LimitMX(id*2+1,mid+1,r,bl,br,val);
		Maintain(id);
	}
	void LimitMX(const int l,const int r,const int val)
	{
		assert(l>=-1);
		if(l==-1)assert(ROOT!=-1),getmin(ROOT_W,val);
		if(N)LimitMX(1,0,N-1,max(0,l),r,val);
	}
	int GetSum(const int id,const int l,const int r)
	{
		if(l==r)return MX[id];
		const int mid=(l+r)/2;
		PutDown(id);
		return GetSum(id*2,l,mid)+GetSum(id*2+1,mid+1,r);
	}
	int GetSum(){return (ROOT==-1?0:ROOT_W)+(N==0?0:GetSum(1,0,N-1));}
};
vector<SegTree>SEG;
struct Edge
{
	int A,B,COST;
	bool VIS;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST),VIS(false){}
};
//bool operator<(const Edge &a,const Edge &b){return a.COST<b.COST;}
int N,M,SZ[100000],DEPTH[100000];
pair<int,int>SEGID[100000];
vector<Edge>EDGE;
vector<int>ET[100000];
int BuildSZ(const int u,const int parent,const int depth)
{
	int &sz=SZ[u]=1;
	DEPTH[u]=depth;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)sz+=BuildSZ(nxt,u,depth+1);
	}
	return sz;
}
void Dfs(const int u,const int parent,vector<int>&now,vector<int>&us,const int root,const int root_w)
{
//	printf("u=%d\n",u);
	vector<pair<int,pair<int,int> > >chs;
	us.push_back(u);
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)chs.push_back(make_pair(SZ[nxt],make_pair(nxt,e.COST)));
	}
	if(chs.empty())
	{
		SegTree s;
		s.ROOT=root,s.ROOT_W=root_w;
		s.Build(now);
		const int id=(int)SEG.size();
		while(!us.empty())
		{
			const int v=us.back();us.pop_back();
			SEGID[v]=make_pair(id,(int)us.size()-1);
		}
		SEG.push_back(s);
		return;
	}
	sort(chs.begin(),chs.end());
	now.push_back(chs.back().second.second);
	Dfs(chs.back().second.first,u,now,us,root,root_w);
	chs.pop_back();
	for(const auto &p:chs)
	{
		now.clear(),us.clear();
		Dfs(p.second.first,u,now,us,u,p.second.second);
	}
}
void LimitMX(int a,int b,const int w)
{
	assert(a!=-1&&b!=-1);
	if(SEGID[a].first==SEGID[b].first)
	{
		if(DEPTH[a]>DEPTH[b])swap(a,b);
		SEG[SEGID[a].first].LimitMX(SEGID[a].second+1,SEGID[b].second,w);
		return;
	}
	if(DEPTH[a]-SEGID[a].second<DEPTH[b]-SEGID[b].second)swap(a,b);
	SEG[SEGID[a].first].LimitMX(-1,SEGID[a].second,w);
	const int nxta=SEG[SEGID[a].first].ROOT;
//	printf("%d+%d+2=%d\n",DEPTH[nxta],SEGID[a].second,DEPTH[a]);
	assert(DEPTH[nxta]+SEGID[a].second+2==DEPTH[a]);
	LimitMX(nxta,b,w);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		BuildSZ(0,-1,0);
		SEG.clear();
		{vector<int>now,us;Dfs(0,-1,now,us,-1,-1);}
		int ans=0;
		for(SegTree &s:SEG)ans+=s.GetSum();
		for(int i=N-1,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			LimitMX(a,b,c);
		}
		for(SegTree &s:SEG)ans-=s.GetSum();
		printf("%d\n",ans);
	}
	return 0;
}
