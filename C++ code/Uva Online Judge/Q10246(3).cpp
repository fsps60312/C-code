#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int C,R,Q,FEAST[81];
int DIS[81][81],ANS[81][81],ORD[81];
int min(int a,int b)
{
	if(a==-1)return b;
	if(b==-1)return a;
	return a<b?a:b;
}
void cal_DIS()
{
	for(int ti=1;ti<=C;ti++)
	{
		int i=ORD[ti];
		for(int tj=1;tj<=C;tj++)
		{
			int j=ORD[tj];
			if(FEAST[j]>FEAST[i])break;
			for(int tk=1;tk<=C;tk++)
			{
				int k=ORD[tk];
				if(FEAST[k]>FEAST[j])break;
				if(DIS[i][k]==-1||(DIS[k][j]==-1&&DIS[j][k]==-1))continue;
				int a=DIS[i][k]+min(DIS[k][j],DIS[j][k]);
				if(a<DIS[i][j]||DIS[i][j]==-1)
				{
					DIS[i][j]=a;
				}
			}
		}
		for(int tj=1;tj<=C;tj++)
		{
			int j=ORD[tj];
			if(FEAST[j]>FEAST[i])break;
			for(int tk=tj;tk<=C;tk++)
			{
				int k=ORD[tk];
				if(FEAST[k]>FEAST[i])break;
				if(DIS[i][k]==-1||(DIS[k][j]==-1&&DIS[j][k]==-1))continue;
				int a=DIS[i][k]+min(DIS[k][j],DIS[j][k]);
				if(a<DIS[i][j]||DIS[i][j]==-1)
				{
					DIS[i][j]=a;
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
void swap(int &a,int &b){a^=b^=a^=b;}
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
			ORD[i]=i;
		}
		for(int i=1;i<=C;i++)
		{
			int k=i;
			for(int j=i+1;j<=C;j++)
			{
				if(FEAST[ORD[j]]<FEAST[ORD[k]])k=j;
			}
			if(k!=i)swap(ORD[i],ORD[k]);
			//printf(" %d",FEAST[ORD[i]]);
		}//printf("\n");
		while(R--)
		{
			int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
			if(FEAST[a]>=FEAST[b])DIS[a][b]=dis;
			if(FEAST[b]>=FEAST[a])DIS[b][a]=dis;
		}
		cal_DIS();
		cal_ANS();
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
