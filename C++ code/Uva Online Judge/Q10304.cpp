#include<cstdio>
#include<cstdlib>
struct pairtype{int i,sum,cost;};
int n,S[250];
pairtype dp[250][250];
pairtype newpair(int a,int b,int c){pairtype z;z.i=a,z.sum=b,z.cost=c;return z;}
pairtype q(int l,int r)
{
	if(l>r)return newpair(-1,0,0);
	if(dp[l][r].cost!=-1)return dp[l][r];
	if(l==r)return dp[l][r]=newpair(l,S[l],0);
	pairtype ans=newpair(-1,-1,2147483647);
	for(int i=l;i<=r;i++)
	{
		pairtype a=q(l,i-1),b=q(i+1,r);
		if(a.cost+a.sum+b.cost+b.sum<ans.cost)ans=newpair(i,a.sum+S[i]+b.sum,a.cost+a.sum+b.cost+b.sum);
	}
	return dp[l][r]=ans;
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=0;i<n;i++)scanf("%d",&S[i]);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				dp[i][j].cost=-1;
			}
		}
		pairtype ans=q(0,n-1);//printf("%d %d %d\n",ans.i,ans.sum,ans.cost);
		printf("%d\n",ans.cost);
	}
	return 0;
}
