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
struct intype
{
	int x,y;
};
dptype dp[300][60];
intype input[30][21];
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
			scanf("%d",&input[i][0].x);
			for(int j=1;j<=input[i][0].x;j++)
			{
				scanf("%d",&input[i][j].x);
				input[i][j].y=0;
			}
			for(int j=1,k;j<=input[i][0].x;j++)
			{
				scanf("%d",&k);
				if(k<input[i][j].x) input[i][j].x=k,input[i][j].y=1;
			}
		}
		for(int i=t3;i>=0;i--)//pod num
		{
			for(int j=0;j<n;j++)//site
			{
				dp[i][j].reset();
			}
		}
		dp[0][0].set(0,-1);
		for(int i=1;i<=input[0][0].x;i++)//site 0
		{
			dp[i][0].set(input[0][i].x,i);
		}
		for(int i=1;i<n;i++)
		{
			for(int j=0;j<=t3;j++) dp[j][i].set(dp[j][i-1].x,0);
			for(int j=1;j<=input[i][0].x;j++)
			{
				for(int k=j;k<=t1;k++)
				{
					dp[k][i].set(dp[k-j][i-1].x+input[i][j].x,j);
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<=t3;j++) printf(" %d",dp[j][i].x);
			printf("\n");
		}
		printf("%d\n",dp[t3][n-1].x);
	}
	return 0;
}
