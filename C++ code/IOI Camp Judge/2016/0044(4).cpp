#include<cstdio>
//#include<cassert>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int min(const int a,const int b,const int c,const int d){return min(min(a,b),min(c,d));}
int R,C,N,EDGE[20][20];
int DP[20][1<<20];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&R,&C,&N);
		assert(N<=20);
		static int r[20],c[20];
		for(int i=0;i<N;i++)scanf("%d%d",&r[i],&c[i]);
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)EDGE[i][j]=EDGE[j][i]=abs(r[i]-r[j])+abs(c[i]-c[j]);
		if(N&1){N++;for(int i=0;i<N-1;i++)EDGE[i][N-1]=EDGE[N-1][i]=min(r[i],R+1-r[i],c[i],C+1-c[i]);}
		assert(N%2==0);
		if(N==0){puts("0");continue;}
		for(int s=0;s<(1<<N);s++)DP[0][s]=INF;
		DP[0][0]=0;
		for(int i=1;i<N;i++)
		{
			for(int s=0;s<(1<<N);s++)DP[i][s]=INF;
			for(int s=0;s<(1<<N);s++)if(DP[i-1][s]!=INF)
			{
				assert(!(s&(1<<i)));
				getmin(DP[i][s],DP[i-1][s]);
				for(int j=0;j<i;j++)if(!(s&(1<<j)))getmin(DP[i][s+(1<<j)+(1<<i)],DP[i-1][s]+EDGE[j][i]);
			}
		}
		assert(DP[N-1][(1<<N)-1]!=INF);
		printf("%d\n",DP[N-1][(1<<N)-1]);
	}
	return 0;
}
