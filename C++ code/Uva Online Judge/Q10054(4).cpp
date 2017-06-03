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
			int inip=start;
			ans=1;
			while(1)
			{
				int u=0;
				for(int i=1;i<=50;i++)
				{
					if(C[start][i])
					{
						printf("check%d(%d)->%d(%d):%d\n",start,C[start][0],i,C[i][0],C[start][i]);
						if(ans<N&&C[i][0]==1&&i==inip)continue;
						C[start][0]--,C[i][0]--;
						C[start][i]--;
						C[i][start]--;
						printf("%d %d\n",start,i);
						ans++;
						u=start=i;
						break;
					}
				}
				if(u==0)break;
			}
		}
		else printf("some beads may be lost\n");
		//for(int i=0;i<=50;i++)printf(" %d",C[28][i]);
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
