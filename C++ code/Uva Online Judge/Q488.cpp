#include<cstdio>
#include<cstdlib>
int T,a,b;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&a,&b);
        while(b--)//waves
        {
            for(int i=1;i<=a;i++)
            {
                for(int j=0;j<i;j++)
                {
                    printf("%d",i);
                }
                if(!(!T&&a==1&&!b)) printf("\n");
            }
            for(int i=a-1;i>0;i--)
            {
                for(int j=0;j<i;j++)
                {
                    printf("%d",i);
                }
                if(!(!T&&!b)||i>1) printf("\n");
            }
            if(T||b)
                printf("\n");
        }
        if(!T)
            printf("\n");
    }
}
