#include<cstdio>
#include<cstdlib>
int T,n,S[1000];
double average,ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        average=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&S[i]);
            average=average+S[i];
        }
        average=average/n;
        //printf(" %.3llf\n",average);
        ans=0;
        for(int i=0;i<n;i++)
        {
            if(S[i]>average) ans=ans+100;
        }
        ans=ans/n;
        printf("%.3lf%%\n",ans);
    }
}
