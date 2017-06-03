#include<cstdio>
#include<cstdlib>
struct dolltype
{
    int h;
    int w;
};
dolltype S[20001],tmp[20001],H[20001];
bool visited[20001];
int T,n;
void range1(int a,int b)
{
    if(a==b) return;
    if(a+1==b&&(S[a].h>S[b].h||(S[a].h==S[b].h&&S[a].w>S[b].w)))
    {
        dolltype c=S[a];
        S[a]=S[b];
        S[b]=c;
        return;
    }
    int mid=(a+b)/2;
    range1(a,mid);
    range1(mid+1,b);
    int d=a,e=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(e>b||(d<=mid&&(S[d].h<S[e].h||(S[d].h==S[e].h&&S[d].w<S[e].w))))
        {
            tmp[i]=S[d];
            d++;
        }
        else
        {
            tmp[i]=S[e];
            e++;
        }
    }
    for(int i=a;i<=b;i++)
    {
        S[i]=tmp[i];
    }
}
void range2(int a,int b)
{
    if(a==b) return;
    if(a+1==b&&(H[a].w>H[b].w||(H[a].w==H[b].w&&H[a].w>H[b].w)))
    {
        dolltype c=H[a];
        H[a]=H[b];
        H[b]=c;
        return;
    }
    int mid=(a+b)/2;
    range2(a,mid);
    range2(mid+1,b);
    int d=a,e=mid+1;
    for(int i=a;i<=b;i++)
    {
        if(e>b||(d<=mid&&(H[d].w<H[e].w||(H[d].w==H[e].w&&H[d].w<H[e].w))))
        {
            tmp[i]=H[d];
            d++;
        }
        else
        {
            tmp[i]=H[e];
            e++;
        }
    }
    for(int i=a;i<=b;i++)
    {
        H[i]=tmp[i];
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&S[i].h,&S[i].w);
            H[i]=S[i];
        }
        range1(0,n-1);
        range2(0,n-1);
        for(int i=0;i<n;i++) visited[i]=false;
        for(int i=n-1;i>=0;i--)
        {
            if(!visited[i])
            {
                visited[i]=true;
            }
        }
    }
    return 0;
}
