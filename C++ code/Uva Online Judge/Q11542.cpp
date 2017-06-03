#include<cstdio>
#include<cstdlib>
long long T,n,S,p[100],f[100][2];
long long pow(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
		}
		a*=a;
		b/=2;
	}
	return ans;
}
int main()
{
	p[0]=2,p[1]=3;
	for(int i=2,j;;i++)
	{
		p[i]=p[i-1];
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		if(p[i]>=500) break;
	}
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		int Max=0;
		for(int i=0;i<n;i++)
		{
			f[i][0]=f[i][1]=0;
			scanf("%lld",&S);
			for(int j=0;S!=1;j++)
			{
				while(S%p[j]==0)
				{
					if(j>Max) Max=j;
					if(j<50) f[i][0]^=(long long)1<<j;
					else f[i][1]^=(long long)1<<(j-50);
					S/=p[j];
				}
			}
		}
		long long ans=0;
		for(int i=0,j=Max;i<n&&j>=0;)
		{
			if(!(j<50?(f[i][0]&((long long)1<<j)):(f[i][1]&((long long)1<<(j-50)))))
			{
				ans=i;
				for(int k=i+1;k<n;k++)
				{
					if(j<50?(f[k][0]&((long long)1<<j)):(f[k][1]&((long long)1<<(j-50))))
					{
						ans=k;
						break;
					}
				}
				if(ans==i)
				{
					j--;
					continue;
				}
				else
				{
					long long a=f[i][0],b=f[i][1];
					f[i][0]=f[ans][0],f[i][1]=f[ans][1];
					f[ans][0]=a,f[ans][1]=b;
				}
			}
			//if(j==-1) break;
			for(int k=0;k<n;k++)
			{
				if(k!=i&&(j<50?(f[k][0]&((long long)1<<j)):(f[k][1]&((long long)1<<(j-50)))))
				{
					f[k][0]^=f[i][0];
					f[k][1]^=f[i][1];
				}
			}
			i++;
		}
		ans=n;
		/*for(int i=0;i<n;i++)
		{
			printf(" ");
			for(int j=0;j<=Max;j++)
			{
				if(f[i][0]&((long long)1<<j)) printf("1");
				else printf("0");
			}
			printf("\n");
		}*/
		for(int i=0;i<n;i++)
		{
			if(f[i][0]>0||f[i][1]>0) ans--;
		}
		printf("%lld\n",pow(2,ans)-1);
	}
	return 0;
}
