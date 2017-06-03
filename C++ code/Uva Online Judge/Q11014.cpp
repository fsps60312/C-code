#include<cstdio>
#include<cstdlib>
typedef long long LL;
LL A[200001],Asum[200001];//A[i]:how many i>=x>=y make gcd(i,x,y)==1
//if(i is prime)
//	A[i]==i*i-1;
//	A[i^n]==i^n*i^n-i^(n-1)*i^(n-1);
//if(i co-prime j)
//	(X)A[i*j]==|{x|x<i*j&&x co-prime i}|*|{x|x<i*j&&x co-prime j}|==phi[i]*j*phi[j]*i
//	A[i*j]==A[i]*A[j]
//	(X)A[i*j]==(phi[i]*j+phi[j]*i)*2
LL phi[200001],phisum[200001];
LL n;
int main()
{
	for(LL i=0;i<=200000;i++)
	{
		phi[i]=0;
		A[i]=0;
	}
	phi[1]=A[1]=1;
	for(LL i=2;i<=200000;i++)
	{
		if(!phi[i])
		{
			for(LL j=i;j<=200000;j+=i)
			{
				if(!phi[j]) phi[j]=j,A[j]=j*j;
				phi[j]=phi[j]/i*(i-1);
				A[j]=A[j]/(i*i)*(i*i-1);
			}
		}
	}
	phisum[0]=Asum[0]=0;
	for(LL i=1;i<=200000;i++)
	{
		phisum[i]=phisum[i-1]+phi[i];
		Asum[i]=Asum[i-1]+A[i];
	}
	//for(LL i=0;i<=100;i++) printf("%lld\t%lld\t%lld\n",i,phi[i],A[i]);
	LL kase=1;
	while(scanf("%lld",&n)==1&&n)
	{
		n>>=1;
		LL ans=Asum[n]*24-phisum[n]*24+phisum[n]*4*6+2;//-8+12-6
		printf("Crystal %lld: %lld\n",kase++,ans);
	}
	return 0;
}
