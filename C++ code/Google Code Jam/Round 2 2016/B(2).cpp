#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(double &a,const double b){if(a<b)a=b;}
double Solve(const vector<double>&s)
{
	static double *dp[2]={new double[401]+200,new double[401]+200};
	int d=0;
	for(int i=-200;i<=200;i++)dp[d][i]=0.0;
	dp[d][0]=1.0;
	for(int i=0;i<(int)s.size();i++,d^=1)
	{
		for(int j=-200;j<=200;j++)dp[d^1][j]=0.0;
		for(int j=-200;j<=200;j++)if(dp[d][j]>0.0)
		{
			assert(-200<j&&j<200);
//			printf("i=%d,j=%d,s[i]=%f,dp=%f\n",i,j,s[i],dp[d][j]);
			dp[d^1][j-1]+=dp[d][j]*(1.0-s[i]);
			dp[d^1][j+1]+=dp[d][j]*s[i];
		}
	}
	return dp[d][0];
}
double S[201];
int N,K;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)scanf("%lf",&S[i]);
		sort(S,S+N);
		double ans=0.0;
		for(int i=0;i<=N-(N-K);i++)
		{
			vector<double>tmp;
			for(int j=0;j<i;j++)tmp.push_back(S[j]);
			for(int j=i+(N-K);j<N;j++)tmp.push_back(S[j]);
			getmax(ans,Solve(tmp));
		}
		static int kase=0;
		printf("Case #%d: %.10f\n",++kase,ans);
	}
	return 0;
}
