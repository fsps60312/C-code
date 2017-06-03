#include<cstdio>
#include<cstdlib>
int n;
int main()
{
    int T=0;
    while(scanf("%d",&n)==1)
    {
        int r=n*2-1;
        r*=r;
        int in=0,out=0;
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<n;j++)
            {
                int k=(i*i+j*j)*4;
                if(k<=r) in++;
                if(k>=r) out++;
            }
        }
        if(T++) printf("\n");
        //printf("%d %d\n",in,out);
        printf("In the case n = %d, %d cells contain segments of the circle.\n",n,(n*n-in-out)*4);
        printf("There are %d cells completely contained in the circle.\n",in*4);
    }
    return 0;
}
