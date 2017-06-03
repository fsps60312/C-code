#include<cstdio>
#include<cstdlib>
long long d,n,m,f[15][15],bas[15],ans;
void dopow(long long a)
{
	long long b[15][15],c[15][15];
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		{
			if(i==j) b[i][j]=1;
			else b[i][j]=0;
		}
	}
	while(a)
	{
		if(a&1)
		{
			//b*=f
			for(int i=0;i<d;i++)
			{
				for(int j=0;j<d;j++)
				{
					c[i][j]=0;
					for(int k=0;k<d;k++)
					{
						c[i][j]+=b[i][k]*f[k][j];
						c[i][j]%=m;
					}
				}
			}
			for(int i=0;i<d;i++)
			{
				for(int j=0;j<d;j++)
				{
					b[i][j]=c[i][j];
				}
			}
		}
		a>>=1;
		//f*=f
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<d;j++)
			{
				c[i][j]=0;
				for(int k=0;k<d;k++)
				{
					c[i][j]+=f[i][k]*f[k][j];
					c[i][j]%=m;
				}
			}
		}
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<d;j++)
			{
				f[i][j]=c[i][j];
			}
		}
	}
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		{
			f[i][j]=b[i][j];
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&d,&n,&m)==3)
	{
		if(d==0&&n==0&&m==0) break;
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<d;j++)
			{
				f[i][j]=0;
			}
		}
		for(int i=1;i<d;i++)
		{
			f[i][i-1]=1;
		}
		for(int i=0;i<d;i++)
		{
			scanf("%lld",&f[0][i]);
			f[0][i]%=m;
		}
		for(int i=0;i<d;i++)
		{
			scanf("%lld",&bas[d-i-1]);
			bas[i]%=m;
		}
		if(n<=d) printf("%lld\n",bas[n-1]>=0?bas[n-1]:bas[n-1]+m);
		else
		{
			dopow(n-d);
			ans=0;
			for(int i=0;i<d;i++)
			{
				ans+=f[0][i]*bas[i];
				ans%=m;
			}
			printf("%lld\n",ans>=0?ans:ans+m);
		}
	}
	return 0;
}
