#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int C,R,Q,FEAST[81];
int DIS[81][81],ANS[81][81];
int min(int a,int b)
{
	if(a==-1)return b;
	if(b==-1)return a;
	return a<b?a:b;
}
void cal_DIS()
{
	bool changed=true;
	while(changed)
	{
		changed=false;
		for(int k=1;k<=C;k++)
		{
			for(int i=1;i<=C;i++)
			{
				if(FEAST[k]>FEAST[i])continue;
				for(int j=1;j<=C;j++)
				{
					if(FEAST[j]>FEAST[i]||DIS[i][k]==-1||(DIS[k][j]==-1&&DIS[j][k]==-1))continue;
					int a=DIS[i][k]+(min(DIS[k][j],DIS[j][k]));
					if(a<DIS[i][j]||DIS[i][j]==-1)
					{
						//printf("change DIS[%d][%d](%d) to %d(=%d+min(%d,%d),k=%d)\n",i,j,DIS[i][j],a,DIS[i][k],DIS[k][j],DIS[j][k],k);
						DIS[i][j]=a;
						changed=true;
					}
				}
			}
		}
	}
}
void cal_ANS()
{
	for(int i=1;i<=C;i++)
	{
		for(int j=1;j<=C;j++)
		{
			for(int k=1;k<=C;k++)
			{
				if(DIS[k][i]==-1||DIS[k][j]==-1)continue;
				int a=FEAST[k]+DIS[k][i]+DIS[k][j];
				if(a<ANS[i][j]||ANS[i][j]==-1)ANS[i][j]=a;
			}
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d%d",&C,&R,&Q)==3&&(C||R||Q))
	{
		for(int i=1;i<=C;i++)
		{
			for(int j=1;j<=C;j++)
			{
				DIS[i][j]=ANS[i][j]=-1;
			}
			DIS[i][i]=0;
			scanf("%d",&FEAST[i]);
		}
		while(R--)
		{
			int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
			if(FEAST[a]>=FEAST[b])DIS[a][b]=dis;
			if(FEAST[b]>=FEAST[a])DIS[b][a]=dis;
		}
		/*printf("DIS1\n");
		for(int i=1;i<=C;i++)
		{
			for(int j=1;j<=C;j++)
			{
				printf("\t%d",DIS[i][j]);
			}
			printf("\n");
		}*/
		cal_DIS();
		/*printf("DIS2\n");
		for(int i=1;i<=C;i++)
		{
			for(int j=1;j<=C;j++)
			{
				printf("\t%d",DIS[i][j]);
			}
			printf("\n");
		}*/
		cal_ANS();
		/*printf("ANS\n");
		for(int i=1;i<=C;i++)
		{
			for(int j=1;j<=C;j++)
			{
				printf("\t%d",ANS[i][j]);
			}
			printf("\n");
		}*/
		if(kase>1)printf("\n");
		printf("Case #%d\n",kase++);
		while(Q--)
		{
			int a,b;scanf("%d%d",&a,&b);
			printf("%d\n",ANS[a][b]);
		}
	}
	return 0;
}
