#include<cstdio>
#include<cstdlib>
struct pairtype
{
    long long n;
    long long ptr;
    long long now;
    long long index;
    void findmin(pairtype a,pairtype b,pairtype c)
    {
        now=a.now;
        ptr=a.index;
        if(b.now<now)
        {
            now=b.now;
            ptr=b.index;
        }
        if(c.now<now)
        {
            now=c.now;
            ptr=c.index;
        }
        now+=n;
    }
};
long long m,n;
pairtype S[10][100];
void showans(long long a,long long b)
{
    if(b==n) return;
    if(b>0) printf(" ");
    printf("%lld",S[a][b].index+1);
    showans(S[a][b].ptr,b+1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    while(scanf("%lld%lld",&m,&n)==2)
    {
        for(long long i=0;i<m;i++)
        {
            for(long long j=0;j<n;j++)
            {
                scanf("%lld",&S[i][j].n);
                S[i][j].index=i;
            }
        }
        /*for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++) printf(" %lld",S[i][j].n);printf("\n");
        }printf("\n");*/
        for(long long j=0;j<m;j++)
        {
            S[j][n-1].now=S[j][n-1].n;
        }
        //printf("%lld\n",9223372036854775807);
        for(long long i=n-2;i>=0;i--)
        {
            for(long long j=1;j<m-1;j++)
            {
                S[j][i].findmin(S[j-1][i+1],S[j][i+1],S[j+1][i+1]);
            }
            if(m>=2)
            {
                S[0][i].findmin(S[0][i+1],S[1][i+1],S[m-1][i+1]);
                S[m-1][i].findmin(S[0][i+1],S[m-2][i+1],S[m-1][i+1]);
            }
            else
            {
                S[0][i].now=S[0][i+1].now+S[0][i].n;
                S[0][i].ptr=0;
            }
        }
        long long a1=0;
        for(int i=1;i<m;i++)
        {
            if(S[i][0].now<S[a1][0].now)
            {
                a1=i;
            }
        }
        /*for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++) printf(" %lld",S[i][j].now);printf("\n");
        }printf("\n");*/
        showans(a1,0);printf("\n");
        printf("%lld\n",S[a1][0].now);
    }
    return 0;
}
