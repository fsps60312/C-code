#include<cstdio>
#include<cstdlib>
struct pairtype
{
    int x;
    int y;
};
pairtype S[500000],tmp[500000];
int n;
bool vis[500000];
bool cmp(pairtype a,pairtype b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
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
bool hasmatch(pairtype a)
{
    int b=a.x;
    a.x=a.y;
    a.y=b;
    int Min=0,Max=n,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(cmp(S[mid],a)) Min=mid+1;
        else Max=mid;
    }
    if(a.x==S[Max].x&&a.y==S[Max].y)
    {
        for(int i=Max;a.x==S[i].x&&a.y==S[i].y;i++)
        {
            if(!vis[i])
            {
                vis[i]=true;
                return true;
            }
        }
        for(int i=Max-1;a.x==S[i].x&&a.y==S[i].y;i--)
        {
            if(!vis[i])
            {
                vis[i]=true;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&S[i].x,&S[i].y);
            vis[i]=false;
        }
        range(0,n-1);
        bool found=true;
        for(int i=0;i<n;i++)
        {
            if(!vis[i]&&!hasmatch(S[i]))
            {
                found=false;
                break;
            }
            vis[i]=true;
        }
        if(found) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
