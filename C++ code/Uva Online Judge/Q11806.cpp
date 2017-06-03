#include<cstdio>
#include<cstdlib>
long long T,n,m,k;
long long C[401][201];
long long c(long long a,long long b)
{
	//if(a<=0) return 0;
	if(b>a) return 0;
	if(b>a/2) b=a-b;
	return C[a][b];
}
long long mod(long long a)
{
	//return a;
	a%=1000007;
	return a>=0?a:a+1000007;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(long long i=1;i<=400;i++)
	{
		C[i][0]=1;
		for(long long j=1;j<=i/2;j++)
		{
			C[i][j]=c(i-1,j)+c(i-1,j-1);
			C[i][j]%=1000007;
		}
	}
	/*for(int i=0;i<=10;i++)
	{
		for(int j=0;j<=10;j++)
		{
			printf(" %lld",C[i][j]);
		}
		printf("\n");
	}*/
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		printf("Case %d: %lld\n",t,mod(c(m*n,k)-2*c(m*(n-1),k)-2*c((m-1)*n,k)+4*c((m-1)*(n-1),k)+c((m-2)*n,k)+c((n-2)*m,k)-2*c((m-2)*(n-1),k)-2*c((m-1)*(n-2),k)+c((m-2)*(n-2),k)));
	}
	return 0;
}
