#include<cstdio>
#include<cstdlib>
int T,K;
int BI[50001],maxbit;
int lowbit(int a){return a&(-a);}
void minus(int i)
{
    while(i<=K)
    {
        BI[i]--;
        i+=lowbit(i);
    }
}
int qindex(int r)
{
    int i=0,sum=0,now=maxbit;
    //printf("in\n");
    while(now)
    {
        //printf("now=%d\n",now);
        if((!BI[i+now]&&sum<r)||((i+now<=K)&&BI[i+now]&&(sum+BI[i+now]<=r)
           &&(now<=1||(BI[i+now]!=BI[i+(now>>1)])))){i+=now,sum+=BI[i];}
        now>>=1;
    }
    //printf("sum=%d r=%d\n",sum,r);
    //printf("b\n");
    return i;
}
int main()
{
    BI[0]=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&K);
        maxbit=1;while((maxbit<<1)<=K)maxbit<<=1;
        for(int i=1;i<=K;i++)BI[i]=lowbit(i);
        //for(int i=1;i<=K;i++)printf("BI=%d,sum=%d\n",BI[i],sum(i));
        for(int i=0,j;i<K;i++)
        {
            if(i)printf(" ");
            scanf("%d",&j);//j is rank
            j=qindex(j+1);//j become index
            printf("%d",j);
            minus(j);
        }
        printf("\n");
    }
    return 0;
}
