#include<cstdio>
#include<cstdlib>
char c;
int S[31],n;
void serch(int a)
{
    if(a==0) return;
    for(int i=1;i<a;i++)
    {
        if(S[i]==a)
        {
            if(i!=1) printf("%d ",n-i+1);
            printf("%d ",n-a+1);
            for(int j=0,k;j<i/2;j++)
            {
                k=S[j+1];
                S[j+1]=S[i-j];
                S[i-j]=k;
            }
            for(int j=0,k;j<a/2;j++)
            {
                k=S[j+1];
                S[j+1]=S[a-j];
                S[a-j]=k;
            }
            break;
        }
    }
    serch(a-1);
}
int main()
{
    n=0;
    while(scanf("%d%c",&S[++n],&c)==2)
    {
        if(c=='\n')
        {
            printf("%d",S[1]);
            for(int i=2;i<=n;i++) printf(" %d",S[i]);printf("\n");
            serch(n);
            printf("0\n");
            n=0;
        }
    }
    return 0;
}
