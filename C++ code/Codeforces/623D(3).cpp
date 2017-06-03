#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int BOUND=500;
int N;
double S[100];
double DP[2][BOUND],P[BOUND],A[BOUND];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lf",&S[i]),S[i]*=0.01;
		double sum=0.0;
		for(int i=0;i<N;i++)sum+=1.0/S[i];
		//(1/s)/((1/s)/sum)=sum
		//p=s*((1/s)/sum)=(s/(s*sum))=1.0/sum
		//to i-th round: (1.0-1.0/sum)^i
		const double p=1.0/sum;//possibility of choose the right one
		P[0]=1.0;
		for(int i=1;i<BOUND;i++)P[i]=P[i-1]*(1.0-p);//P[i]: possibility of do i rounds and not finished
		DP[0][0]=A[0]=0.0;
		for(int i=1;i<BOUND;i++)DP[0][i]=A[i]=P[i-1]*p;//possibility of end at i-th round
		int d=0;
		for(int i=1;i<N;i++,d^=1)
		{
			for(int j=0;j<BOUND;j++)DP[d^1][j]=0.0;
			for(int j=0;j<BOUND;j++)for(int k=0;k<BOUND;k++)if(j!=k)
			{
				DP[d^1][max(j,k)]+=DP[d][j]*A[k];
			}
//			double test=0.0;
//			for(int j=0;j<BOUND;j++)test+=DP[d^1][j];
//			printf("i=%d,test=%.9f\n",i,test);
		}
		double ans=0.0;
		for(int i=0;i<BOUND;i++)ans+=i*DP[d][i];
		printf("%.9f\n",ans);
	}
	return 0;
}
