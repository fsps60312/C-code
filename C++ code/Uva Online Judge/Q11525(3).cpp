#include<cstdio>
#include<cstdlib>
int T,K;
int ST[200000],TAG[200000];
void buildtree(int id,int l,int r)
{
    ST[id]=r-l+1;
    if(l==r)return;
    int mid=(l+r)/2;
    buildtree(id*2,l,mid);
    buildtree(id*2+1,mid+1,r);
}
int queryminus(int id,int l,int r,int rank)
{
    if(ST[id]<rank)return 0;
    ST[id]--;
    if(l==r)return l;
    int mid=(l+r)/2;
    int q=queryminus(id*2,l,mid,rank);
    return q?q:queryminus(id*2+1,mid+1,r,rank-ST[id*2]);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&K);
        buildtree(1,1,K);
        for(int i=0,j;i<K;i++)
        {
            if(i)printf(" ");
            scanf("%d",&j);
            printf("%d",queryminus(1,1,K,j+1));
        }
        printf("\n");
    }
    return 0;
}
