#include<cstdio>
#include<cmath>
struct Dot
{
	double x,y;
}START,END,W1,W2;
double V,T;
void SolveEquation(double a,double b,double c,double &x,double &y)
{
	x=(-b+sqrt(b*b-4.0*a*c))/(2.0*a);
	y=(-b-sqrt(b*b-4.0*a*c))/(2.0*a);
}
double Pow(double a){return a*a;}
void Solve1(double a,double b,double c,double d,double v,double x,double y,double &ans1,double &ans2)
{
	SolveEquation(c*c+d*d-v*v,2.0*(a*c-c*x+b*d-d*y),x*x+a*a-2.0*a*x+y*y+b*b-2.0*b*y,ans1,ans2);
}
double Solve()
{
	double t1,t2;
	Solve1(START.x,START.y,W1.x,W1.y,V,END.x,END.y,t1,t2);
	double ans=1e100;
	if(t1>=0.0&&t1<=T)ans=min(ans,t1);
	if(t2>=0.0&&t2<=T)ans=min(ans,t2);
	if(ans!=1e100)return ans;
	
}
int main()
{
	scanf("%lf%lf%lf%lf",&START.x,&START.y,&END.x,&END.y);
	scanf("%lf%lf",&V,&T);
	scanf("%lf%lf%lf%lf",&W1.x,&W1.y,&W2.x,&W2.y);
	printf("%.9f\n",Solve());
	return 0;
}
