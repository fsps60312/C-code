#include<cstdio>
#include<cmath>
const double PI=acos(-1.0),EPS=1e-2;
double R,H;
double Abs(double x){return x>=0?x:-x;}
double F(double x){return PI*R*R+2.0*(H-x)*sqrt(R*R-x*x)-2.0*Abs(acos(x/R))*R*R;}
double Sum(double l,double r){return 0.5*(F(l)+F(r))*(r-l);}
double GetV(double l,double r)
{
    double ans=0.0;
    for(int i=0;i<=100000;i++)ans+=F(l+i*(r-l)/100000.0)*(r-l)/100000.0;
    return ans;
}
double solve1()
{
    double ans=(H-R*2.0)*PI*R*R;
    return ans+GetV(0.0,R)*2.0;
    //abs(x)<=R:
    //A==Pi R^2 + 2H sqrt(R^2-x^2) - 2x sqrt(R^2-x^2) - 4 acos(x/R)/2Pi * Pi R^2
    //==Pi R^2 + 2(H-x)sqrt(R^2-x^2) - 2abs(acos(x/R))R^2
}
double solve2()
{

}
int main()
{
    while(scanf("%lf%lf",&R,&H)==2)
    {
        printf("%.4f\n",H>=R*2.0?solve1():solve2());
    }
    return 0;
}
