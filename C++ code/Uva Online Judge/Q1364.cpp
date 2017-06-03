#include<cstdio>
#include<cstdlib>
#define min(x,y) (x)<(y)?(x):(y)
int N,M,LIKE[1001][1001],PRE[1001],LOW[1001],ISCUT[1001],PRE_CNT,BCC_CNT;
void show(){for(int i=1;i<=N;i++)printf("LOW=%d\tISCUT=%d\tPRE=%d\n",LOW[i],ISCUT[i],PRE[i]);}
void dfs(int u,int fa)
{
	int lowu=LOW[u]=PRE[u]=++PRE_CNT;
	int child=0;
	for(int i=1;i<=N;i++)
	{
		if(!LIKE[u][i])continue;
		if(!PRE[i])
		{
			child++;
			dfs(i,u);
			if(LOW[i]>=lowu)ISCUT[u]=true;
			LOW[u]=min(LOW[u],LOW[i]);
		}
		else if(PRE[i]<PRE[u]&&i!=fa)
		{
			LOW[u]=min(LOW[u],PRE[i]);
		}
	}
	if(fa==-1&&child==1)ISCUT[u]=false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		PRE_CNT=BCC_CNT=0;
		for(int k1=1;k1<=N;k1++)
		{
			PRE[k1]=LOW[k1]=ISCUT[k1]=0;
			for(int k2=1;k2<=N;k2++)
			{
				LIKE[k1][k2]=false;
			}
		}
		while(M--)
		{
			int k1,k2;scanf("%d%d",&k1,&k2);
			LIKE[k1][k2]=LIKE[k2][k1]=true;
		}
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])dfs(i,-1);
		}
		for(int i=1;i<=N;i++)printf("LOW=%d\tISCUT=%d\tPRE=%d\n",LOW[i],ISCUT[i],PRE[i]);
		show();
	}
	return 0;
}
