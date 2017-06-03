#include<cstdio>
#include<cstdlib>
long long T,a,b,c;
long long pow(long long x,long long y)
{
    long long ans=1%c;
    while(y)
    {
        if(y&1)
        {
            ans*=x;
            ans%=c;
        }
        x*=x;
        x%=c;
        y>>=1;
    }
    return ans;
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&a,&b,&c);
        printf("%lld\n",pow(a,b));
    }
    return 0;
}
