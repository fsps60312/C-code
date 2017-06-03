#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0),INF=1e100;
struct Point
{
	double X,Y;
	Point(){}
	Point(const double _X,const double _Y):X(_X),Y(_Y){}
};
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
double Dist(const Point &a,const Point &b){return Hypot(a.X-b.X,a.Y-b.Y);}
struct Vector
{
	double X,Y;
	Vector(){}
	Vector(const double _X,const double _Y):X(_X),Y(_Y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
Vector operator*(const Vector &a,const double b){return Vector(a.X*b,a.Y*b);}
Point operator+(const Point &a,const Vector &b){return Point(a.X+b.X,a.Y+b.Y);}
Vector Rotate(const Vector &o,const double angle){return Vector(cos(angle)*o.X-sin(angle)*o.Y,cos(angle)*o.Y+sin(angle)*o.X);}
Vector Unit(const Vector &o){const double v=Hypot(o.X,o.Y);return Vector(o.X/v,o.Y/v);}
Point A,B;
double VMAX,T;
Vector V1,V2;
double Time(const Vector &w,const Point &s,const Point &t)
{
	double l=0,r=INF;
	while(r-l>=EPS)
	{
		double mid=(l+r)/2;
		if(Dist(t,s+w*mid)<=VMAX*mid)r=mid;
		else l=mid;
	}
	return (l+r)/2;
}
double Solve(const double angle)
{
	return T+Time(V2,A+V1*T+Unit(Rotate(B-A,angle))*VMAX*T,B);
}
double Solve()
{
	if(Time(V1,A,B)<=T)return Time(V1,A,B);
	else
	{
		double l=-PI/2,r=PI/2;
		while(r-l>=EPS)
		{
			double ml=(l+l+r)/3,mr=(l+r+r)/3;
			if(Solve(ml)>Solve(mr))l=ml;
			else r=mr;
		}
		return Solve((l+r)/2);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf%lf%lf",&A.X,&A.Y,&B.X,&B.Y)==4)
	{
		scanf("%lf%lf",&VMAX,&T);
		scanf("%lf%lf%lf%lf",&V1.X,&V1.Y,&V2.X,&V2.Y);
		printf("%.10f\n",Solve());
	}
	return 0;
}
