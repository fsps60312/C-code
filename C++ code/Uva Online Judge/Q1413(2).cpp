#include<cstdio>
int N,K;
double P[50],DP[50][50][2];
double PR[50][50]/*(i,j)=>pass right to i+j from i*/;
double PL[50][50]/*(i,j)=>pass left to i-j from i*/;
int main()
{
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<N;i++)scanf("%d",&P[i]);
		for(int i=1;i<N;i++)
		{
			PR[i][0]=0.0;
			PR[i][1]=P[i];
			for(int j=2;j<N-1&&i+j-1<N;j++)PR[i][j]=PR[i][j-1]*P[i+j-1]+PR[i][j-2]*(1.0-P[i+j-1]);
			PL[i][0]=0.0;
			PL[i][1]=1.0-P[i];
			for(int j=2;j<N-1&&i-j+1>=1;j++)PL[i][j]=PL[i][j-1]*(1.0-P[i-j+1])+PL[i][j-2]*P[i-j+1];
		}
		//DP[l,r,0]=DP[l,r,1]*PL[K+r,r+l]+DP[
		for(int l=0;K-l>=1;l++)
		{
			if(l)DP[l][0]=DP[l-1][0]*(1.0-P[K-l+1]);
			else DP[l][0]=1.0;
			for(int r=1;K+r<N;r++)
			{
				DP[l][r]=DP[l][r-1]*P[K+r-1];
				if(l)DP[l][r]+=DP[l-1][r]*(1.0-P[K-l+1]);
			}
		}
		
	}
	return 0;
}
