#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const double INF=1e100;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
void Multiply(const int n,const double *a,const double *b,double *ans)
{
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans[i+j]+=a[i]*b[j];
}
int T;
void GetCoefficient(const int time,const double *a,const double *b,double *ans,const double fine)
{
	for(int n=1;time%n==0;n<<=1)Multiply(n,a+n,(b+time)-n,ans+time);
	for(int i=time+1;i<=T;i++)ans[time]+=a[i]*fine;
}
struct Edge
{
	int A,B,COST;
	double P[200001],DP[200001];
};
vector<Edge>EDGE;
int N,M,X;
vector<int>ET[50];
double DP[50][200001];
void BuildDist()
{
	static double dist[50][50];
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)dist[i][j]=(i==j?0:INF);
	for(const Edge &e:EDGE)dist[e.A][e.B]=e.COST;
	for(int k=0;k<N;k++)for(int i=0;i<N;i++)for(int j=0;j<N;j++)getmin(dist[i][j],dist[i][k]+dist[k][j]);
	for(int i=0;i+1<N;i++)DP[i][0]=dist[i][N-1]+X;
	DP[N-1][0]=0.0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	EDGE.reserve(100);
	while(scanf("%d%d%d%d",&N,&M,&T,&X)==4)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static Edge e;
			scanf("%d%d%d",&e.A,&e.B,&e.COST),--e.A,--e.B;
			for(int j=1;j<=T;j++)scanf("%lf",&e.P[j]),e.P[j]/=100000.0,e.DP[j]=0;
			EDGE.push_back(e);
			ET[e.A].push_back(i);
		}
		BuildDist();
		for(int time=1;time<=T;time++)
		{
			for(Edge &e:EDGE)GetCoefficient(time,e.P,DP[e.B],e.DP,DP[e.B][0]+(e.B==N-1?X:0));
			for(int i=0;i+1<N;i++)
			{
				double &dp=DP[i][time]=INF;
				for(const int ei:ET[i])getmin(dp,EDGE[ei].DP[time]+EDGE[ei].COST);
			}
			DP[N-1][time]=0.0;
		}
		printf("%.10f\n",DP[0][T]);
	}
	return 0;
}
