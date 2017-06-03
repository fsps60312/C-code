#include<cstdio>
#include<cmath>
const double EPS=1e-9;
int T;
double D,H,B,L;
double sq(double x){return x*x;}
double F(double x,double d){return sqrt(1.0+sq(8.0*H/sq(d)*x));}//a x^2==H, a(d^2)/4==H, a=4H/d^2
double SUM(double l,double r,double d){return (r-l)/6.0*(F(l,d)+F(r,d)+4.0*F(0.5*(l+r),d));}
double ABS(double a){return a>=0.0?a:-a;}
double MAX(double a,double b){return a>b?a:b;}
double LEN(double l,double r,double d)
{
    double s0=SUM(l,r,d);
    double mid=0.5*(l+r),s1=SUM(l,mid,d)+SUM(mid,r,d);
    if(ABS(s0-s1)<=EPS)return s1;
    return LEN(l,mid,d)+LEN(mid,r,d);
}
double CMP(double gaps){return LEN(0.0,0.5*B/gaps,B/gaps)*gaps*2.0;}
int CEILING(double a){return a-(int)a==0.0?(int)a:(int)a+1;}
int getgaps()
{
    double l=MAX(1.0,B/D),r=sqrt((sq(L)-sq(D))/(4.0*sq(H))),mid;
    while((int)l<(int)r)
    {
        mid=0.5*(l+r);
        //printf("mid=%lf\n",H);
        if(CMP(mid)>L)l=mid;
        else r=mid;
    }
    return CEILING(l);
}
int main()
{
    printf("%d\n",CEILING(1.0001));
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    int kase=0;
    while(T--)
    {
        scanf("%lf%lf%lf%lf",&D,&H,&B,&L);
        //ax^2+c a(d/2)^2==H
        //a==H/(d/2)^2
        //sqrt(1+(2ax)^2)
        //==sqrt(1+(8H/d x)^2)
        //==sqrt(1+64H^2/d^2 x^2)
        //x=sqrt((H-c)/a)
        //S(sqrt(dx^2+(dx*'f(x))^2))
        //=S: sqrt(1+(2ax)^2)
        //=S: sqrt(1+4a^2x^2)
        //simpson: S(f)=(b-a)/6*(f(a)+4f((a+b)/2)+f(b))
        double ans=(double)getgaps();
        //printf("CMP(ans)=%lf\nCMP(ans-1.0)=%lf\nL=%lf\n",CMP(ans),CMP(ans-1.0),L);
        double h=H,l=0.0,r=H;
        while(r-l>EPS)
        {
            H=0.5*(r+l);
            //printf("H=%lf\n",H);
            if(CMP(ans)>L)r=H;
            else l=H;
        }
        if(kase)puts("");
        printf("Case %d:\n%.2f\n",++kase,h-H);
    }
    return 0;
}
