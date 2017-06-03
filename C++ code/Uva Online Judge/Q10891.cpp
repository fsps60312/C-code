#include<cstdio>
#include<cstdlib>
int S[101],n;
int main()
{
    while(scanf("%d",&n)==1)
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&S[i]);
            sum+=S[i];
        }
        int Min=0,Max=n-1,ans=0;
        while(1)
        {
            int a=S[Min];
            int b=2147483647;
            int c=0;
            for(int i=Min+1;i<=Max;i++)
            {
                if(a<b) b=a,c=Max-i+1;
                a+=S[i];
            }
            //a+=S[Max];
            ans+=a;
            for(int i=Min;i<Max;i++)
            {
                if(a<b) b=a,c=Min-i-1;
                a-=S[i];
            }
            if(c<0) Min-=c;
            else if(c>0) Max-=c;
            else break;
            ans-=b;
            printf("%d %d %d %d\n",Min,Max,b,ans);
            system("pause");
            if(Min>Max) break;

            a=S[Min];
            c=0;
            for(int i=Min+1;i<=Max;i++)
            {
                if(a<b) c=Max-i+1;
                a+=S[i];
            }
            //a+=S[Max];
            for(int i=Min;i<Max;i++)
            {
                if(a<b) c=Min-i-1;
                a-=S[i];
            }
            if(c<0) Min-=c;
            else if(c>0) Max-=c;
            else break;
            printf("%d %d %d %d\n",Min,Max,b,ans);
            system("pause");
            if(Min>Max) break;
        }
        printf("%d\n",sum-ans-ans);
    }
    return 0;
}
