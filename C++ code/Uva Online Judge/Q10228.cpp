#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;
const int MOD=10000;
const double PI=acos(-1.0),EPS=1e-9,DM=MOD;
int T,N;
double X[100],Y[100];
double Hypot(double a,double b){return sqrt(a*a+b*b);}
double F(double x,double y)
{
	double ans=0.0;
	for(int i=0;i<N;i++)ans+=Hypot(x-X[i],y-Y[i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	srand(time(NULL));
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		double x,y,dx,dy;
		for(int i=0;i<N;i++)
		{
			scanf("%lf%lf",&X[i],&Y[i]);
			x+=X[i],y+=Y[i];
		}
//		int cnt=0;x=0.0,y=0.0;
		x/=N,y/=N;
		double r=10000.0,ratio=0.999;
		double ans=F(x,y),ta,angle;
		while(r>EPS)
		{
			angle=((double)((rand()%MOD+MOD)%MOD))/DM*2.0*PI;
			dx=r*cos(angle),dy=r*sin(angle);
//			printf("%.2f,%.2f\n",dx,dy);
			ta=F(x+dx,y+dy);
			if(ta<ans)ans=ta,x+=dx,y+=dy;
			r*=ratio;
//			cnt++;
		}
//		printf("cnt=%d\n",cnt);
		printf("%.0f\n",ans);
	}
	return 0;
}
