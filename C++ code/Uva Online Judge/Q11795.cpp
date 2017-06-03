#include<cstdio>
#include<cstdlib>
long long MegaBuster;
long long weapon[16];
long long n,Mxbit,T;
long long tmp[16][1<<16];//sum of method
long long power[16][1<<16];//robots can kill
int countbit(int a)
{
	//printf("%lld ",a);
    a=(a&0x55555555)+((a&0xaaaaaaaa)>>1);
    a=(a&0x33333333)+((a&0xcccccccc)>>2);
    a=(a&0x0f0f0f0f)+((a&0xf0f0f0f0)>>4);
    a=(a&0x00ff00ff)+((a&0xff00ff00)>>8);
    a=(a&0x0000ffff)+((a&0xffff0000)>>16);
    //printf("%lld\n",a);
    //system("pause");
    return a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%lld",&T);
    for(long long t=1;t<=T;t++)
    {
        scanf("%lld",&n);
        Mxbit=1<<n;
        MegaBuster=0;
        for(long long i=0;i<n;i++)
        {
        	char j;
            while(scanf("%c",&j)==1&&j!='0'&&j!='1');
            if(j=='1') MegaBuster|=1<<i;
        }
        //printf("pass\n");
        for(long long i=0;i<n;i++)
        {
            weapon[i]=0;
            for(long long j=0;j<n;j++)
            {
            	char k;
                while(scanf("%c",&k)==1&&k!='0'&&k!='1');
                if(k=='1') weapon[i]|=1<<j;
            }
        }
        for(long long i=0;i<n;i++)
        {
            for(long long j=0;j<Mxbit;j++)
            {
                tmp[i][j]=0;
                power[i][j]=0;
            }
            if(1<<i&MegaBuster)//can kill first
            {
                tmp[i][1<<i]=1;//weapon hold now
                power[i][1<<i]|=MegaBuster|weapon[i];
                //printf(" %lld\n",i);
            }
        }
        for(long long i=2;i<=n;i++)
        {
            for(int j=0;j<Mxbit;j++)
            {
                if(countbit(j)==i)//sum of killed robot
                {
                	//printf(" %lld\n",j);
                    for(long long k=0;k<n;k++)
                    {
                        if(1<<k&j)//possible weapon hold & robot now
                        {
                            for(long long l=0;l<n;l++)
                            {
                                if(l!=k&&(1<<l&j)&&(1<<k&power[l][j-(1<<k)]))//weapon hold before, which can kill this robot
                                {
                                    tmp[k][j]+=tmp[l][j-(1<<k)];
                                    power[k][j]|=power[l][j-(1<<k)]|weapon[k];
                                    //printf(" %#x %lld %lld %lld %lld\n",j,i,k,l,tmp[k][j]);
                                }
                            }
                        }
                    }
                }
            }
        }
        long long ans=0;
        for(long long i=0;i<n;i++)
        {
            ans+=tmp[i][Mxbit-1];
        }
        printf("Case %lld: %lld\n",t,ans);
    }
    return 0;
}
