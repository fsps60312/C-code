#include<cstdio>
#include<cstdlib>
struct tmptype
{
    int a;
    int b;
};
tmptype tmp[10001][201],ans;
int T,ferry,S[201];
void dfsprint(int a,int b)
{
    if(b<=0) return;
    dfsprint(a-tmp[a][b].a,b-1);
    if(tmp[a][b].a==0) printf("port");
    else printf("starboard");
    if(T||b<ans.b) printf("\n");
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&ferry);
        ferry*=100;
        int sum=0,n=-1;
        do
        {
            n++;
            scanf("%d",&S[n]);
        }while(S[n]!=0);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=ferry;j++)
            {
                tmp[j][i].a=0;
                tmp[j][i].b=2147483647;
            }
        }
        tmp[0][0].a=tmp[0][0].b=0;
        ans.a=ans.b=0;
        for(int i=0;i<n;i++)
        {
            for(int j=ans.b+1;j>0;j--)
            {
                for(int k=ferry;k>=0;k--)
                {
                    if(tmp[k][j].b!=2147483647)
                    {
                        if(k>=S[i]&&tmp[k][j].b<tmp[k-S[i]][j-1].b)
                        {
                            tmp[k][j].a=S[i];
                            tmp[k][j].b=tmp[k-S[i]][j-1].b;
                            //printf("pass\n");
                            if(j>ans.b) ans.a=k,ans.b=j;
                        }
                        if(tmp[k][j-1].b+S[i]<=ferry&&tmp[k][j].b<tmp[k][j-1].b+S[i])
                        {
                            tmp[k][j].a=0;
                            tmp[k][j].b=tmp[k][j-1].b+S[i];
                            if(j>ans.b) ans.a=k,ans.b=j;
                        }
                    }
                }
            }
        }
        printf("%d\n",ans.b);
        dfsprint(ans.a,ans.b);

    }
    return 0;
}
