#include<cstdio>
#include<cstdlib>
struct pairtype
{
    int n;
    int r;
    int index;
};
char tmp[1000];
pairtype S[30];
int n;
bool isnumber(char a)
{
    return a>='0'&&a<='9';
}
void serch(int a)
{
    if(a==0) return;
    //printf("\n");for(int i=0;i<n;i++) printf("%d ",S[i].r);printf("\n");
    for(int i=0;i<a;i++)
    {
        if(S[i].r==a)
        {
            if(i!=0) printf("%d ",n-i);
            printf("%d ",n-a);
            for(int j=0,k;j<=i/2;j++)
            {
                k=S[j].r;
                S[j].r=S[i-j].r;
                S[i-j].r=k;
            }
            for(int j=0,k;j<=a/2;j++)
            {
                k=S[j].r;
                S[j].r=S[a-j].r;
                S[a-j].r=k;
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
        //printf("%s\n",tmp);
        n=-1;
        //printf(" %d",n);
        int no=-1;
        while(tmp[++no]&&!isnumber(tmp[no]));
        while(sscanf(tmp+no,"%d",&S[++n].n)==1)
        {
            S[n].index=n;
            while(tmp[++no]&&isnumber(tmp[no]));
            if(tmp[no])
            {
                while(tmp[++no]&&!isnumber(tmp[no]));
            }
        }
        //printf(" %d\n",n);
        printf("%d",S[0].n);
        for(int i=1;i<n;i++) printf(" %d",S[i].n);printf("\n");
        for(int i=0;i<n;i++)
        {
            int k=0;
            for(int j=1;j<n;j++)
            {
                if(S[j].n<S[k].n) k=j;
            }
            S[k].n=2147483647;
            S[k].r=i;
        }
        serch(n-1);
        printf("0\n");
    }
    return 0;
}
