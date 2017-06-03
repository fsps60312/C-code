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
bool hasnegacycle(int sp,double d)
{
	queue<Edge> q;
	q.push((Edge){sp,0});
	while(!q.empty())
	{
		Edge e=q.front();q.pop();
		if(e.to<sp||e.l>BEST[e.to]+1e-8)continue;
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
bool isans(double d)
{
	for(int i=1;i<=N;i++)VIS[i]=CNT[i]=0,BEST[i]=510000000;
	for(int i=1;i<=N;i++)
	{
		if(VIS[i])continue;
		for(int j=i;j<=N;j++)CNT[j]=0,BEST[j]=510000000;
		if(hasnegacycle(i,d))return true;
		//if(i==1)for(int j=1;j<=N;j++)printf("BEST[%d]=%.3lf\n",j,BEST[j]);
	}
	return false;
}
double MIN,MAX;
double solve()
{
	while(MAX-MIN>1e-8)
	{
		double mid=(MAX+MIN)/2;
		//printf("\t%.10lf\t%.10lf\t%.10lf\n",MAX,MIN,MAX-MIN);
		if(isans(mid))MAX=mid;
		else MIN=mid;
	}
	return (MAX+MIN)/2;
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
		if(!isans(MAX+1))printf("No cycle found.\n");
		else printf("%.2lf\n",solve()+1e-7);
	}
	return 0;
}
