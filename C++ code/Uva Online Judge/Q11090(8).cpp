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
int VIS[51];
double BEST[51];
int CNT[51];
bool negacycle(double d)
{
	queue<Edge> q;
	for(int i=1;i<=N;i++)
	{
		VIS[i]=CNT[i]=0;
		BEST[i]=510000000;
		q.push((Edge){i,0});
	}
	while(!q.empty())
	{
		Edge e=q.front();q.pop();
		if(e.l>BEST[e.to])continue;
		BEST[e.to]=e.l;
		VIS[e.to]++,CNT[e.to]++;
		if(CNT[e.to]>N)return true;
		for(int i=0;i<VER[e.to].size();i++)
		{
			Edge &te=VER[e.to][i];
			q.push((Edge){te.to,e.l+(te.l-d)});
		}
	}
	return false;
}
double MIN,MAX;
double solve()
{
	while(MAX-MIN>1e-3)
	{
		double mid=(MAX+MIN)/2;
		//printf("\t%.10lf\t%.10lf\t%.10lf\n",MAX,MIN,MAX-MIN);
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
