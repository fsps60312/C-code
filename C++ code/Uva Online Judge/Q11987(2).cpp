#include<cstdio>
#include<cstdlib>
int N,M;
int leader[200001],num[100001],sum[100001];
int findset(int a)
{
    if(leader[a]==a)return a;
    return leader[a]=findset(leader[a]);
}
int main()
{
    while(scanf("%d%d",&N,&M)==2)
    {
        for(int i=1;i<=N;i++)
        {
            leader[i]=N+i,sum[i]=i,num[i]=1;
            leader[N+i]=N+i;
        }
        while(M--)
        {
            int type;scanf("%d",&type);
            switch(type)
            {
                case 1:
                {
                    int a,b;
                    scanf("%d%d",&a,&b);
                    a=findset(a)-N,b=findset(b)-N;
                    if(a==b)break;
                    sum[a]+=sum[b],num[a]+=num[b];
                    num[b]=sum[b]=0;
                    leader[b+N]=a+N;
                }break;
                case 2:
                {
                    int a,b;
                    scanf("%d%d",&a,&b);
                    int ta=findset(a)-N;
                    b=findset(b)-N;
                    if(ta==b)break;
                    num[ta]--,num[b]++;
                    sum[ta]-=a,sum[b]+=a;
                    leader[a]=b+N;
                }break;
                case 3:
                {
                    int a;scanf("%d",&a);
                    a=findset(a)-N;
                    printf("%d %d\n",num[a],sum[a]);
                }break;
            }
            //for(int i=1;i<=N;i++)printf("now:%d %d %d\n",leader[i],num[i],sum[i]);
        }
    }
    return 0;
}
