#include<cstdio>
#include<cstdlib>
int T,G,L,SA[50001],TARRAY[3][50001];
char S[50001];
void getsa()
{
    int cn=26;
    int i,*c=TARRAY[2],*x=TARRAY[0],*y=TARRAY[1];
    for(i=0;i<cn;i++)c[i]=0;
    for(i=0;i<L;i++)c[x[i]=S[i]-'a']++;
    for(i=1;i<cn;i++)c[i]+=c[i-1];
    for(i=L-1;i>=0;i--)SA[--c[x[i]]]=i;
    for(int k=1;k<=L;k<<=1)
    {
        int p=0;
        for(i=L-k;i<L;i++)y[p++]=i;
        for(i=0;i<L;i++)if(SA[i]>=k)y[p++]=SA[i]-k;
        for(i=0;i<cn;i++)c[i]=0;
        for(i=0;i<L;i++)c[x[i]]++;
        for(i=1;i<cn;i++)c[i]+=c[i-1];
        for(i=L-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
        p=0;y[SA[0]]=p++;
        for(i=1;i<L;i++)
        {
            y[SA[i]]=x[SA[i]]==x[SA[i-1]]&&((SA[i]+k<L&&SA[i-1]+k<L&&x[SA[i]+k]==x[SA[i-1]+k])||(SA[i]+k>=L&&SA[i-1]+k>=L))?p-1:p++;
        }
        if(p==L)break;
        cn=p;
        int *tx=x;x=y,y=tx;
    }
}
int RANK[50001],HEIGHT[50001];
void getheight()
{
    for(int i=0;i<L;i++)RANK[SA[i]]=i;
    for(int i=0,k=0,j;i<L;i++)
    {
        if(k)k--;
        if(!RANK[i])continue;
        j=SA[RANK[i]-1];
        while(S[i+k]&&S[j+k]&&S[i+k]==S[j+k])k++;
        HEIGHT[RANK[i]]=k;
    }
}
int GETH(int a,int b)
{
    int ans=HEIGHT[a];
    for(int i=a+1;i<=b;i++)
    {
        int j=HEIGHT[i];
        if(j<ans)ans=j;
    }
    return ans;
}
int calseg(int sp,int fp)
{
    int ans=0;
    for(int i=sp;i<=fp;i++)
    {
        for(int j=i;j<=fp;j++)
        {
            int k=SA[i-1]-SA[j];
            if(k<0)k=-k;
            k--;
            int h=GETH(i,j);
            if(G<=k&&G>=k-h+1)
            {
                //printf(" %d %d h=%d,(%d,%d)\n",SA[i-1],SA[j],h,i,j);
                ans++;
            }
        }
    }
    return ans;
}
int solve()
{
    int prei=1,ans=0;
    for(int i=1;;i++)
    {
        if(i==L||HEIGHT[i]==0)
        {
            if(prei==i){prei=i+1;continue;}
            ans+=calseg(prei,i-1);
            prei=i+1;
            if(i==L)return ans;
        }
    }
}
int main()
{
    scanf("%d",&T);
    int kase=1;
    while(T--)
    {
        scanf("%d%s",&G,S);
        L=-1;while(S[++L]);
        getsa();
        getheight();
        //for(int i=0;i<L;i++)printf(" %d",RANK[i]);printf("\n");
        //for(int i=0;i<L;i++)printf(" %d",SA[i]);printf("\n");
        //for(int i=0;i<L;i++)printf(" %d",HEIGHT[i]);printf("\n");
        printf("Case %d: %d\n",kase++,solve());
    }
    return 0;
}
