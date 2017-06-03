#include<cstdio>
#include<cmath>
#include<cassert>
using namespace std;
const double EPS=1e-7;
bool Zero(const double a){return fabs(a)<EPS;}
bool AtRange(const double o,const double a,const double b){return (a<=o+EPS&&o<=b+EPS)||(b<=o+EPS&&o<=a+EPS);}
struct Pair
{
	double x,y;
	Pair(){}
	Pair(const int _x,const int _y):x(_x),y(_y){}
}P1[2],P2[2];
//ax+by=c
//Ax+By=C
//Aax+Aby=Ac
//Aax+Bay=Ca
//(Ab-Ba)y=Ac-Ca
//y=(Ac-Ca)/(Ab-Ba)
//Bax+Bby=Bc
//Abx+Bby=Cb
//(Ba-Ab)x=Bc-Cb
//x=(Bc-Cb)/(Ba-Ab)
double Sq(const double a){return a*a;}
double Dist(const Pair &a,const Pair &b)
{
	return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));
}
double Halon(const double a,const double b,const double c)
{
	const double s=(a+b+c)/2.0;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
double Area(const Pair &a,const Pair &b,const Pair &c)
{
	return Halon(Dist(a,b),Dist(b,c),Dist(a,c));
}
double Solve()
{
	double x1=P1[0].x,x2=P1[1].x,y1=P1[0].y,y2=P1[1].y;
	const double a=y2-y1,b=x1-x2,c=x1*y2-x2*y1;
//	assert(Zero(a*x1+b*y1-c)&&Zero(a*x2+b*y2-c));
	x1=P2[0].x,x2=P2[1].x,y1=P2[0].y,y2=P2[1].y;
	const double A=y2-y1,B=x1-x2,C=x1*y2-x2*y1;
//	assert(Zero(A*x1+B*y1-C)&&Zero(A*x2+B*y2-C));
	if(Zero(A*b-B*a))return 0.0;
	double x=(B*c-C*b)/(B*a-A*b),y=(A*c-C*a)/(A*b-B*a);
//	printf("(%.4f,%.4f)\n",x,y);
	if(AtRange(x,P1[0].x,P1[1].x)&&AtRange(y,P1[0].y,P1[1].y)&&AtRange(x,P2[0].x,P2[1].x)&&AtRange(y,P2[0].y,P2[1].y))
	{
		const Pair o=Pair(x,y);
		return Area(P1[0],P1[1],P2[0])+Area(P1[0],P1[1],P2[1]);
//		return Area(o,P1[0],P2[0])+Area(o,P1[0],P2[1])+Area(o,P1[1],P2[0])+Area(o,P1[1],P2[1]);
	}
	else return 0.0;
}
int main()
{
//	freopen("E.txt","r",stdin);
	while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&P1[0].x,&P1[0].y,&P1[1].x,&P1[1].y,&P2[0].x,&P2[0].y,&P2[1].x,&P2[1].y)==8)
	{
		printf("%.10f\n",Solve());
		break;
	}
	return 0;
}
