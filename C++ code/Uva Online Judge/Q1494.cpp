#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int T,N;
	struct City{int x,y,p;};
City CITY[1000];
vector<int> TO[1000];
int DJSET[1000];
void getmax(double &a,double b){if(b>a)a=b;}
	struct Point{int x,y;};
Point CPAIR[1000000];
double pow(double a){return a*a;}
double disq(Point a){return pow(CITY[a.x].x-CITY[a.y].x)+pow(CITY[a.x].y-CITY[a.y].y);}
bool cmp_CPAIR(Point a,Point b)
{
	if(a.x==a.y)return false;
	if(b.x==b.y)return true;
	return disq(a)<disq(b);
}
int findset(int a){return DJSET[a]==a?a:(DJSET[a]=findset(DJSET[a]));}
double MSTCOST,MAXCOST[1000][1000];
int VIS[1000];
void dfs_MAXCOST(int &o,int u,double dis)
{
	if(VIS[u])return;
	VIS[u]=1;
	MAXCOST[o][u]=dis;
	for(int i=0;i<TO[u].size();i++)
	{
		int j=TO[u][i];
		dfs_MAXCOST(o,j,max(dis,sqrt(disq((Point){u,j}))));
	}
}
void buildMST()
{
	for(int c1=0;c1<N;c1++)
	{
		DJSET[c1]=c1;
		TO[c1].clear();
		for(int c2=0;c2<N;c2++)
		{
			CPAIR[c1*N+c2]=(Point){c1,c2};
		}
	}
	sort(CPAIR,CPAIR+N*N,cmp_CPAIR);
	/*for(int c1=0;c1<N*N;c1++)
	{
		printf(" %lf",disq(CPAIR[c1]));
	}printf("\n");*/
	int cnet=0,idx=0;
	MSTCOST=0;
	while(cnet<N-1)
	{
		Point &p=CPAIR[idx++];
		if(findset(p.x)==findset(p.y))continue;
		DJSET[findset(p.x)]=findset(p.y);
		TO[p.x].push_back(p.y);
		TO[p.y].push_back(p.x);
		MSTCOST+=sqrt(disq(p));
		cnet++;
	}
	for(int c1=0;c1<N;c1++)
	{
		for(int i=0;i<N;i++)VIS[i]=0;
		dfs_MAXCOST(c1,c1,0);
	}
}
double solve(int c1,int c2)
{
	double up=CITY[c1].p+CITY[c2].p;
	double down=MSTCOST-MAXCOST[c1][c2];//+sqrt(disq((Point){c1,c2}));
	//printf("(%d,%d),down=%lf\tans=%lf\n",c1,c2,down,up/down);
	return up/down;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			City &c=CITY[i];
			scanf("%d%d%d",&c.x,&c.y,&c.p);
		}
		buildMST();
		double ans=0;
		for(int c1=0;c1<N;c1++)
		{
			for(int c2=0;c2<N;c2++)
			{
				if(c1==c2)continue;
				getmax(ans,solve(c1,c2));
			}
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
