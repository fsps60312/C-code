#include<cstdio>
#include<cmath>
const double EPS=1e-9;
double H,D,V,R;
double abs(double a){return a>=0.0?a:-a;}
double sq(double a){return a*a;}
double SF(double x,double z)
{
    return 0.5*x*sqrt(x*x+z*z)+0.5*z*z*log(x+sqrt(x*x+z*z));
}
double inteA(double l,double r,double z)
{
    //F[x]=sqrt(x*x+z*z)
    //S[H*(R-sqrt(x*x+z*z))/R]
    //=S[H]-S[H/R*F(x)]
    //=(r-l)*H-H/R*ans
    double ans=SF(r,z)-SF(l,z);
    return (r-l)*H-H/R*ans;
}
double inteA(double z){double dis=sqrt(R*R-z*z);return 2.0*inteA(0.0,dis,z);}
double getV(double l,double r){return (r-l)/6.0*(inteA(l)+inteA(r)+4.0*inteA(0.5*(l+r)));}
double inteV(double l,double r)
{
    double s0=getV(l,r);
    double mid=0.5*(l+r),s1=getV(l,mid)+getV(mid,r);
    if(abs(s0-s1)<EPS)return s1;
    return inteV(l,mid)+inteV(mid,r);
}
int main()
{
    //printf("%.3f\n",log(10));
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf%lf%lf",&H,&D,&V);
        double l=0,r=R=0.5*D,mid;
        while(r-l>EPS)
        {
            mid=0.5*(r+l);
            //printf("mid=%.3lf\n",mid);
            if(inteV(mid,R)>V)l=mid;
            else r=mid;
        }
        printf("%.5f\n",l+R);
    }
    return 0;
}
