#include<cstdio>
#include<cstdlib>
struct pairtype
{
    double x;
    double a;
};
pairtype up[200];
pairtype down[200];
int n1,n2,n;
double upheight(double site)
{
    if(site<up[0].x||site>up[n1-1].x) return 0;
}
int addleft(double x,double y,double r)
{
    int Min=0,Max=n1,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(up[mid].x<x-r) Min=mid+1;
        else Max=mid;
    }
    int a=Min;//left point
    if(a==n1)
    {
        up[a].x=x-r;
        up[a].a=y+r;
        a++;
        up[a].x=x+r;
        up[a].a=y+r;
        n1=a+1;
        return a;
    }
    if(up[a].x==x-r||upheight(x-r)>=y+r)
    {
        if(up[a].a<y+r) up[a].a=y+r;
        return a;
    }
    for(int i=n;i>a;i--)
    {
        up[i]=up[i-1];
    }

}
void add(double x,double y,double r)//x index, max height, min height
{
    int Min=0,Max=n1,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(up[mid].x<x-r) Min=mid+1;
        else Max=mid;
    }
    int a=Min;//left point
    if(a==n1)
    {
        up[a].x=x-r;
        up[a].a=y+r;
        a++;
        up[a].x=x+r;
        up[a].a=y+r;
        n1=a+1;
        return;
    }
    if(up[a].x==x-r)
    {
        if(up[a].a<y+r) up[a].a=y+r;
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        n1=n2=0;
        for(int i=0;i<n;i++)
        {
            double x,y,r;
            scanf("%llf%llf%llf",&x,&y,&r);
            add(x,y,r);
        }
    }
    return 0;
}
