#include<cstdio>
#include<cstdlib>
int T,G,L,SA1[50001],SA2[50001],TARRAY[3][50001];
char S1[50001],S2[50001];
void buildsa(char *s,int *sa)
{
    int cn=26;
    int i,*c=TARRAY[2],*x=TARRAY[0],*y=TARRAY[1];
    for(i=0;i<cn;i++)c[i]=0;
    for(i=0;i<L;i++)c[x[i]=s[i]-'a']++;
    for(i=1;i<cn;i++)c[i]+=c[i-1];
    for(i=L-1;i>=0;i--)sa[--c[x[i]]]=i;
    for(int k=1;k<=L;k<<=1)
    {
        int p=0;
        for(i=L-k;i<L;i++)y[p++]=i;
        for(i=0;i<L;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
        for(i=0;i<cn;i++)c[i]=0;
        for(i=0;i<L;i++)c[x[i]]++;
        for(i=1;i<cn;i++)c[i]+=c[i-1];
        for(i=L-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        p=0;y[sa[0]]=p++;
        for(i=1;i<L;i++)
        {
            y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&((sa[i]+k<L&&sa[i-1]+k<L&&x[sa[i]+k]==x[sa[i-1]+k])||(sa[i]+k>=L&&sa[i-1]+k>=L))?p-1:p++;
        }
        if(p==L)break;
        cn=p;
        int *tx=x;x=y,y=tx;
    }
}
int R1[50001],R2[50001],H1[50001],H2[50001];
void buildheight(int *sa,int *r,int *h,char *s)
{
    for(int i=0;i<L;i++)r[sa[i]]=i;
    for(int i=0,k=0,j;i<L;i++)
    {
        if(k)k--;
        if(!r[i])continue;
        j=sa[r[i]-1];
        while(s[i+k]==s[j+k])k++;
        h[r[i]]=k;
    }
}
int RMQ1[50001][17],RMQ2[50001][17];
int min(int a,int b){return a<b?a:b;}
void buildrmq(int *h,int r[][17])
{
    for(int i=1;i<L;i++)r[i][0]=h[i];
    for(int i=1;(1<<i)<L;i++)
    {
        for(int j=1;j+(1<<i)<=L;j++)
        {
            r[j][i]=min(r[j][i-1],r[j+(1<<(i-1))][i-1]);
        }
    }
}
int getH(int r[][17],int *rank,int a,int b)
{
    a=rank[a],b=rank[b];
    if(a>b){int c=a;a=b,b=c;}
    a++;
    int d=0;
    while((1<<(d+1))<=b-a+1)d++;
    return min(r[a][d],r[b-(1<<d)+1][d]);
}
int solve()
{
    int ans=0;
    for(int l=1;l<L;l++)
    {
        for(int i=0;i+l+G<L;i+=l)
        {
            int rlcp=getH(RMQ1,R1,i,i+l+G);
            int llcp=getH(RMQ2,R2,L-1-(i+l+G),L-1-i);
            int k=llcp+rlcp;
            if(S1[i]==S1[i+l+G])k--,i+=rlcp-1;
            if(k>=l)ans+=k-l+1;
        }
    }
    return ans;
}
int main()
{
    scanf("%d",&T);
    int kase=1;
    while(T--)
    {
        scanf("%d%s",&G,S1);
        L=-1;while(S1[++L]);
        for(int i=0;i<L;i++)S2[i]=S1[L-1-i];S2[L]=0;
        buildsa(S1,SA1);
        buildsa(S2,SA2);
        buildheight(SA1,R1,H1,S1);
        buildheight(SA2,R2,H2,S2);
        buildrmq(H1,RMQ1);
        buildrmq(H2,RMQ2);
        printf("Case %d: %d\n",kase++,solve());
    }
    return 0;
}
