#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
const int INF=2147483647;
int N,M,C[300][301];
void generateInput()
{
	FILE *out=fopen("in.txt","w");
	srand(7122);
	fprintf(out,"100\n");
	for(int i=0;i<100;i++)
	{
		fprintf(out,"300 300\n");
		for(int j=0;j<300;j++)for(int k=0;k<300;k++)fprintf(out,"%d ",rand()%1000000+1);
		fprintf(out,"\n");
	}
	fclose(out);
}
int main()
{
//	generateInput();
//	return 0;
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			C[i][0]=0;
			for(int j=1;j<=M;j++)scanf("%d",&C[i][j]);
			sort(C[i]+1,C[i]+M+1);
			for(int j=1;j<=M;j++)C[i][j]+=C[i][j-1];
		}
		static int dp[300][301];
		for(int i=1;i<=M;i++)dp[0][i]=C[0][i]+i*i;
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<=M;j++)dp[i][j]=INF;
			for(int j=1;j<=M;j++)
			{
				for(int k=0;j-1+k<=M;k++)
				{
					getmin(dp[i][j-1+k],dp[i-1][j]+C[i][k]+k*k);
				}
			}
		}
		static int kase=0;
		printf("Case #%d: %d\n",++kase,dp[N-1][1]);
	}
	return 0;
}
