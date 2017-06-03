#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
const double LIMIT=51.0*10000000;
const double eps=1e-9;
int T,N,M;
int dcmp(double x)
{
	if((x>=0?x:-x)<eps) return 0;
	return x<0?-1:1;
}
struct Edge
{
	int to;
	double l;
	bool operator<(Edge a)const{return dcmp(l-a.l)==1;}
};
vector<Edge> VER[51];
int VIS[51];
bool nocycle()
{
	for(int i=1;i<=N;i++)VIS[i]=0;
	for(int i=1;i<=N;i++)
	{
		if(VIS[i])continue;
		queue<int> q;
		q.push(i);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			if(u<i)continue;
			if(VIS[u])return false;
			VIS[u]=1;
			for(int ti=0;ti<VER[u].size();ti++)
			{
				q.push(VER[u][ti].to);
			}
		}
	}
	return true;
}
double BEST[51];
int CNT[51];
bool hasnegacycle(int sp,double d)
{
	priority_queue<Edge> pq;
	pq.push((Edge){sp,0});
	while(!pq.empty())
	{
		Edge e=pq.top();pq.pop();
		if(e.to<sp||dcmp(e.l-BEST[e.to])==1)continue;
		BEST[e.to]=e.l;
		VIS[e.to]++,CNT[e.to]++;
		if(CNT[e.to]>=N)return true;
		for(int i=0;i<VER[e.to].size();i++)
		{
			Edge te=VER[e.to][i];
			pq.push((Edge){te.to,e.l+te.l-d});
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
		for(int j=i;j<=N;j++)if(VIS[j])CNT[j]=0,BEST[j]=510000000;
		if(hasnegacycle(i,d))return true;
		//if(i==1)for(int j=1;j<=N;j++)printf("BEST[%d]=%.3lf\n",j,BEST[j]);
	}
	return false;
}
double MIN,MAX;
double solve()
{
	while(MAX-MIN>1e-4)
	{
		double mid=(MAX+MIN)/2;
		//printf("\t%.3lf\n",mid);
		if(isans(mid))MAX=mid;
		else MIN=mid;
	}
	return (MAX+MIN)/2;
}
int main()
{
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
		if(nocycle())printf("No cycle found.\n");
		else printf("%.2lf\n",solve());
	}
	return 0;
}
