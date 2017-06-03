#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,N,M;
struct Edge
{
	int to;
	double l;
};
vector<Edge> VER[51];
double BEST[51];
int CNT[51],INQ[51];
bool negacycle(double d)
{
	queue<int> q;
	for(int i=1;i<=N;i++)
	{
		CNT[i]=0;
		BEST[i]=0;
		q.push(i);
		INQ[i]=1;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=0;
		CNT[u]++;
		if(CNT[u]>N)return true;
		for(int i=0;i<VER[u].size();i++)
		{
			Edge &e=VER[u][i];
			if(BEST[e.to]<BEST[u]+e.l-d)continue;
			BEST[e.to]=BEST[u]+e.l-d;
			if(INQ[e.to])continue;
			q.push(e.to);
			INQ[e.to]=1;
		}
	}
	return false;
}
double MIN,MAX;
double solve()
{
	while(MAX-MIN>1e-8)
	{
		double mid=(MAX+MIN)/2;
		if(negacycle(mid))MAX=mid;
		else MIN=mid;
	}
	return MAX;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
		{
			VER[i].clear();
		}
		MIN=10000000,MAX=0;
		for(int i=0;i<M;i++)
		{
			int a,b;double l;scanf("%d%d%lf",&a,&b,&l);
			VER[a].push_back((Edge){b,l});
			if(l>MAX)MAX=l;
			if(l<MIN)MIN=l;
		}
		printf("Case #%d: ",kase++);
		if(!negacycle(MAX+1))printf("No cycle found.\n");
		else printf("%.2lf\n",solve());
	}
	return 0;
}
