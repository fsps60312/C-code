#include<cstdio>
#include<algorithm>
using namespace std;
int T,N,M,K,POW[11],SUF[11];
int DP[150][59049];
int TMP[150][10];
int Get(int r,int s)
{
	int &dp=dp[r][s];
	if(dp!=-1)return dp;
	int *tmp=TMP[r];
	bool found=false;
	for(int i=0;i<M;i++)
	{
		tmp[i]=s/POW[i]%3;
		if(tmp[i]==0)
		{
			found=true;
			if()
			dp=max(dp,1+Get(r,))
		}
	}
	if(!found)return dp=Get(r+1,s-SUF[M]);
	return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	POW[0]=SUF[0]=1;
	for(int i=1;i<=10;i++)POW[i]=POW[i-1]*3,SUF[i]=SUF[i-1]+POW[i];
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&N,&M,&K);
			for(int i=0;i<POW[M];i++)
			{
				for(int j=0;j<N;j++)
				{
					DP[j][i]=-1;
				}
			}
			printf("%d\n",Get(j,0));
		}
	}
	return 0;
}
