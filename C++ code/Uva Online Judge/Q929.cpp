#include<cstdio>
#include<cstdlib>
int S[999][999],tmp[18000][2];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&x,&y);
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				scanf("%d",&S[i][j]);
			}
		}
		int n=x+y-1;
		for(int i=0;i<=n*9;i++) tmp[i][0]=0;
		tmp[0][0]=1;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<=i;j++)
			{
				if(j<x&&i-j<y)
				{
					for(int k=n*9;k>=0;k--)
					{
						if(k>=S[j][i-j]&&tmp[k-S[j][i-j]][i%2])
						{
							tmp[k][(i+1)%2]++;
						}
						else
						{
							tmp[k][(i+1)%2]=0;
						}
					}
				}
			}
		}
		int ans;
		for(ans=0;;ans++) if(tmp[ans][n%2]) break;
		printf("%d\n",ans);
	}
	return 0;
}
