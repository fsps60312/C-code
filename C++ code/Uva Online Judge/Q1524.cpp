#include<cstdio>
int N;
double S,E,F[100];
double solve()
{
    double ans=0.0,p1=S,p2=E;
    for(int i=0;i<=N;i++)
    {
        F[i]/=i+1;
        ans+=F[i]*(p2-p1);
        p1*=S,p2*=E;
    }
    return ans/(E-S);
}
int main()
{
    while(scanf("%d",&N)&&N)
    {
        for(int i=N;i>=0;i--)scanf("%lf",&F[i]);
        scanf("%lf%lf",&S,&E);
        printf("%.3f\n",solve());
    }
    return 0;
}
