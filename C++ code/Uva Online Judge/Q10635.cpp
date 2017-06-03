#include<cstdio>
#include<cstdlib>
const int themaxn=62505;
int T,n,p,q,S1[themaxn],S2[themaxn],index[themaxn],tmp[themaxn],tm[themaxn];
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d%d%d",&n,&p,&q);
        for(int i=0;i<=n*n;i++)
        {
            index[i]=-1;
        }
        scanf("%d",&S1[0]);
        for(int i=0;i<p;i++)
        {
            scanf("%d",&S1[i]);
            index[S1[i]]=i;
        }
        scanf("%d",&S2[0]);
        int tmpn=0;
        for(int i=0;i<q;i++)
        {
            scanf("%d",&S2[i]);
            if(index[S2[i]]!=-1)
            {
                tmp[tmpn]=index[S2[i]];
                tmpn++;
            }
        }
        //for(int i=0;i<tmpn;i++) printf("%d ",tmp[i]); printf("\n");
        //printf(" %d\n",tmpn);
        tm[0]=tmp[0],tm[1]=2147483647;
        int tmn=1;
        for(int i=1;i<tmpn;i++)
        {
            int Min=0,Max=tmn,Mid;
            while(Min<Max)
            {
                Mid=(Min+Max)/2;
                //printf("%d %d %d\n",Min,Mid,Max);
                if(tmp[i]>tm[Mid]) Min=Mid+1;
                else Max=Mid;
            }
            //printf("%d\n",i);
            Mid=(Min+Max)/2;
            //if(Max<Min) Mid++;
            tm[Mid]=tmp[i];
            if(Mid==tmn)
            {
                tmn++;
                tm[tmn]=2147483647;
            }
        }
        //for(int i=0;i<tmn;i++) printf("%d ",tm[i]); printf("\n");
        printf("Case %d: %d\n",t,tmn+1);
    }
    return 0;
}
