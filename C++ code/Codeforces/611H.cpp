#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
const int INF=2147483647;
int DigitCount(int n)
{
	int ans=0;
	for(;n;n/=10,++ans);
	return ans;
}
struct DisjointSets
{
	int S[7];
	void Clear(const int N){for(int i=1;i<=N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b;return true;}
};
struct NetworkFlow
{
	struct Edge
	{
		int A,B,FLOW,LIMIT;
		Edge(){}
		Edge(const int _A,const int _B,const int _FLOW,const int _LIMIT):A(_A),B(_B),FLOW(_FLOW),LIMIT(_LIMIT){}
	};
	vector<vector<int> >ET;
	vector<Edge>EDGE;
	void AddEdge(const int a,const int b,const int limit)
	{
		assert(limit>=0);
		const int sz=(int)EDGE.size();
		EDGE.push_back(Edge(a,b,0,limit));
		EDGE.push_back(Edge(b,a,limit,limit));
		ET[a].push_back(sz);
		ET[b].push_back(sz+1);
	}
	int N,TARGET,LEVEL[23],CUR[23];
	int Dfs(const int u,int supply)
	{
		if(supply==0||u==TARGET)return supply;
		int ans=0;
		for(int &i=CUR[u];i<(int)ET[u].size();i++)
		{
			const int ei=ET[u][i];
			const Edge &e=EDGE[ei];
			if(e.FLOW==e.LIMIT||LEVEL[e.B]!=LEVEL[u]+1)continue;
			const int flow=Dfs(e.B,min(supply,e.LIMIT-e.FLOW));
			EDGE[ei].FLOW+=flow;
			EDGE[ei^1].FLOW-=flow;
			supply-=flow;
			ans+=flow;
			if(!supply)break;
		}
		return ans;
	}
	int SOURCE;
	bool Bfs()
	{
		for(int i=0;i<N;i++)LEVEL[i]=INF,CUR[i]=0;
		queue<int>q;q.push(SOURCE);LEVEL[SOURCE]=0;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const int ei:ET[u])
			{
				const Edge &e=EDGE[ei];
				if(e.FLOW==e.LIMIT)continue;
				if(LEVEL[u]+1<LEVEL[e.B])
				{
					LEVEL[e.B]=LEVEL[u]+1;
					q.push(e.B);
				}
			}
		}
		return LEVEL[TARGET]!=INF;
	}
	int GOAL;
	void Initialize(const int D,const int CNT[7][7],const vector<pair<int,int> >&edges,const vector<int>VS[7])
	{
		N=D+D*(D-1)/2+2;
		SOURCE=D+D*(D-1)/2+1,TARGET=D+D*(D-1)/2;
		ET.clear(),ET.resize(D+D*(D-1)/2+2);
		EDGE.clear();
		static vector<int>ei[7];
		for(int i=1;i<=D;i++)ei[i].clear();
		int goal=0;
		for(int i=0;i<(int)edges.size();i++)
		{
			const int a=edges[i].first,b=edges[i].second;
			ei[a].push_back(i);
			ei[b].push_back(i);
			AddEdge(D+i,D+D*(D-1)/2,CNT[a][b]);
			goal+=CNT[a][b];
		}
		GOAL=goal;
		for(int i=1;i<=D;i++)
		{
			AddEdge(D+D*(D-1)/2+1,i-1,(int)VS[i].size()-1);
			goal-=(int)VS[i].size()-1;
			for(const int nxt:ei[i])AddEdge(i-1,D+nxt,INF);
		}
		assert(goal==0);
	}
	bool ReachFullFlow()
	{
		while(Bfs())GOAL-=Dfs(SOURCE,INF);
		assert(GOAL>=0);
		return GOAL==0;
	}
	void ExtractAnswer(const int D,vector<pair<int,int> >&ans,const vector<pair<int,int> >&edges,const vector<int>VS[7])
	{
		for(int i=0;i<D;i++)
		{
			int cur=1;
			for(const int ei:ET[i])
			{
				const Edge &e=EDGE[ei];
				const auto &p=edges[e.B-D];
				const int nxt=(i+1==p.first?p.second:p.first);
				for(int j=0;j<e.FLOW;j++)
				{
					assert(cur<(int)VS[i+1].size());
					ans.push_back(make_pair(VS[i+1][cur++],VS[nxt][0]));
				}
			}
			assert(cur==(int)VS[i+1].size());
		}
	}
};
DisjointSets DJ;
NetworkFlow NF;
int N,D,E,ORI[7][7],CNT[7][7];
vector<int>VS[7];
bool IsTree(const vector<pair<int,int> >&edges,const int s)
{
	DJ.Clear(D);
	int cnt=0;
//	puts("IsTree");
	for(int i=0;i<E;i++)if(s&(1<<i))
	{
//		printf("%d %d\n",edges[i].first,edges[i].second);
		if(!DJ.Merge(edges[i].first,edges[i].second))return false;
		else ++cnt;
	}
	return cnt==D-1;
}
bool Valid(const vector<pair<int,int> >&edges,const int s,vector<pair<int,int> >&ans)
{
	for(int i=0;i<E;i++)if(s&(1<<i))
	{
		const int a=edges[i].first,b=edges[i].second;
		if(--CNT[a][b]<0)return false;
		ans.push_back(make_pair(VS[a][0],VS[b][0]));
	}
	NF.Initialize(D,CNT,edges,VS);
	if(!NF.ReachFullFlow())return false;
	NF.ExtractAnswer(D,ans,edges,VS);
//	assert(0);
	return true;
}
vector<pair<int,int> >Solve()
{
	vector<pair<int,int> >ans;
	for(int i=1;i<=D;i++)
	{
		if(CNT[i][i]>=(int)VS[i].size())return vector<pair<int,int> >();
		while(CNT[i][i]--)ans.push_back(make_pair(VS[i].front(),VS[i].back())),VS[i].pop_back();
	}
	if(D==1)
	{
		if((int)VS[1].size()>1)return vector<pair<int,int> >();
		return ans;
	}
	E=D*(D-1)/2;
	vector<pair<int,int> >edges;
//	printf("D=%d\n",D);
	for(int i=1;i<=D;i++)for(int j=i+1;j<=D;j++)edges.push_back(make_pair(i,j));
	assert((int)edges.size()==E);
	for(int s=0;s<(1<<E);++s)if(IsTree(edges,s))
	{
		for(int i=1;i<=D;i++)for(int j=i+1;j<=D;j++)CNT[i][j]=0;
		for(int i=1;i<=D;i++)for(int j=1;j<=D;j++)CNT[min(i,j)][max(i,j)]+=ORI[i][j];
		const auto &pre_ans_sz=ans.size();
		if(Valid(edges,s,ans))return ans;
		while(ans.size()>pre_ans_sz)ans.pop_back();
	}
//	puts("pass");
	return vector<pair<int,int> >();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=6;i++)VS[i].clear();
		for(int i=1;i<=N;i++)VS[DigitCount(i)].push_back(i);
		D=DigitCount(N);
		for(int i=1;i<=D;i++)for(int j=1;j<=D;j++)CNT[i][j]=ORI[i][j]=0;
		for(int i=0;i<N-1;i++)
		{
			static char as[7],bs[7];
			scanf("%s%s",as,bs);
			int a=-1,b=-1;
			while(as[++a]);while(bs[++b]);
			++ORI[a][b];
			if(a>b)swap(a,b);
			++CNT[a][b];
		}
		const vector<pair<int,int> >&ans=Solve();
		if(ans.empty())puts("-1");
		else
		{
			assert((int)ans.size()==N-1);
			for(const auto &p:ans)
			{
				int a=p.first,b=p.second;
				if(!ORI[DigitCount(a)][DigitCount(b)])swap(a,b);
//				assert((ORI[DigitCount(a)][DigitCount(b)]--)>0);
				printf("%d %d\n",a,b);
			}
		}
	}
	return 0;
}
