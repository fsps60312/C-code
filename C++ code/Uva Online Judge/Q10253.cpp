#include<cstdio>
#include<cstdlib>
long long f[31][31];//edges, nodes
int n;
int main()
{
	for(int i=0;i<31;i++)
	{
		for(int j=0;j<31;j++)
		{
			f[i][j]=0;
		}
	}
	f[1][1]=1;
	for(int i=2;i<=30;i++)//edges
	{
		for(int j=1;j<=30;j++)//nodes
		{
			if(j==1)
			{
				for(int l=1;l<=30;l++)//parallel
				{
					f[i][j]+=f[i-1][l];
				}
			}
			else
			{
				for(int k=1;k<=i/2;k++)//k edge + (i-k) edge
				{
					for(int l=1;l<=j/2;l++)//l node + (j-l) node
					{
						f[i][j]+=f[k][l]*f[i-k][j-l];
						if(i==4&&j==2) printf(" %lld\n",f[i][j]);
					}
				}
			}
			if(i<=5&&j<=5) printf(" %d %d %lld\n",i,j,f[i][j]);
		}
	}
	for(int i=1;i<=30;i++)//edges
	{
		for(int j=1;j<=30;j++)//nodes
		{
			f[i][0]+=f[i][j];
		}
	}
	while(scanf("%d",&n)==1)
	{
		printf("%lld\n",f[n][0]);
	}
	return 0;
}
