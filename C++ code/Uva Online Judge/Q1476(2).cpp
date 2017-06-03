#include<cstdio>
const double EPS=1e-9;
int T,N;
double A[10000],B[10000],C[10000];
void getmax(double &a,double b){if(b>a)a=b;}
double F(double x)
{
    double ans=-5000000.0-5000.0;
    for(int i=0;i<N;i++)getmax(ans,A[i]*x*x+B[i]*x+C[i]);
    return ans;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=0;i<N;i++)scanf("%lf%lf%lf",&A[i],&B[i],&C[i]);
        double l=0.0,r=1000.0,ml,mr;
        while(r-l>EPS)
        {
            ml=l+(r-l)/3.0;
            mr=r-(r-l)/3.0;
            if(F(ml)<F(mr))r=mr;
            else l=ml;
        }
        printf("%.4f\n",F((r+l)/2.0));
    }
    return 0;
}
