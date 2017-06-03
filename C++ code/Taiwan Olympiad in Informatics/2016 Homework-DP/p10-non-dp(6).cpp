#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#include<cmath>
using namespace std;
const double EPS=1e-9;
struct Edge
{
	int a,b;
	double dist;
	Edge(){}
	Edge(const int _a,const int _b,const double _dist):a(_a),b(_b),dist(_dist){}
	bool operator<(const Edge &e)const{return dist>e.dist;}
};
void getmax(double &a,const double b){if(b>a)a=b;}
int N,M;
double W[2501];
set<int>ET[2501];
struct DisjointSets
{
	int S[2501];
	void Clear(const vector<int>&s)
	{
		for(const int i:s)S[i]=i;
	}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b;return true;}
}DJ;
void Merge(const int a,const int b)
{
	W[b]+=W[a],W[a]=-1e100;
	for(const int nxt:ET[a])if(nxt!=b)
	{
		ET[b].insert(nxt);
		ET[nxt].erase(a),ET[nxt].insert(b);
	}
	ET[b].erase(a);
}
void Build(const int root,double *dist,int *pre)
{
	static bool inq[2501];
	for(int i=0;i<N;i++)dist[i]=-1e100,inq[i]=false;
	queue<int>q;q.push(root),inq[root]=true;
	dist[root]=W[root];
	while(!q.empty())
	{
		const int u=q.front();q.pop();inq[u]=false;
		if(W[u]>0.0)continue;
		for(const int nxt:ET[u])if(dist[u]+W[nxt]>dist[nxt])
		{
			pre[nxt]=u;
			dist[nxt]=dist[u]+W[nxt];
			if(!inq[nxt])q.push(nxt),inq[nxt]=true;
		}
	}
}
double DIST[2501][2501];
int PRE[2501][2501];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0,v;i<N;i++)scanf("%d%lf",&v,&W[i]);
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),--a,--b;
		ET[a].insert(b),ET[b].insert(a);
	}
	for(int changed=true;changed;)
	{
		changed=false;
		for(int u=0;u<N;u++)if(W[u]!=-1e100)
		{
			for(const int nxt:ET[u])if(W[nxt]!=-1e100)
			{
				if(W[u]>=0.0&&W[nxt]>=0.0)
				{
//					--cnt;
					changed=true;
					Merge(nxt,u);
					break;
				}
			}
		}
	}
	int cnt=0;
	for(int i=0;i<N;i++)if(W[i]>0.0)cnt++;
	printf("cnt=%d\n",cnt);
	vector<int>ps;
	for(int i=0;i<N;i++)if(W[i]>0.0)ps.push_back(i),Build(i,DIST[i],PRE[i]);
	const int n=ps.size();
	printf("n=%d\n",n);
	double ans=0.0;
	for(int s=0;s<(1<<n);s++)
	{
		if(s%1000==0)printf("s=%d\n",s);
		vector<int>pss;
		for(int i=0;i<n;i++)if(s&(1<<i))pss.push_back(ps[i]);
		vector<Edge>edges;
		for(int i=0;i<(int)pss.size();i++)
		{
			for(int j=0;j<(int)pss.size();j++)if(i!=j)
			{
				edges.push_back(Edge(pss[i],pss[j],DIST[pss[i]][pss[j]]-W[pss[i]]-W[pss[j]]));
			}
		}
		DJ.Clear(pss);
		sort(edges.begin(),edges.end());
		double ta=0.0;
		for(int i=0;i<(int)edges.size();i++)
		{
			const Edge &e=edges[i];
			if(DJ.Merge(e.a,e.b))ta+=e.dist;
		}
		for(int i=0;i<(int)pss.size();i++)ta+=W[pss[i]];
		getmax(ans,ta);
	}
	printf("%.9f\n",ans);
	return 0;
}
