#include<cstdio>
#include<cmath>
#include<cassert>
using namespace std;
const double INF=1e100,EPS=1e-9;
void getmin(double &a,const double b){if(b<a)a=b;}
void getmax(double &a,const double b){if(b>a)a=b;}
int N;
struct Hungary
{
	double DIST[100][100];
	double WA[100],WB[100];
	int AT[100],BT[100];
	bool AVIS[100],BVIS[100];
	bool CheckPaired(const int source)
	{
		assert(!AVIS[source]);
		AVIS[source]=true;
		for(int i=0;i<N;i++)if(!BVIS[i]&&DIST[source][i]-WA[source]-WB[i]<EPS)
		{
			assert(DIST[source][i]-WA[source]-WB[i]>-EPS);
			BVIS[i]=true;
			if(BT[i]==-1||CheckPaired(BT[i]))
			{
				AT[source]=i,BT[i]=source;
				return true;
			}
		}
		return false;
	}
	void Update()
	{
		double low=INF;
		for(int i=0;i<N;i++)if(AVIS[i])
		{
			for(int j=0;j<N;j++)if(!BVIS[j])
			{
				getmin(low,DIST[i][j]-WA[i]-WB[j]);
			}
		}
		for(int i=0;i<N;i++)
		{
			if(AVIS[i])WA[i]+=low;
			if(BVIS[i])WB[i]-=low;
		}
	}
	void Solve()
	{
		for(int i=0;i<N;i++)WA[i]=WB[i]=0.0,AT[i]=BT[i]=-1;
		for(int source=0;source<N;source++)if(AT[source]==-1)
		{
			for(;;)
			{
				for(int i=0;i<N;i++)AVIS[i]=BVIS[i]=false;
				if(CheckPaired(source))break;
				else Update();
			}
		}
	}
}HUNGARY;
struct Dot
{
	double x,y;
}ANT[100],TREE[100];
double Sq(const double &a){return a*a;}
double Dist(const Dot &a,const Dot &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lf%lf",&ANT[i].x,&ANT[i].y);
		for(int i=0;i<N;i++)scanf("%lf%lf",&TREE[i].x,&TREE[i].y);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)HUNGARY.DIST[i][j]=Dist(ANT[i],TREE[j]);
		HUNGARY.Solve();
		for(int i=0;i<N;i++)printf("%d\n",HUNGARY.AT[i]+1);
	}
	return 0;
}
