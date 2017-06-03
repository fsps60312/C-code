#include<cstdio>
#include<cstdlib>
int S[14][14];
int vis[1001],Max,ans,T,n;
void dfs(int a,int b,int c)
{
	if(ans==Max||vis[S[a][b]]) return;
	if(c>ans) ans=c;
	vis[S[a][b]]=1;
	dfs(a-1,b,c+1);
	dfs(a,b+1,c+1);
	dfs(a+1,b,c+1);
	dfs(a,b-1,c+1);
	vis[S[a][b]]=0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<1001;i++) vis[i]=0;
		Max=0,ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				scanf("%d",&S[i][j]);
				if(!vis[S[i][j]])
				{
					vis[S[i][j]]=1;
					Max++;
				}
			}
		}
		for(int i=0;i<1001;i++) vis[i]=0;
		for(int i=1;i<=n;i++)
		{
			S[0][i]=S[1][i];
			S[i][0]=S[i][1];
			S[n+1][i]=S[n][i];
			S[i][n+1]=S[i][n];
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				//for(int k=0;k<1001;k++) vis[k]=0;
				dfs(i,j,1);
			}
		}
		printf("%d\n",ans);
		if(T) printf("\n");
	}
	return 0;
}
