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
	bool operator<(Edge a)const{return l>a.l;}
};
vector<Edge> VER[51];
int VIS[51];
double solve(int sp)
{
	for(int i=sp;i<=N;i++)VIS[sp]=0;
	priority_queue<Edge> pq;
	for(int i=0;i<VER[sp].size();i++)pq.push(VER[sp][i]);
	while(!pq.empty())
	{
		Edge e=pq.top();pq.pop();
		if(e.to<sp||VIS[e.to])continue;
		if(e.to==sp)return e.l;
		VIS[e.to]=1;
		for(int i=0;i<VER[e.to].size();i++)
		{
			Edge te=VER[e.to][i];
			pq.push((Edge){te.to,e.l+te.l});
		}
	}
	return 10000002;
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
		for(int i=0;i<M;i++)
		{
			int a,b;double l;scanf("%d%d%lf",&a,&b,&l);
			VER[a].push_back((Edge){b,l});
		}
		double ans=10000001;
		bool found=false;
		for(int i=1;i<=N;i++)
		{
			double ta=solve(i);
			if(ta<ans)
			{
				found=true;
				ans=ta;
			}
		}
		printf("Case #%d: ",kase++);
		if(found)printf("%.2lf\n",ans);
		else printf("No cycle found.\n");
	}
	return 0;
}
