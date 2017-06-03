#include<cstdio>
const int MAX=2000000;
int A[MAX],B[MAX],N,M,C,num=0;
int main()
{
    for(scanf("%d",&C);C--;)
    {
        scanf("%d%d",&N,&M);
        A[0]=B[0]=1;
        int i=0,j=0;
        while(A[i]<N)
        {
            i++;
            A[i]=B[i-1]+1;
            while(A[j+1]*M<A[i])j++;
            if(A[j]*M<A[i])B[i]=B[j]+A[i];
            else B[i]=A[i];
        }
        for(int k=0;k<=i;k++)printf(" %d",A[k]);puts("");
        printf("Case %d: ",++num);
        if(A[i]==N)
        {
            puts("lose");
            continue;
        }
        int ans;
        while(N)
        {
            if(N>=A[i])N-=A[i],ans=A[i];
            i--;
        }
        printf("%d\n",ans);
    }
    return 0;
}
