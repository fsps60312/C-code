#include<cstdio>
#include<cstdlib>
int T,N,C[51][51];
int main()
{
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		if(kase>1)printf("\n");
		scanf("%d",&N);
		for(int i=1;i<=50;i++)
		{
			for(int j=0;j<=50;j++)
			{
				C[i][j]=0;
			}
		}
		int ans=0,start=0;
		for(int i=0,n1,n2;i<N;i++)
		{
			scanf("%d%d",&n1,&n2);
			start=n1;
			C[n1][n2]++,C[n2][n1]++;
			C[n1][0]++;
			if(C[n1][0]&1)ans++;
			else ans--;
			C[n2][0]++;
			if(C[n2][0]&1)ans++;
			else ans--;
		}
		//printf("ans=%d\n",ans);
		printf("Case #%d\n",kase++);
		if(ans==0)
		{
			int now=start;
			while(1)
			{
				int u=0;
				while(C[now][now])
				{
					C[now][now]-=2;
					printf("%d %d\n",now,now);
				}
				for(int i=1;i<=50;i++)
				{
					if(C[now][i])
					{
						u=i;
						C[now][u]--;
						C[u][now]--;
						printf("%d %d\n",now,u);
						now=u;
						break;
					}
				}
				if(u==0)break;
			}
		}
		else printf("some beads may be lost\n");
		/*for(int i=1;i<=50;i++)
		{
			for(int j=1;j<=50;j++)
			{
				printf(" %d",C[i][j]);
			}
			printf("\n");
		}*/
	}
	return 0;
}
