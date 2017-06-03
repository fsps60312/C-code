#include<cstdio>
#include<cstdlib>
int T,n;
int S[770][770];
int sum[770][770];
int square(int a,int b,int c,int d)
{
    return sum[c][d]+sum[a-1][b-1]-sum[a-1][d]-sum[c][b-1];
}
int main()
{
    //freopen("abc.txt","w",stdout);
    for(int i=0;i<770;i++)
    {
        sum[i][0]=sum[0][i]=S[i][0]=S[0][i]=0;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&S[i][j]);
            }
        }
        sum[1][1]=S[1][1];
        for(int i=2;i<=n;i++)
        {
            sum[i][1]=sum[i-1][1]+S[i][1];
            sum[1][i]=sum[1][i-1]+S[1][i];
        }
        for(int i=2;i<=n;i++)
        {
            for(int j=2;j<=n;j++)
            {
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+S[i][j];
            }
        }
        int ans=-200000000;
        //int now[4];
        for(int a=1;a<=n;a++)
        {
            for(int b=1;b<=n;b++)//from (a,b)
            {
                //sum[a][b]
                for(int c=1;c<a;c++)
                {
                    for(int d=1;d<b;d++)
                    {
                        int e=sum[c][d]+sum[n][d]-sum[a-1][d]+sum[c][n]-sum[c][b-1]+square(a,b,n,n);
                        if(e>ans) ans=e;//,now[0]=a,now[1]=b,now[2]=c,now[3]=d;
                    }
                    for(int d=b;d<=n;d++)
                    {
                        int e=square(a,b,n,d)+square(1,b,c,d);
                        if(e>ans) ans=e;//,now[0]=a,now[1]=b,now[2]=c,now[3]=d;
                    }
                }
                for(int c=a;c<=n;c++)
                {
                    for(int d=1;d<b;d++)
                    {
                        int e=square(a,b,c,n)+square(a,1,c,d);
                        if(e>ans) ans=e;//,now[0]=a,now[1]=b,now[2]=c,now[3]=d;
                    }
                    for(int d=b;d<=n;d++)//to (c,d)
                    {
                        int e=square(a,b,c,d);
                        if(e>ans) ans=e;//,now[0]=a,now[1]=b,now[2]=c,now[3]=d;
                    }
                }
            }
        }
        printf("%d\n",ans);

    }
    return 0;
}
