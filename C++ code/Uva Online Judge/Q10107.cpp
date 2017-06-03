#include<cstdio>
#include<cstdlib>
int S[10000],tmp,n;
void add(int a)
{
    int Min=0,Max=n,mid;
    while(Min<Max)
    {
        mid=(Min+Max)/2;
        if(S[mid]<a) Min=mid+1;
        else Max=mid;
    }
    for(int i=n;i>=Max;i--) S[i+1]=S[i];
    S[Max]=a;
}
int main()
{
    n=0;
    while(scanf("%d",&tmp)==1)
    {
        add(tmp);
        n++;
        //for(int i=0;i<n;i++) printf(" %d",S[i]);printf("\n");
        if(n%2) printf("%d\n",S[n/2]);
        else printf("%d\n",(S[n/2]+S[n/2-1])/2);
    }
    return 0;
}
