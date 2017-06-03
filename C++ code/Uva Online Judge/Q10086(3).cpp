#include<cstdio>
#include<cstdlib>
struct dptype
{
	int x,y;
	void reset()
	{
		x=y=1147483647;
	}
	void set(int a,int b)
	{
		if(a<x)
		{
			x=a,y=b;
		}
	}
};
dptype dp[300][30];
int in[30][21],m[30];
int t1,t2,n;
void dfs(int a,int b)
{
	if(a==0)
	{
		printf("%d",dp[b][a].y);
		return;
	}
	dfs(a-1,b-dp[b][a].y);
	printf(" %d",dp[b][a].y);
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d",&t1,&t2)==2&&(t1||t2))
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&m[i]);
			in[i][0]=0;
			for(int j=1;j<=m[i];j++)
			{
				scanf("%d",&in[i][j]);
			}
			for(int j=1,k;j<=m[i];j++)
			{
				scanf("%d",&k);
				in[i][m[i]-j]+=k;
			}
		}
		for(int i=t1;i>=0;i--)//pod num
		{
			for(int j=0;j<n;j++)//site
			{
				dp[i][j].reset();
			}
		}
		for(int i=0;i<=m[0];i++)
		{
			dp[i][0].set(in[0][i],i);
		}
		for(int i=1;i<n;i++)
		{
			for(int j=0;j<=m[i];j++)
			{
				for(int k=j;k<=t1;k++)
				{
					dp[k][i].set(dp[k-j][i-1].x+in[i][j],j);
				}
			}
		}
		/*for(int i=0;i<n;i++)
		{
			for(int j=0;j<=t1;j++) printf(" %d",dp[j][i].x);
			printf("\n");
		}*/
		printf("%d\n",dp[t1][n-1].x);
		dfs(n-1,t1);
		printf("\n\n");
		/*for(int i=n-1,j=t1;i>=0;i--)
		{
			printf(" %d",dp[j][i].y);
			j-=dp[j][i].y;
		}*/
	}
	return 0;
}
