#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0);
double Solve(const double l,const double r1,const double r2)
{
	if(r1<r2)return Solve(l,r2,r1);
	if(r1+r2<l+EPS)return 0.0;
	const double s=(l+r1+r2)/2.0;
	const double area=sqrt(s*(s-l)*(s-r1)*(s-r2));
	if(r1*r1<=l*l+r2*r2)
	{
		double ans=0.0;
		ans+=acos((r1*r1+l*l-r2*r2)/(2.0*r1*l))*r1*r1;
		ans+=acos((r2*r2+l*l-r1*r1)/(2.0*r2*l))*r2*r2;
		return ans-area*2.0;
	}
	else if(r1-l<r2-EPS)
	{
		double ans=acos((r2*r2+l*l-r1*r1)/(2.0*r2*l))*r2*r2;
		const double h=area*2.0/l;
		const double b=sqrt(r2*r2-h*h);
		return ans-h*b;
	}
	else return PI*r2*r2;
	assert(0);
}
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
int main()
{
//	freopen("in.txt","r",stdin);
	for(double x1,y1,r1,x2,y2,r2;scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&r1,&x2,&y2,&r2)==6;)
	{
		printf("%.9lf\n",Solve(Hypot(x1-x2,y1-y2),r1,r2));
	}
	return 0;
}
