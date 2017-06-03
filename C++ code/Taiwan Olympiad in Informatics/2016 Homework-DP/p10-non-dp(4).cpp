#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#include<cmath>
using namespace std;
const double EPS=1e-9,INF=1e100;
void getmax(double &a,const double b){if(b>a)a=b;}
int N,M;
double W[2501];
set<int>ET[2501];
void Merge(const int a,const int b)
{
	W[b]+=W[a],W[a]=-1e100;
	for(const int nxt:ET[a])if(nxt!=b)
	{
		ET[b].insert(nxt);
		ET[nxt].erase(a),ET[nxt].insert(b);
	}
	ET[b].erase(a);
	ET[a].clear();
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
struct Pq
{
	int a,b;
	double dist;
	Pq(){}
	Pq(const int _a,const int _b,const double _dist):a(_a),b(_b),dist(_dist){}
	bool operator<(const Pq &p)const{return dist>p.dist;}
};
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
	for(int i=0;i<N;i++)Build(i,DIST[i],PRE[i]);
	double ans=0.0;
	for(int i=0;i<N;i++)getmax(ans,W[i]);
	set<Pq>pq;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(i!=j)pq.insert(Pq(i,j,DIST[i][j]));
	while(!pq.empty())
	{
		const auto p=*pq.begin();pq.erase(pq.begin());
		if(p.dist<0.0)break;
		if(DIST[p.a][p.b]!=p.dist)continue;
		getmax(ans,p.dist);
		vector<int>ps;
		for(int cur=p.b;cur!=p.a;cur=PRE[p.a][cur])ps.push_back(cur);
		ps.push_back(p.a);
		reverse(ps.begin(),ps.end());
		for(int i=1;i<(int)ps.size();i++)Merge(ps[i],ps[0]);
		Build(ps[0],DIST[ps[0]],PRE[ps[0]]);
	
	}
	printf("%.9f\n",ans);
	return 0;
}
