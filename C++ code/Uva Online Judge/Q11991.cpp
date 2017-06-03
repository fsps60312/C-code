#include<cstdio>
#include<cstdlib>
struct pairtype
{
    int index;
    int n;
};
pairtype S[1000000],tmp[1000000];
int n,m,k,v;
bool cmp(pairtype a,pairtype b)
{
    if(a.n!=b.n) return a.n<b.n;
    return a.index<b.index;
}
void range(int a,int b)
{
    if(a==b) return;
    int mid=(a+b)/2;
    range(a,mid);
    range(mid+1,b);
    int c=a,d=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(d>b||(c<=mid&&cmp(S[c],S[d])))
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
int seek(int b,int a)
{
    int Min=0,Max=n-1,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(S[mid].n<a) Min=mid+1;
        else Max=mid;
    }
    if(S[Max+b-1].n!=a) return 0;
    return S[Max+b-1].index;
}
int main()
{
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&S[i].n);
            S[i].index=i+1;
        }
        range(0,n-1);
        while(m--)
        {
            scanf("%d%d",&k,&v);
            printf("%d\n",seek(k,v));
        }
    }
    return 0;
}
