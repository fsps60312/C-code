#include<cstdio>
#include<cstdlib>
int T;
long long n,m,k,C[1001][1001],level[1001];
int main()
{
	level[0]=1;
	C[0][0]=1;
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
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		long long ans=0;
		for(int i=0;i<=m-k;i++)
		{
			if(i&1)
			{
				ans-=C[m-k][i]*level[n-k-i]%1000000007;
			}
			else
			{
				ans+=C[m-k][i]*level[n-k-i]%1000000007;
			}
			ans%=1000000007;
		}
		//C(m,k)*(C(n-k,m-k)(n-m)!-C(n-k,m-k+1)(n-m-1)!+...+-C(n-k,n-k)(0)!)
		//((n-k)!-C(m-k,1)(n-k-1)!+C(m-k,2)(n-k-2)...+-C(m-k,m-k)(n-m)!)
		//5,3,2
		//C(3,2)*(C(3,1)2!-C(3,2)1!+C(3,3)0!)=3*(6-3+1)=12
		ans*=C[m][k];
		ans=ans%1000000007+1000000007;
		printf("Case %d: %lld\n",kase,ans%1000000007);
	}
	return 0;
}
