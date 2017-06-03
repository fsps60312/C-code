#include<cstdio>
#include<cstdlib>
using namespace std;
long long n,m;
long long S[40][20];
long long tmp[40][20][500];//row, column, sum of sum
bool ptr[40][20][500][2];//0:L 1:R
bool ans[40][20][500][2];//0:-- 1:++
void dfs(long long a,long long b,long long c,long long d)
{
    //printf(" %lld %lld %lld %lld %lld %lld %lld\n",a,b,c,d,S[a][b],ptr[a][b][c][0],ptr[a][b][c][1]);
    if(ans[a][b][c][d]) return;
    ans[a][b][c][d]=true;
    //printf(" %lld %lld %lld %lld ans=%lld\n",a,b,c,d,ans[a][b][c][d]);
    if(a<1) return;
    if(a>n)//0
    {
        if(ptr[a][b][c][0])
        {
        	//printf(" 0pass\n");
            dfs(a-1,b-1,c-S[a][b],0);
        }
        if(ptr[a][b][c][1])
        {
        	//printf(" 1pass\n");
            dfs(a-1,b,c-S[a][b],1);
        }
    }
    else
    {
        if(ptr[a][b][c][0])
        {
            dfs(a-1,b,c-S[a][b],0);
        }
        if(ptr[a][b][c][1])
        {
            dfs(a-1,b+1,c-S[a][b],1);
        }
    }
}
void showpath(long long a,long long b,long long c)
{
    //printf(" %lld %lld %lld %lld %lld\n",a,b,c,ans[a][b][c][0],ans[a][b][c][1]);
    if(a==n*2-1) return;
    if(a<n)
    {
        if(ans[a][b][c][1])//
        {
            printf("L");
            showpath(a+1,b-1,c+S[a+1][b-1]);
        }
        else
        {
            printf("R");
            showpath(a+1,b,c+S[a+1][b]);
        }
    }
    else
    {
        if(ans[a][b][c][1])
        {
            printf("L");
            showpath(a+1,b,c+S[a+1][b]);
        }
        else
        {
            printf("R");
            showpath(a+1,b+1,c+S[a+1][b+1]);
        }
    }
}
int main()
{
    while(scanf("%lld%lld",&n,&m)==2)
    {
        if(n==m&&m==0) break;
        for(long long i=1;i<n;i++)
        {
            for(long long j=0;j<=n-i;j++)
            {
                scanf("%lld",&S[i][j]);
            }
        }
        for(long long i=n;i<n*2;i++)
        {
            for(long long j=0;j<=i-n;j++)
            {
                scanf("%lld",&S[i][j]);
            }
        }
        for(long long i=0;i<n*2;i++)
        {
            for(long long j=0;j<n;j++)
            {
                for(long long k=0;k<500;k++)
                {
                    tmp[i][j][k]=0;
                    ptr[i][j][k][0]=ptr[i][j][k][1]=false;
                }
            }
        }
        /*for(long long i=0;i<n*2;i++)
        {
        	for(long long j=0;j<n;j++)
        	{
        		printf(" %lld",S[i][j]);
        	}
        	printf("\n");
        }printf("\n");*/
        for(long long i=0;i<n;i++)
        {
            tmp[1][i][S[1][i]]++;//start point
        }
        for(long long i=2;i<=n;i++)
        {
            for(long long j=0;j<=n-i;j++)
            {
                for(long long k=S[i][j];k<500;k++)
                {
                    if(tmp[i-1][j][k-S[i][j]])
                    {
                        ptr[i][j][k][0]=true;
                        tmp[i][j][k]+=tmp[i-1][j][k-S[i][j]];
                    }
                    if(tmp[i-1][j+1][k-S[i][j]])
                    {
                        ptr[i][j][k][1]=true;
                        tmp[i][j][k]+=tmp[i-1][j+1][k-S[i][j]];
                    }
                }
            }
        }
        for(long long i=n+1;i<n*2;i++)
        {
            for(long long j=0;j<=i-n;j++)
            {
                for(long long k=S[i][j];k<500;k++)
                {
                    if(j>0&&tmp[i-1][j-1][k-S[i][j]])
                    {
                        ptr[i][j][k][0]=true;
                        tmp[i][j][k]+=tmp[i-1][j-1][k-S[i][j]];
                    }
                    if(j<i-n&&tmp[i-1][j][k-S[i][j]])
                    {
                        ptr[i][j][k][1]=true;
                        tmp[i][j][k]+=tmp[i-1][j][k-S[i][j]];
                    }
                }
            }
        }
        /*for(long long i=0;i<n*2;i++)
        {
        	for(long long j=0;j<n;j++)
        	{
        		for(long long k=0;k<500;k++)
        		{
        			if(tmp[i][j][k]) printf(" %lld",k);
        		}
        		printf(",");
        	}
        	printf("\n");
        }*/
        long long Ans=0;
        for(long long i=0;i<n;i++)
        {
            Ans+=tmp[n*2-1][i][m];
        }
        printf("%lld\n",Ans);
        if(Ans>0)
        {
            for(long long i=0;i<n*2;i++)
            {
                for(long long j=0;j<n;j++)
                {
                    for(long long k=0;k<500;k++)
                    {
                        ans[i][j][k][0]=ans[i][j][k][1]=false;
                    }
                }
            }
            for(long long i=0;i<n;i++)
            {
                //printf(" %lld %lld %lld\n",i,S[n*2-1][i],tmp[n*2-1][i][m]);
                if(tmp[n*2-1][i][m])
                {
                    if(ptr[n*2-1][i][m][0]) dfs(n*2-2,i-1,m-S[n*2-1][i],0);
                    if(ptr[n*2-1][i][m][1]) dfs(n*2-2,i,m-S[n*2-1][i],1);
                }
            }
            for(long long i=0;i<n;i++)
            {
                //printf(" %lld %lld %lld\n",n,ans[1][i][S[1][i]][0],ans[1][i][S[1][i]][1]);
                if(ans[1][i][S[1][i]][0]||ans[1][i][S[1][i]][1])
                {
                    printf("%lld ",i);
                    showpath(1,i,S[1][i]);
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
