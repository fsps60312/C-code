#include<cstdio>
#include<cstdlib>
long long d,n,m,Ans,bas[15],f[15][15];//column, row
void dopow(long long a)
{
	long long ans[d][d],tmp[d][d];
	for(long long i=0;i<d;i++)
	{
		for(long long j=0;j<d;j++)
		{
			ans[i][j]=(i==j?1:0);
		}
	}
	/*for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		{
			printf(" %lld",ans[j][i]);
		}
		printf("\n");
	}*/
	//long long now=1,pow=0;
	while(a)
	{
		//printf("%lld\n",a);
		if(a&1)
		{
			//ans*=f
			//pow+=now;
			//printf("%lld\n",pow);
			for(long long i=0;i<d;i++)
			{
				for(long long j=0;j<d;j++)//calculate ans[i][j]
				{
					tmp[i][j]=0;
					for(long long k=0;k<d;k++)//sum ans[k][j]*f[i][k]
					{
						tmp[i][j]+=ans[k][j]*f[i][k];
						tmp[i][j]%=m;
					}
				}
			}
			for(long long i=0;i<d;i++)
			{
				for(long long j=0;j<d;j++)
				{
					ans[i][j]=tmp[i][j];
				}
			}
		}
		a>>=1;
		//f*=f
		//now*=2;
		for(long long i=0;i<d;i++)
		{
			for(long long j=0;j<d;j++)//calculate f[i][j]
			{
				tmp[i][j]=0;
				for(long long k=0;k<d;k++)//sum f[k][j]*f[i][k]
				{
					tmp[i][j]+=f[k][j]*f[i][k];
					tmp[i][j]%=m;
				}
			}
		}
		for(long long i=0;i<d;i++)
		{
			for(long long j=0;j<d;j++)
			{
				f[i][j]=tmp[i][j];
			}
		}
	}
	for(long long i=0;i<d;i++)
	{
		for(long long j=0;j<d;j++)
		{
			f[i][j]=ans[i][j];
		}
	}
}
void showf()
{
		for(long long i=0;i<d;i++)
		{
			for(long long j=0;j<d;j++)
			{
				printf(" %lld",f[j][i]);
			}
			printf("\n");
		}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&d,&n,&m)==3)
	{
		if(d==0&&n==0&&m==0) break;
		//n--;
		//printf("%lld %lld %lld\n",d,n,m);
		for(long long i=0;i<d;i++)
		{
			for(long long j=1;j<d;j++)
			{
				f[i][j]=0;
			}
		}
		for(long long i=0;i<d-1;i++)
		{
			f[i][i+1]=1;
		}
		for(long long i=0;i<d;i++)
		{
			scanf("%lld",&f[i][0]);
			//printf(" %lld",f[i][0]);
			f[i][0]%=m;
		}//printf("\n");
		for(long long i=0;i<d;i++)
		{
			scanf("%lld",&bas[i]);
			//printf(" %lld",bas[i]);
			bas[i]%=m;
		}//printf("\n");
		//showf();
		if(n<=d) printf("%lld\n",bas[n-1]);
		else
		{
			//f^(n-d+1)*bas==ans
			dopow(n-d);
			//return f*bas
			printf(" %lld\n",n-d+1);showf();
			Ans=0;
			for(long long i=0;i<d;i++)
			{
				Ans+=f[i][0]*bas[i];
				Ans%=m;
			}
			printf("%lld\n",Ans);
		}
	}
	return 0;
}
