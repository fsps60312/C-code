#include<cstdio>
#include<cstdlib>
#include<cmath>
double L,T,n;
const double errorrate=1e-15;
double value(double a)
{
	return sin(a)/a-L/(L*(1+T*n));
}
double approach(double a,double b)
{
	double mid=(a+b)/2;
	if(b-a<errorrate) return mid;
	if(value(mid)>0) return approach(mid,b);
	else return approach(a,mid);
}
double solve()
{
	if(T*n==0) return 0.0;
	//sin(a)=L/2/r
	//r=L/2/sin(a)
	//2ar=L+T*n
	//sin(a)/a=L/2ar=L/(L+T*n)
	//`(sin(a)/a)=`sin(a)*a^-1+sin(a)*`a^-1
	//=cos(a)/a+sin(a)*(-a^-2)=cos(a)/a-sin(a)/a^2
	//if==0
	//a*cos(a)=sin(a)
	//a=tan(a)
	//so a==0 if(a<=Pi/2), no second ans
	double a=approach(0.0,1.5);
	double r=L/2/sin(a);
	//printf("a=%.10lf,r=%.10lf\n",a,r);
	return r-sqrt(r*r-(L/2)*(L/2));
}
int main()
{
	while(scanf("%lf%lf%lf",&L,&T,&n)==3&&L>=0&&T>=0&&n>=0)
	{
		//n*=1000;
		printf("%.3lf\n",solve());
	}
	return 0;
}
