#include<cstdio>
#include<algorithm>
using namespace std;
int M,N;
int ANS[300][300],GSUM[300][300],NOT[300][300];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main()
{
	for(int i=1;i<300;i++)NOT[1][i]=NOT[i][1]=0;
	for(int i=2;i<300;i++)
	{
		for(int j=2;j<300;j++)
		{
			NOT[i][j]=NOT[i-1][j]+NOT[i][j-1]-NOT[i-1][j-1];
			int v=gcd(i,j);
			if(v==1)continue;
			if(v==2)NOT[i][j]++;
			NOT[i][j]++;
		}
	}
	for(int i=1;i<300;i++)GSUM[1][i]=GSUM[i][1]=i;
	for(int i=2;i<300;i++)
	{
		for(int j=2;j<300;j++)
		{
			GSUM[i][j]=i*j-NOT[i][j];
		}
	}
	ANS[1][1]=GSUM[1][1];
	for(int i=2;i<300;i++)ANS[1][i]=ANS[i][1]=ANS[1][i-1]+GSUM[1][i];
	for(int i=2;i<300;i++)
	{
		for(int j=2;j<300;j++)
		{
			ANS[i][j]=ANS[i-1][j]+ANS[i][j-1]-ANS[i-1][j-1]+GSUM[i][j];
		}
	}
	while(scanf("%d%d",&M,&N)==2&&(M||N))
	{
		printf("%d\n",ANS[--M][--N]<<1);
	}
	return 0;
}
