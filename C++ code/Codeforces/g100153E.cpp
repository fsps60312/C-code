#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0),EPS=1e-9;
double Hypot(const double x,const double y,const double z){return sqrt(x*x+y*y+z*z);}
double Angle(const double x,const double y)
{
	if(x==0&&y==0)return 0.0;
	if(x>0&&y>=0)return 0.0*PI+atan2(y,x);
	if(x<=0&&y>0)return 0.5*PI+atan2(-x,y);
	if(x<0&&y<=0)return 1.0*PI+atan2(-y,-x);
	if(x>=0&&y<0)return 1.5*PI+atan2(x,-y);
	assert(0);return 0.0;
}
double CurveLength(const double chord,const double radius)
{
	const double angle=asin((chord/2)/radius);
	return angle*2*radius;
}
double R,D,Z1,H1,Z2,H2,H;
double DIF;
double Solve(const double dif)
{
	const double x=H*cos(dif),y=H*sin(dif),z=D/2;
	return CurveLength(Hypot(H1-x,0-y,Z1-z),R)+CurveLength(Hypot(H2*cos(DIF)-x,H2*sin(DIF)-y,Z2-z),R);
}
void ReadInput()
{
	double x1,y1,x2,y2;
	scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&Z1,&x2,&y2,&Z2);
	if(fabs(Hypot(x1,y1,Z1)-R)>fabs(Hypot(x2,y2,Z2)-R))swap(x1,x2),swap(y1,y2),swap(Z1,Z2);
	assert(fabs(Hypot(x1,y1,Z1)-R)<EPS&&fabs(Hypot(x2,y2,Z2-D)-R)<EPS);
	assert(Z1<=Z2);
	H1=Hypot(x1,y1,0.0),H2=Hypot(x2,y2,0.0);
	DIF=fabs(Angle(x1,y1)-Angle(x2,y2));
	if(DIF>PI)DIF=2*PI-DIF;
	assert(DIF<PI+EPS);
	H=sqrt(R*R-(D/2)*(D/2));
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	while(scanf("%lf%lf",&R,&D)==2)
	{
		ReadInput();
		double l=0,r=DIF;
		while(r-l>=EPS)
		{
			const double ml=(l+l+r)/3,mr=(l+r+r)/3;
			if(Solve(ml)<Solve(mr))r=mr;
			else l=ml;
		}
		printf("%.15f\n",Solve((l+r)/2));
	}
	return 0;
}
