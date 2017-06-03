#include<cstdio>
#include<cstdlib>
int n,sum,S[10000],tmp[10000];
void range(int a,int b)
{
    if(a==b) return;
    int mid=(a+b)/2;
    range(a,mid);
    range(mid+1,b);
    int c=a,d=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(d>b||(c<=mid&&S[c]<S[d]))
        {
            tmp[i]=S[c];
            c++;
        }
        else
        {
            tmp[i]=S[d];
            d++;
        }
    }
    for(int i=a;i<=b;i++) S[i]=tmp[i];
}
bool serch(int a,int b)
{
    int Min=0,Max=n-1,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(S[mid]<a) Min=mid+1;
        else Max=mid;
    }
    if(Max==b)
    {
        if(Max>0&&a==S[Max-1]) return true;
        if(Max<n-1&&a==S[Max+1]) return true;
        return false;
    }
    return a==S[Max];
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=0;i<n;i++) scanf("%d",&S[i]);
        scanf("%d",&sum);
        range(0,n-1);
        int ans=0;
        for(int i=0;S[i]*2<=sum;i++)
        {
            if(serch(sum-S[i],i))
            {
                ans=i;
            }
        }
        printf("Peter should buy books whose prices are %d and %d.\n\n",S[ans],sum-S[ans]);
    }
    return 0;
}
