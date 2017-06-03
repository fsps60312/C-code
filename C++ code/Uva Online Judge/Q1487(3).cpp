#include<cstdio>
#include<cmath>
const double PI=acos(-1.0),EPS=1e-2;
double R,H;
double Abs(double x){return x>=0?x:-x;}
double F1(double x){return PI*R*R+2.0*H*sqrt(R*R-x*x)-2.0*x*sqrt(R*R-x*x)-2.0*acos(x/R)*R*R;}
double F2(double x){return 2.0*H*sqrt(R*R-x*x)-2.0*x*sqrt(R*R-x*x)+2.0*asin(x/R)*R*R;}
double SF1(double x)
{
	double ans=x*PI*R*R;
	ans+=2.0*H*(0.5*asin(x/R)*R*R+0.5*x*sqrt(R*R-x*x));
	//x sqrt(R^2-x^2)
	//t=R^2-x^2
	//dt=-2x
	//==-0.5 dt t^0.5
	//==-0.5 1/1.5t^1.5
	//==-1/3 t^1.5
	ans-=2.0*(-1.0/3.0)*pow(R*R-x*x,1.5);
	//S[acos(x/R)dx]
	//==x acos(x/R) - S[-x/sqrt(1-(x/R)^2)/R*dx]
	//t=1-(x/R)^2
	//dt=-2x/R/R
	//==x acos(x/R) - S[0.5*R*R*dt*t^-0.5/R]
	//==x acos(x/R) - 0.5*R S[(2.0*t^0.5)']
	//==x acos(x/R) - 0.5*R 2.0*t^0.5 
	//==x acos(x/R) - R*t^0.5 
	ans-=2.0*R*R*(x*acos(x/R)-R*sqrt(1.0-(x/R)*(x/R)));
	return ans;
}
double SF2(double x)
{
	double ans=0.0;
	ans+=2.0*H*(0.5*asin(x/R)*R*R+0.5*x*sqrt(R*R-x*x));
	ans-=2.0*(-1.0/3.0)*pow(R*R-x*x,1.5);
	ans+=2.0*R*R*(x*asin(x/R)+R*sqrt(1.0-(x/R)*(x/R)));
	return ans;
}
double solve1()
{
	double ans=(H-R*2.0)*PI*R*R;
//	for(int i=0;i<=1000000;i++)ans+=2.0*R/1000000.0*F(i*R/1000000.0);return ans;
	return ans+2.0*(SF1(R)-SF1(0.0));
	//abs(x)<=R:
	//A==Pi R^2 + 2H sqrt(R^2-x^2) - 2x sqrt(R^2-x^2) - 4 acos(x/R)/2Pi * Pi R^2
	//==Pi R^2 + 2(H-x)sqrt(R^2-x^2) - 2abs(acos(x/R))R^2
}
double solve2()
{
	double ans=4.0*H*(acos(0.5*H/R)*R*R-(0.5*H)*sqrt(R*R-0.25*H*H));
//	for(int i=0;i<=1000000;i++)ans+=2.0*(0.5*H/1000000.0)*F2(0.5*H*i/1000000.0);return ans;
	return ans+2.0*(SF2(0.5*H)-SF2(0.0));
}
int main()
{
	while(scanf("%lf%lf",&R,&H)==2)
	{
		printf("%.4f\n",H>=R*2.0?solve1():solve2());
	}
	return 0;
}

