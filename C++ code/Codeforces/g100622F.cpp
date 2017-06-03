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
void SolveIntersection(const double a1,const double b1,const double c1,const double a2,const double b2,const double c2)
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
	
	assert(fabs(a1*b2-b1*a2)>1e-9);
	const double x=(b1*c2-c1*b2)/(a1*b2-b1*a2);
	const double y=(a1*c2-c1*a2)/(b1*a2-a1*b2);
	printf("%.10lf %.10lf\n",x,y);
}
void Solve(const double a,const double b)
{
	const double c1=0-(a*X1+b*Y1),c2=0-(a*X2+b*Y2);
	const double c3=0-(b*X3-a*Y3),c4=0-(b*X4-a*Y4);
	SolveIntersection(a,b,c1,b,-a,c3);
	SolveIntersection(a,b,c1,b,-a,c4);
	SolveIntersection(a,b,c2,b,-a,c4);
	SolveIntersection(a,b,c2,b,-a,c3);
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
		Solve((X3-X4)-(Y1-Y2),(X1-X2)+(Y3-Y4));
	}
	return 0;
}
