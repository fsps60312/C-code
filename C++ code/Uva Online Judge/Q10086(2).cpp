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
dptype dp[300][60];
int in1[30][21],in2[30][21];
int t1,t2,t3,n;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&t1,&t2)==2&&(t1||t2))
	{
		t3=t1+t2;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&in1[i][0]);
			//printf(" %d\n",in1[i][0]);
			for(int j=1;j<=in1[i][0];j++)
			{
				scanf("%d",&in1[i][j]);
			}
			//in2[i][0]=in1[i][0];
			for(int j=1;j<=in1[i][0];j++)
			{
				scanf("%d",&in2[i][j]);
			}
		}
		for(int i=t3;i>=0;i--)//pod num
		{
			for(int j=0;j<n*2;j++)//site
			{
				dp[i][j].reset();
			}
		}
		dp[0][0].set(0,-1);
		for(int i=1;i<=in1[0][0];i++)//site 0
		{
			dp[i][0].set(in1[0][i],i);
		}
		for(int i=1;i<n;i++)
		{
			for(int j=0;j<=t1;j++) dp[j][i].set(dp[j][i-1].x,0);
					//printf("%d %d pass\n",in1[i][0],i);
			for(int j=1;j<=in1[i][0];j++)
			{
				for(int k=j;k<=t1;k++)
				{
					dp[k][i].set(dp[k-j][i-1].x+in1[i][j],j);
				}
			}
		}
		for(int i=0;i<t1;i++)
		{
			dp[i][n-1].reset();
		}
		for(int i=n;i<2*n;i++)
		{
			for(int j=t1;j<=t3;j++) dp[j][i].set(dp[j][i-1].x,0);
					//printf("%d %d pass\n",in1[i-n][0],i-n);
			for(int j=1;j<=in1[i-n][0];j++)
			{
				for(int k=t1+j;k<=t3;k++)
				{
					dp[k][i].set(dp[k-j][i-1].x+in2[i-n][j],j);
				}
			}
		}
		for(int i=0;i<2*n;i++)
		{
			for(int j=0;j<=t3;j++) printf(" %d",dp[j][i].x);
			printf("\n");
		}
		printf("%d\n",dp[t3][2*n-1].x);
		for(int i=2*n-1,j=t3;i>=0;i--)
		{
			printf(" %d",dp[j][i].y);
			j-=dp[j][i].y;
		}
	}
	return 0;
}
