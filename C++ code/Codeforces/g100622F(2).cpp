//a(x1-x2)+(y1-y2)=(x3-x4)-a(y3-y4)
//a((x1-x2)+(y3-y4))=(x3-x4)-(y1-y2)
//a(x1-x2)+(y1-y2)=a(y3-y4)-(x3-x4)
//a((x1-x2)-(y3-y4))=-(x3-x4)-(y1-y2)
//(a,b)=((x3-x4)-(y1-y2),(x1-x2)+(y3-y4))
//(a,b)=(-(x3-x4)-(y1-y2),(x1-x2)-(y3-y4))
//ax1+by1+c1=0
//bx3-ay3+c3=0
#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
double Cross(const double x1,const double y1,const double x2,const double y2)
{
	return x1*y2-x2*y1;
}
bool SameDirection(const double x1,const double y1,const double x2,const double y2,const double x3,const double y3)
{
	return (Cross(x1,y1,x2,y2)>0)==(Cross(x2,y2,x3,y3)>0);
}
double X1,Y1,X2,Y2,X3,Y3,X4,Y4;
void SolveIntersection(const double a1,const double b1,const double c1,const double a2,const double b2,const double c2,double &x,double &y)
{
	//a1x+b1y+c1=0
	//a2x+b2y+c2=0
	//a1a2x+b1a2y+c1a2=0
	//a1a2x+a1b2y+a1c2=0
	//(b1a2-a1b2)y+(c1a2-a1c2)=0
	//y=(a1c2-c1a2)/(b1a2-a1b2)
	
	//a1b2x+b1b2y+c1b2=0
	//b1a2x+b1b2y+b1c2=0
	//(a1b2-b1a2)x+(c1b2-b1c2)=0
	//x=(b1c2-c1b2)/(a1b2-b1a2)
	if(!(fabs(a1*b2-b1*a2)>1e-7))
	{
		printf("(%f,%f)(%f,%f)\n",a1,b1,a2,b2);
		assert(fabs(a1*b2-b1*a2)>1e-7);
		assert(0);
	}
	x=(b1*c2-c1*b2)/(a1*b2-b1*a2);
	y=(a1*c2-c1*a2)/(b1*a2-a1*b2);
}
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
double Dist(const double x1,const double y1,const double x2,const double y2)
{
	return Hypot(x1-x2,y1-y2);
}
const double EPS=1e-8;
bool Solve(const double a,const double b)
{
//	printf("(%f,%f)\n",a,b);
	const double c1=0-(a*X1+b*Y1),c2=0-(a*X2+b*Y2);
	const double c3=0-(b*X3-a*Y3),c4=0-(b*X4-a*Y4);
	double x1,y1,x2,y2,x3,y3,x4,y4;
	SolveIntersection(a,b,c1,b,-a,c3,x1,y1);
	SolveIntersection(a,b,c1,b,-a,c4,x2,y2);
	SolveIntersection(a,b,c2,b,-a,c4,x3,y3);
	SolveIntersection(a,b,c2,b,-a,c3,x4,y4);
	if(!SameDirection(x1-X2,y1-Y2,X1-X2,Y1-Y2,x2-X2,y2-Y2))return false;
	if(!SameDirection(x2-X3,y2-Y3,X4-X3,Y4-Y3,x3-X3,y3-Y3))return false;
	if(!SameDirection(x3-X1,y3-Y1,X2-X1,Y2-Y1,x4-X1,y4-Y1))return false;
	if(!SameDirection(x4-X4,y4-Y4,X3-X4,Y3-Y4,x1-X4,y1-Y4))return false;
	printf("%f %f\n",x1,y1);
	printf("%f %f\n",x2,y2);
	printf("%f %f\n",x3,y3);
	printf("%f %f\n",x4,y4);
	assert(fabs(Dist(x1,y1,x2,y2)-Dist(x3,y3,x4,y4))<EPS&&fabs(Dist(x1,y1,x3,y3)-Dist(x2,y2,x4,y4))<EPS&&fabs(Dist(x1,y1,x4,y4)-Dist(x2,y2,x3,y3))<EPS&&fabs(Dist(x1,y1,x2,y2)-Dist(x2,y2,x3,y3))<EPS);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("four.in","r",stdin);
	freopen("four.out","w",stdout);
	while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&X1,&Y1,&X2,&Y2,&X3,&Y3,&X4,&Y4)==8)
	{
		if(SameDirection(X3-X1,Y3-Y1,X4-X1,Y4-Y1,X2-X1,Y2-Y1))swap(X2,X4),swap(Y2,Y4);
		else if(SameDirection(X2-X1,Y2-Y1,X3-X1,Y3-Y1,X4-X1,Y4-Y1))swap(X2,X3),swap(Y2,Y3);
		assert(SameDirection(X3-X1,Y3-Y1,X2-X1,Y2-Y1,X4-X1,Y4-Y1));
//		printf("(%f,%f)\n(%f,%f)\n(%f,%f)\n(%f,%f)\n",X1,Y1,X2,Y2,X3,Y3,X4,Y4);
		if(fabs(Dist(X1,Y1,X2,Y2)-Dist(X3,Y3,X4,Y4))<EPS&&fabs(Dist(X1,Y1,X3,Y3)-Dist(X2,Y2,X4,Y4))<EPS&&fabs(Dist(X1,Y1,X4,Y4)-Dist(X2,Y2,X3,Y3))<EPS&&fabs(Dist(X1,Y1,X4,Y4)-Dist(X2,Y2,X4,Y4))<EPS)
		{
//			puts("pass");
			for(double angle=0;;angle+=0.1)if(Solve(sin(angle),cos(angle)))break;
		}
		else if(!Solve((X3-X4)-(Y1-Y2),(X1-X2)+(Y3-Y4)))
		{
			if(!Solve(-(X3-X4)-(Y1-Y2),(X1-X2)-(Y3-Y4)))
			{
				for(int i=0;i<4;i++)puts("0 0");
			}
		}
	}
	return 0;
}
