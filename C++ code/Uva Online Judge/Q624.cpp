#include<cstdio>
#include<cstdlib>
int n,L,S[21],tmp[100000][22];
void dfsprint(int a,int b)
{
    if(a==0) return;
    dfsprint(a-tmp[a][b],b-1);
    printf("%d ",tmp[a][b]);
}
int main()
{
    while(scanf("%d",&L)==1)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",&S[i]);
        for(int i=0;i<=L;i++)
        {
            for(int j=0;j<22;j++)
            {
                tmp[i][j]=-1;
            }
        }
        tmp[0][0]=0;
        int Max=0,row=1;
        for(int i=0;i<n;i++)
        {
            for(int k=22;k>=1;k--)
            {
                for(int j=L;j>=S[i];j--)
                {
                    if(tmp[j-S[i]][k-1]>=0&&tmp[j][k]==-1)
                    {
                        tmp[j][k]=S[i];
                        if(j>Max) Max=j,row=k;
                    }
                }
            }
        }
        dfsprint(Max,row);
        printf("sum:%d\n",Max);
    }
    return 0;
}
