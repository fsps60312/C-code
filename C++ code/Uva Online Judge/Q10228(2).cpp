#include<cstdio>
#include<cmath>
using namespace std;
const double EPS=1e-9;
int T,N;
double X[100],Y[100],d[4][2]={{1.0,0.0},{-1.0,0.0},{0.0,1.0},{0.0,-1.0}};
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
		x/=N,y/=N;
//		x=y=0.0;
		double r=10000.0,ratio=0.9;
		double ans=F(x,y),ta,angle;
		while(r>EPS)
		{
			for(int i=0;i<4;i++)
			{
				dx=r*d[i][0],dy=r*d[i][1];
				ta=F(x+dx,y+dy);
				if(ta<ans)ans=ta,x+=dx,y+=dy;
			}
			r*=ratio;
		}
		printf("%.0f\n",ans);
		if(T)puts("");
	}
	return 0;
}
