#include<cstdio>
#include<cstdlib>
long long f[31][31],n,ans[31];
long long C(long long a,long long b)
{
	double ans=1;
	for(int i=0;i<b;i++) ans*=(a-i);
	for(int i=1;i<=b;i++) ans/=i;
	return (long long)(ans+0.5);
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	for(int i=0;i<=30;i++)
	{
		f[i][0]=1;
	}
	for(int i=1;i<=30;i++)
	{
		f[i][1]=1;
		f[0][i]=0;
	}
	ans[1]=1;
	for(int i=1;i<=30;i++)//max tree
	{
		for(int j=2;j<=30;j++)//total leaf
		{
			f[i][j]=0;
			for(int k=0;k*i<=j;k++)
			{
				f[i][j]+=f[i-1][j-k*i]*C(ans[i]+k-1,k);
			}
		}
		ans[i+1]=f[i][i+1];
	}
	while(scanf("%lld",&n)==1)
	{
		if(n==0) break;
		printf("%lld\n",n==1?1:ans[n]*2);
	}
	return 0;
}
