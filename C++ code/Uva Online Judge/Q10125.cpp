#include<cstdio>
#include<cstdlib>
struct pairtype
{
    int x;
    int y;
    int s;
};
int S[1000],tmpS[1000],maxs,n;
pairtype sum[1000000],tmpsum[1000000];
bool cmp(pairtype a,pairtype b)
{
    if(a.s!=b.s) return a.s<b.s;
    if(a.y!=b.y) return a.y<b.y;
    return a.x<b.x;
}
void rangesum(int a,int b)
{
    if(a==b) return;
    int mid=(a+b)/2;
    rangesum(a,mid);
    rangesum(mid+1,b);
    int c=a,d=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(d>b||(c<=mid&&cmp(sum[c],sum[d])))
        {
            tmpsum[i]=sum[c];
            c++;
        }
        else
        {
            tmpsum[i]=sum[d];
            d++;
        }
    }
    for(int i=a;i<=b;i++) sum[i]=tmpsum[i];
}
void rangeS(int a,int b)
{
    if(a==b) return;
    int mid=(a+b)/2;
    rangeS(a,mid);
    rangeS(mid+1,b);
    int c=a,d=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(d>b||(c<=mid&&S[c]<S[d]))
        {
            tmpS[i]=S[c];
            c++;
        }
        else
        {
            tmpS[i]=S[d];
            d++;
        }
    }
    for(int i=a;i<=b;i++) S[i]=tmpS[i];
}
bool contains(pairtype a)//x:small not-contain, y:large not-contain, s:value
{
    int Min=0,Max=maxs-1,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(sum[mid].s<a.s) Min=mid+1;
        else Max=mid;
    }
    //printf("%d\n",Max);
    if(sum[Max].s!=a.s) return false;
    for(int i=Max;i<maxs&&sum[i].s==a.s;i++)
    {
        if(a.x!=sum[i].x&&a.x!=sum[i].y&&a.y!=sum[i].x&&a.y!=sum[i].y) return true;
    }
    return false;
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++) scanf("%d",&S[i]);
        rangeS(0,n-1);
        for(int i=1;i<n;i++)
        {
            for(int j=0;j<i;j++)
            {
                int k=j+i*(i-1)/2;
                sum[k].x=j;
                sum[k].y=i;
                sum[k].s=S[j]+S[i];
            }
        }
        maxs=(n-1)*(n-2)/2+n-1;
        rangesum(0,maxs-1);
        //for(int i=0;i<maxs;i++) printf(" %d %d %d\n",sum[i].s,sum[i].y,sum[i].x);
        bool found=false;
        int ans=-1;
        for(int i=n-1;!found&&i>=0;i--)
        {
            for(int j=0;!found&&j<n;j++)
            {
                if(j==i) continue;
                pairtype k;
                k.x=j;
                k.y=i;
                k.s=S[i]-S[j];
                //printf("%d %d %d %d\n",k.x,k.y,k.s,contains(k));
                if(contains(k)) found=true,ans=S[i];
            }
        }
        if(found) printf("%d\n",ans);
        else printf("no solution\n");
    }
    return 0;
}
