#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const long double EPS=1e-12,PI=acos(-1.0);
long double Solve(const long double l,const long double r1,const long double r2)
{
	if(r1<r2)return Solve(l,r2,r1);
	if(r1+r2<l+EPS)return 0.0;
	const long double s=(l+r1+r2)/2.0;
	const long double area=sqrt(s*(s-l)*(s-r1)*(s-r2));
	if(r1-l<r2-EPS)
	{
		long double ans=0.0;
		ans+=acos((r1*r1+l*l-r2*r2)/(2.0*r1*l))*r1*r1;
		ans+=acos((r2*r2+l*l-r1*r1)/(2.0*r2*l))*r2*r2;
		return ans-area*2.0;
	}
	else return PI*r2*r2;
}
long double Hypot(const long double x,const long double y){return sqrt(x*x+y*y);}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int x1,y1,r1,x2,y2,r2;scanf("%d%d%d%d%d%d",&x1,&y1,&r1,&x2,&y2,&r2)==6;)
	{
		printf("%.9lf\n",(double)Solve(Hypot(x1-x2,y1-y2),r1,r2));
	}
	return 0;
}
