#include<cstdio>
typedef long long LL;
LL func(int n,int m)
{
    LL result=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(i!=j)result+=(LL)(n%i)*(m%j);
            //(n-n/i*i)(m-m/j*j)
            //n*m-n(m/j*j)-m(n/i*i)+(n/i*i)(m/j*j)
            
    return result;
}
int main()
{
//	for(LL i=1;i<=100;i++)
//	{
//		LL ans=0;
//		for(LL j=1;j<=i;j++)ans+=i%j;
//		printf("%-4lld:%lld\n",i,ans);
//	}
	for(int i=1;i<100;i++)printf("func(%d,%d)=%lld\n",i,i,func(i,i));
	return 0;
}
