#include<cstdio>
#include<cstdlib>
int C,S,Q,MAT[101][101];
void setMAT(int i,int j,int v){if(i>j)i^=j^=i^=j;MAT[i][j]=v;}
int getMAT(int i,int j){if(i>j)i^=j^=i^=j;return MAT[i][j];}
void getmin(int &a,int b){if(b<a)a=b;}
#define max(x,y) (x)>(y)?(x):(y)
void pre_cal()
{
	for(int k=1;k<=C;k++)
	{
		for(int i=1;i<=C;i++)
		{
			for(int j=1;j<=C;j++)
			{
				getmin(MAT[i][j],max(getMAT(i,k),getMAT(k,j)));
			}
		}
	}
}
int main()
{
	int kase=1;
	while(scanf("%d%d%d",&C,&S,&Q)==3&&(C||S||Q))
	{
		if(kase>1)printf("\n");
		for(int i=1;i<=C;i++)for(int j=i;j<=C;j++)MAT[i][j]=2147483647;
		while(S--)
		{
			int a,b,d;scanf("%d%d%d",&a,&b,&d);
			setMAT(a,b,d);
		}
		pre_cal();
		printf("Case #%d\n",kase++);
		while(Q--)
		{
			int a,b;scanf("%d%d",&a,&b);
			int ans=getMAT(a,b);
			if(ans==2147483647)printf("no path\n");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
