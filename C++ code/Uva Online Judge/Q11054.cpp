#include<cstdio>
#include<cstdlib>
int n;
long long S[100000];
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++)
        {
            scanf("%lld",&S[i]);
            //printf(" %lld",S[i]);
        }
        long long ans=0;
        long long nows=0;
        //long long zero=0;
        for(int i=0;i<n;i++)
        {
            //printf("%lld ",now);
            //printf("%lld\n",ans);
            nows+=S[i];
            if(nows>0)
            {
                ans+=nows;
                //printf("pass\n");
            }
            else
            {
                ans-=nows;
            }
        }
        printf("%lld\n",ans);
    }
}
