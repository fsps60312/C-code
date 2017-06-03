#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M;
struct Monkey
{
	int v,a,b;
	Monkey(){}
	Monkey(const int _v,const int _a,const int _b):v(_v),a(_a),b(_b){}
};
vector<Monkey>MONKEY;
vector<int>X;
void Discretize()
{
	X.clear();
	for(const Monkey &m:MONKEY)X.push_back(m.a),X.push_back(m.b);
	sort(X.begin(),X.end()),X.resize(unique(X.begin(),X.end())-X.begin());
	for(Monkey &m:MONKEY)m.a=lower_bound(X.begin(),X.end(),m.a)-X.begin(),m.b=lower_bound(X.begin(),X.end(),m.b)-X.begin();
}
vector<int>ANS[100],ET[302];
struct Edge
{
	int a,b,flow,limit;
	Edge(){}
	Edge(const int _a,const int _b,const int _flow,const int _limit):a(_a),b(_b),flow(_flow),limit(_limit){}
};
vector<Edge>EDGE;
int FLOOR[302];
bool Bfs(const int source,const int target)
{
	for(int i=0;i<N+(int)X.size()+2;i++)FLOOR[i]=INF;
	queue<int>q;q.push(source);FLOOR[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit||FLOOR[e.b]!=INF)continue;
			FLOOR[e.b]=FLOOR[u]+1;
			q.push(e.b);
		}
	}
	return FLOOR[target]!=INF;
}
int Dfs(const int u,const int target,int supply)
{
	if(!supply||u==target)return supply;
	int ans=0;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(FLOOR[u]+1==FLOOR[e.b]&&e.flow<e.limit)
		{
			const int flow=Dfs(e.b,target,min(supply,e.limit-e.flow));
			supply-=flow;
			ans+=flow;
			EDGE[ei].flow+=flow;
			EDGE[ei^1].flow-=flow;
			if(!supply)break;
		}
	}
	return ans;
}
int MaxFlow(const int source,const int target)
{
	int ans=0;
	while(Bfs(source,target))ans+=Dfs(source,target,INF);
	return ans;
}
void AddEdge(const int a,const int b,const int limit)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,0,limit));
	EDGE.push_back(Edge(b,a,limit,limit));
	ET[a].push_back(sz);
	ET[b].push_back(sz+1);
}
bool Solve()
{
	const int flow=MaxFlow(N+(int)X.size(),N+(int)X.size()+1);
	{int sum=0;for(int i=0;i<N;i++)sum+=MONKEY[i].v;assert(flow<=sum);if(flow<sum)return false;}
	int *cnt=new int[X.size()];
	for(int i=0;i<(int)X.size();i++)cnt[i]=0;
	for(int i=0;i<N;i++)
	{
		ANS[i].clear();
		for(const int ei:ET[i])
		{
			const Edge &e=EDGE[ei];
			const int lb=X[e.b-N],rb=X[e.b-N+1];
			for(int j=0;j<e.flow;j++,cnt[e.b-N]++)
			{
				ANS[i].push_back(lb+cnt[e.b-N]%(rb-lb));
			}
		}
		sort(ANS[i].begin(),ANS[i].end());
	}
	delete[]cnt;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		MONKEY.clear();
		EDGE.clear();
		for(int i=0;i<N+(int)X.size()+2;i++)ET[i].clear();
		for(int i=0,v,a,b;i<N;i++)
		{
			scanf("%d%d%d",&v,&a,&b);
			MONKEY.push_back(Monkey(v,a,b));
		}
		Discretize();
		for(int i=0;i<N;i++)AddEdge(N+(int)X.size(),i,MONKEY[i].v);
		for(int i=0;i<N;i++)
		{
			for(int j=MONKEY[i].a;j<MONKEY[i].b;j++)AddEdge(i,N+j,X[j+1]-X[j]);
		}
		for(int i=0;i+1<(int)X.size();i++)
		{
			AddEdge(N+i,N+(int)X.size()+1,M*(X[i+1]-X[i]));
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!Solve())puts("No");
		else
		{
			puts("Yes");
			for(int i=0;i<N;i++)
			{
				vector<pair<int,int> >ans;
				for(const int v:ANS[i])
				{
					if(ans.empty()||ans.back().second<v)ans.push_back(make_pair(v,v+1));
					else ans.back().second++;
				}
				printf("%d",(int)ans.size());
				for(const auto &p:ans)printf(" (%d,%d)",p.first,p.second);puts("");
			}
		}
	}
	return 0;
}
