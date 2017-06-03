#include<cstdio>
#include<cstdlib>
int T,n,ans,now,S[12][12];
bool vis[12][12];
bool nvi[1001];
bool found;
void dfs(int a,int b,int c)
{
	if(now==ans||vis[a][b]||nvi[S[a][b]]) return;
	vis[a][b]=true;
	nvi[S[a][b]]=true;
	if(c>now) now=c;
	if(a>0) dfs(a-1,b,c+1);//1
	if(b>0) dfs(a,b-1,c+1);//2
	if(a<n) dfs(a+1,b,c+1);//3
	if(b<n) dfs(a,b+1,c+1);//4
	vis[a][b]=false;
	nvi[S[a][b]]=false;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<=1000;i++)
		{
			nvi[i]=false;
		}
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				scanf("%d",&S[i][j]);
				if(!nvi[S[i][j]])
				{
					ans++;
					nvi[S[i][j]]=true;
				}
				vis[i][j]=false;
			}
		}
		//printf("%d\n",ans);
		for(int i=0;i<=1000;i++) nvi[i]=false;
		found=false;
		now=0;
		for(int i=0;i<n&&now!=ans;i++)
		{
			for(int j=0;j<n&&now!=ans;j++)
			{
				dfs(i,j,1);
			}
		}
		printf("%d\n",now);
	}
	return 0;
}
