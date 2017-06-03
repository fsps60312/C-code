#include<cstdio>
#include<cmath>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;
const double PI=acos(-1.0),INF=1e100,EPS=1e-9;
void getmax(double &a,const double &b){if(b>a)a=b;}
void getmin(double &a,const double &b){if(b<a)a=b;}
struct Oppo
{
	double x,y,range;
	Oppo(){}
	Oppo(const double &_x,const double &_y,const double &_r):x(_x),y(_y),range(_r){}
//	void Print(){printf("(%.2f,%.2f,%.2f)\n",x,y,range);}
};
double Sq(const double &a){return a*a;}
int N;
vector<Oppo>OPPO;
vector<int>ET[1000];
bool VIS[1000];
void BuildEdge()
{
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
	{
		Oppo &oa=OPPO[i],&ob=OPPO[j];
		if(Sq(oa.range+ob.range)>=EPS+Sq(oa.x-ob.x)+Sq(oa.y-ob.y))ET[i].push_back(j),ET[j].push_back(i);
	}
}
bool Solve(double &lans,double &rans)
{
	BuildEdge();
	for(int i=0;i<N;i++)VIS[i]=false;
	lans=1000.0,rans=1000.0;
	for(int i=0;i<N;i++)if(!VIS[i])
	{
		double down=INF,up=-INF;
		double tlans=INF,trans=INF;
		queue<int>q;
		q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			if(VIS[u])continue;
			VIS[u]=true;
//			printf(" %d",u);
			const Oppo &o=OPPO[u];
			getmax(up  ,o.y+o.range);
			getmin(down,o.y-o.range);
			if(o.x-o.range<=0.0)getmin(tlans,o.y-sqrt(Sq(o.range)-Sq(o.x)));
			if(o.x+o.range>=1000.0)getmin(trans,o.y-sqrt(Sq(o.range)-Sq(1000.0-o.x)));
			for(const int nxt:ET[u])q.push(nxt);
		}
//		puts("");
		if(up>=1000.0)
		{
			getmin(lans,tlans),getmin(rans,trans);
			if(down<=0.0)return false;
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		OPPO.clear();
		for(int i=0;i<N;i++)
		{
			static double x,y,r;
			scanf("%lf%lf%lf",&x,&y,&r),OPPO.push_back(Oppo(x,y,r));
		}
		double lans,rans;
		if(Solve(lans,rans))printf("%.2lf %.2lf %.2lf %.2lf\n",0.0,lans,1000.0,rans);
		else puts("IMPOSSIBLE");
	}
	return 0;
}
