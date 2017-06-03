#include<cstdio>
#include<cstdlib>
unsigned long long n,k,dp1[31][901],dp2[31][901];
int main()
{
    dp1[0][0]=1;
    for(unsigned long long i=1;i<61;i++) dp1[0][i]=0;
    //counts of dp1[i]: (i-1)/2*2+1
    for(unsigned long long i=1;i<=30;i++)
    {
        dp1[i][0]=1;
        for(unsigned long long j=1;j<901;j++)
        {
            dp1[i][j]=dp1[i-1][j-1]*(((i-1)/2*2+1)-(j-1));
            dp1[i][j]+=dp1[i-1][j];
        }
    }
    //counts of dp2[i]: (i+1)/2*2
    dp2[0][0]=1;
    for(unsigned long long i=1;i<901;i++) dp2[0][i]=0;
    for(unsigned long long i=1;i<=30;i++)
    {
        dp2[i][0]=1;
        for(unsigned long long j=1;j<901;j++)
        {
            dp2[i][j]=dp2[i-1][j-1]*(((i+1)/2*2)-(j-1));
            dp2[i][j]+=dp2[i-1][j];
        }
    }
    while(scanf("%llu%llu",&n,&k)==2&&(n||k))
    {
        unsigned long long ans=0;
        for(unsigned long long i=0;i<=k;i++)
        {
            ans+=dp1[n][i]*dp2[n-1][k-i];
        }
        printf("%llu\n",ans);
    }
    return 0;
}
