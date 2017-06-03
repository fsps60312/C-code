#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1e-12;
int N,M,X[100];
double DP[2][100002];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		DP[0][0]=M-1;
		for(int i=1;i<=M*N;i++)DP[0][i]=0;
		int d=0,sum=0;
		for(int contest=0,x;contest<N;contest++,d^=1)
		{
			scanf("%d",&x),sum+=x;
			for(int i=0;i<=M*N;i++)DP[d^1][i]=0;
			for(int i=0;i<=M*N;i++)
			{
				const double &v=DP[d][i];
				if(fabs(v)<EPS)continue;
				DP[d^1][i+1]+=v/(M-1);
				DP[d^1][i+x]-=v/(M-1);
				DP[d^1][i+x+1]+=v/(M-1);
				DP[d^1][i+M+1]-=v/(M-1);
			}
			for(int i=1;i<=M*N;i++)DP[d^1][i]+=DP[d^1][i-1];
		}
		double ans=1;
		for(int i=0;i<sum;i++)ans+=DP[d][i];
		printf("%.10f\n",ans);
	}
	return 0;
}
