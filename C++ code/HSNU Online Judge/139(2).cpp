#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,M;
struct Edge
{
	int to;
	LL cost;
	Edge(){}
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
};
vector<Edge>ET[500];
LL Solve()
{
	static LL dist[500];
	static int cnt[500];
	static bool inq[500];
	for(int i=0;i<N;i++)dist[i]=INF,cnt[i]=0,inq[i]=false;
	queue<int>q;
	dist[0]=0LL;
	q.push(0),inq[0]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		inq[u]=false;
		for(const Edge &e:ET[u])if(dist[u]+e.cost<dist[e.to])
		{
			dist[e.to]=dist[u]+e.cost;
			if(cnt[e.to]++>N)return INF;
			if(!inq[e.to])q.push(e.to),inq[e.to]=true;
		}
	}
	return dist[N-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;
		static LL c;
		scanf("%d%d%lld",&a,&b,&c),a--,b--;
		assert(a>=0&&a<N),assert(b>=0&&b<N),assert(c>=-10000LL&&c<=10000LL);
		ET[a].push_back(Edge(b,c));
	}
	const LL result=Solve();
	if(result==INF)puts("QAQ");
	else printf("%lld\n",result);
	return 0;
}
