#include<cstdio>
#include<cstdlib>
int T;
long long n,m,k,C[1001][1001],level[1001];
long long pow(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
			ans%=1000000007;
		}
		a*=a;
		a%=1000000007;
		b>>=1;
	}
	return ans%1000000007;
}
int main()
{
	level[0]=1;
	for(int i=1;i<=1000;i++)
	{
		level[i]=level[i-1]*i%1000000007;
		C[i][0]=1;
		for(int j=1;j<i;j++)
		{
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			C[i][j]%=1000000007;
		}
		C[i][i]=1;
	}
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		long long ans=C[m][k]*pow(n-k-1,m-k);
		ans%=1000000007;
		ans*=level[n-m];
		//C(m,k)*(n-k-1)^(m-k)*(n-m)!
		//C(m,k)*((n-k)!-C(n-k,1)(n-k-1)!+C(n-k,2)(n-k-2)!-...+-C(n-k,m-k)(n-m))
		//5,3,2
		//C(3,2)*(5-2-1)^(1)*(5-3)!==3*2*2==12
		printf("Case %d: %lld\n",kase,ans%1000000007);
	}
	return 0;
}
