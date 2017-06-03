#include<cstdio>
#include<cstdlib>
int T,m,n,k;
long long cs[401][401];
long long C(long long a,long long b)
{
	if(a<0||b>a) return 0;
	if(a==b||b==0) return 1;
	if(cs[a][b]!=-1) return cs[a][b];
	return cs[a][b]=(C(a-1,b-1)+C(a-1,b))%1000007;
}
int main()
{
	for(int i=0;i<=400;i++)
	{
		for(int j=0;j<=400;j++)
		{
			cs[i][j]=-1;
		}
	}
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d",&m,&n,&k);
		long long ans=0;
		for(int i=0;i<16;i++)
		{
			int a=m,b=n,c=0;
			if(i&(1)) a--,c++;
			if(i&(1<<1)) a--,c++;
			if(i&(1<<2)) b--,c++;
			if(i&(1<<3)) b--,c++;
			if(c%2)
			{
				ans-=C(a*b,k);
			}
			else
			{
				ans+=C(a*b,k);
			}
			//printf("%lld\n",ans);
		}
		ans%=1000007;
		if(ans<0) ans+=1000007;
		printf("Case %d: %lld\n",kase,ans);
	}
	return 0;
}
