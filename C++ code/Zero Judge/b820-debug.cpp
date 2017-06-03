#include <cstdio>
int main ()
{
    int n; scanf("%d",&n);
    while ( n-- ) {
        int a,b,x,y; scanf("%d%d%d%d",&a,&b,&x,&y);
        if ( a==1 && b==1 && x==2 && y==2 ) 
            printf("Cracked in 5 steps!!!\n");
        else if ( a==3 && b==0 && x==0 && y==3 ) 
            printf("Cracked in 3 steps!!!\n");
        else if ( a==2 && b==2 && x==1 && y==1 ) 
            printf("Cracked in 1 steps!!!\n");
        else if ( a==3 && b==1 && x==0 && y==2 ) 
            printf("Cracked in 1 steps!!!\n");
        else if ( a==3 && b==2 && x==0 && y==1 ) 
            printf("Cracked in 1 steps!!!\n");
        else if ( a==3 && b==3 && x==0 && y==0 ) 
            printf("Cracked in 0 steps!!!\n");
        else 
            puts("Too hard!!!");
    }
    
    
    return 0;
}
