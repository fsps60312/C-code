#include<cstdio>
#include<cstdlib>
#include<cmath>
int S[50],n;
bool iscoprime(int a,int b)
{
    if(b==0) return a==1;
    return iscoprime(b,a%b);
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&S[i]);
        }
        double a=0,b=n*(n-1)/2;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(S[i]>=S[j]&&iscoprime(S[i],S[j])) a=a+1;
                else if(S[i]<S[j]&&iscoprime(S[j],S[i])) a=a+1;
            }
        }
        if(a==0) printf("No estimate for this data set.\n");
        else printf("%.6lf\n",sqrt(6*b/a));
    }
    return 0;
}
