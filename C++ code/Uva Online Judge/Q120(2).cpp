#include<cstdio>
#include<cstdlib>
char tmp[1000];
int S[100],n;
bool isnumber(char a)
{
    return a>='0'&&a<='9';
}
void show(int a)
{
    if(a!=1) printf("%d ",n-a);
}
void serch(int a)
{
    if(a==0) return;
    for(int i=1;i<a;i++)
    {
        if(S[i]==a)
        {
            show(i);
            show(a);
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
    while(gets(tmp))
    {
        n=0;
        int now=-1;
        while(tmp[++now]&&!isnumber(tmp[now]));
        while(sscanf(tmp+now,"%d",&S[++n])==1)
        {
            while(tmp[++now]&&isnumber(tmp[now]));
            while(tmp[++now]&&!isnumber(tmp[now]));
        }
        if(n>1) printf("%d",S[1]);
        for(int i=2;i<n;i++) printf(" %d",S[i]);
        printf("\n");
        serch(n);
        printf("0\n");
    }
    return 0;
}
