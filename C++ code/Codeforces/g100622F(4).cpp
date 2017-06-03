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
long double Cross(const long double x1,const long double y1,const long double x2,const long double y2)
{
	return x1*y2-x2*y1;
}
bool SameDirection(const long double x1,const long double y1,const long double x2,const long double y2,const long double x3,const long double y3)
{
	return (Cross(x1,y1,x2,y2)>0)==(Cross(x2,y2,x3,y3)>0);
}
long double X1,Y1,X2,Y2,X3,Y3,X4,Y4;
void SolveIntersection(const long double a1,const long double b1,const long double c1,const long double a2,const long double b2,const long double c2,long double &x,long double &y)
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
		printf("(%Lf,%Lf)(%Lf,%Lf)\n",a1,b1,a2,b2);
		assert(fabs(a1*b2-b1*a2)>1e-7);
		assert(0);
	}
	x=(b1*c2-c1*b2)/(a1*b2-b1*a2);
	y=(a1*c2-c1*a2)/(b1*a2-a1*b2);
}
long double Hypot(const long double x,const long double y){return sqrt(x*x+y*y);}
long double Dist(const long double x1,const long double y1,const long double x2,const long double y2)
{
	return Hypot(x1-x2,y1-y2);
}
const long double EPS=1e-12;
bool Solve(const long double a,const long double b)
{
//	printf("(%Lf,%Lf)\n",a,b);
	const long double c1=0-(a*X1+b*Y1),c2=0-(a*X2+b*Y2);
	const long double c3=0-(b*X3-a*Y3),c4=0-(b*X4-a*Y4);
	long double x1,y1,x2,y2,x3,y3,x4,y4;
	SolveIntersection(a,b,c1,b,-a,c3,x1,y1);
	SolveIntersection(a,b,c1,b,-a,c4,x2,y2);
	SolveIntersection(a,b,c2,b,-a,c4,x3,y3);
	SolveIntersection(a,b,c2,b,-a,c3,x4,y4);
	if(!SameDirection(x1-X2,y1-Y2,X1-X2,Y1-Y2,x2-X2,y2-Y2))return false;
	if(!SameDirection(x2-X3,y2-Y3,X4-X3,Y4-Y3,x3-X3,y3-Y3))return false;
	if(!SameDirection(x3-X1,y3-Y1,X2-X1,Y2-Y1,x4-X1,y4-Y1))return false;
	if(!SameDirection(x4-X4,y4-Y4,X3-X4,Y3-Y4,x1-X4,y1-Y4))return false;
	assert(fabs(Cross(x1-X1,y1-Y1,x2-X1,y2-Y1))<EPS);
	assert(fabs(Cross(x2-X4,y2-Y4,x3-X4,y3-Y4))<EPS);
	assert(fabs(Cross(x3-X2,y3-Y2,x4-X2,y4-Y2))<EPS);
	assert(fabs(Cross(x4-X3,y4-Y3,x1-X3,y1-Y3))<EPS);
	printf("%.10f %.10f\n",(double)x1,(double)y1);
	printf("%.10f %.10f\n",(double)x2,(double)y2);
	printf("%.10f %.10f\n",(double)x3,(double)y3);
	printf("%.10f %.10f\n",(double)x4,(double)y4);
	assert(fabs(Dist(x1,y1,x2,y2)-Dist(x3,y3,x4,y4))<EPS&&fabs(Dist(x1,y1,x3,y3)-Dist(x2,y2,x4,y4))<EPS&&fabs(Dist(x1,y1,x4,y4)-Dist(x2,y2,x3,y3))<EPS&&fabs(Dist(x1,y1,x2,y2)-Dist(x2,y2,x3,y3))<EPS);
	return true;
}
long long HypotLL(const long long x,const long long y){return x*x+y*y;}
long long DistLL(const long double x1,const long double y1,const long double x2,const long double y2)
{
	return Hypot((long long)x1-(long long)x2,(long long)y1-(long long)y2);
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("four.in","r",stdin);
	freopen("four.out","w",stdout);
	for(double x1,y1,x2,y2,x3,y3,x4,y4;scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4)==8;)
	{
		X1=x1,X2=x2,X3=x3,X4=x4;
		Y1=y1,Y2=y2,Y3=y3,Y4=y4;
		if(SameDirection(X3-X1,Y3-Y1,X4-X1,Y4-Y1,X2-X1,Y2-Y1))swap(X2,X4),swap(Y2,Y4);
		else if(SameDirection(X2-X1,Y2-Y1,X3-X1,Y3-Y1,X4-X1,Y4-Y1))swap(X2,X3),swap(Y2,Y3);
		assert(SameDirection(X3-X1,Y3-Y1,X2-X1,Y2-Y1,X4-X1,Y4-Y1));
//		printf("(%Lf,%Lf)\n(%Lf,%Lf)\n(%Lf,%Lf)\n(%Lf,%Lf)\n",X1,Y1,X2,Y2,X3,Y3,X4,Y4);
		if(DistLL(X1,Y1,X2,Y2)==DistLL(X3,Y3,X4,Y4)&&DistLL(X1,Y1,X3,Y3)==DistLL(X2,Y2,X4,Y4)&&DistLL(X1,Y1,X4,Y4)==DistLL(X2,Y2,X3,Y3)&&DistLL(X1,Y1,X4,Y4)==DistLL(X2,Y2,X4,Y4))
		{
//			puts("pass");
			for(long double angle=0;;angle+=0.1)if(Solve(sin(angle),cos(angle)))break;
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
