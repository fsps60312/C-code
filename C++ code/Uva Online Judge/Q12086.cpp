#include<cstdio>
#include<cstdlib>
int N,S[200001],BI[200001];
int lowbit(int a){return a&(-a);}
int sum(int i)
{
    int ans=0;
    while(i)
    {
        ans+=BI[i];
        i-=lowbit(i);
    }
    return ans;
}
int getv(int i){return sum(i)-sum(i-1);}
void addv(int i,int v)
{
    while(i<=N)
    {
        BI[i]+=v;
        i+=lowbit(i);
    }
}
void change(int i,int v){addv(i,v-getv(i));}
int main()
{
    int kase=0;
    while(scanf("%d",&N)==1&&N)
    {
        if(kase)printf("\n");
        printf("Case %d:\n",++kase);
        BI[0]=0;
        for(int i=1;i<=N;i++){scanf("%d",&S[i]);BI[i]=0;}
        for(int i=1;i<=N;i++)addv(i,S[i]);
        char tstr[4];bool isend=false;
        while(!isend&&scanf("%s",tstr)==1)
        {
            switch(tstr[0])
            {
                case'S':
                {
                    int x,r;scanf("%d%d",&x,&r);
                    change(x,r);
                }break;
                case'M':
                {
                    int x,y;scanf("%d%d",&x,&y);
                    printf("%d\n",sum(y)-sum(x-1));
                }break;
                default:
                {isend=true;}
                break;
            }
        }
    }
    return 0;
}
