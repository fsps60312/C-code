#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
double P[2][3],HH,HF,FH,FF;
pair<double,int>DP[100000][2];
char S[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lf%lf%lf%lf",&HH,&HF,&FH,&FF);
	for(int i=0;i<2;i++)for(int j=0;j<3;j++)scanf("%lf",&P[i][j]);
	scanf("%s",S);
	DP[0][0]=make_pair(1.0,1),DP[0][1]=make_pair(0.0,0);
	int t;
	for(t=1;S[t];t++)
	{
//		static int q[2][3];
//		for(int i=0;i<2;i++)for(int j=0;j<3;j++)q[i][j]=0.0;
//		for(int i=0;i<3;i++)
//		{
//			q[0][i]+=DP[t-1][0].first*HH*P[0][i];
//			q[1][i]+=DP[t-1][0].first*HF*P[1][i];
//			q[0][i]+=DP[t-1][1].first*FH*P[0][i];
//			q[1][i]+=DP[t-1][1].first*FF*P[1][i];
//		}
		const int d=S[t]-'1';
//		printf("d=%d\n",d);
		assert(0<=d&&d<3);
		DP[t][0]=max(make_pair(DP[t-1][0].first*HH*P[0][d],DP[t-1][0].second+1),make_pair(DP[t-1][1].first*FH*P[0][d],DP[t-1][1].second+1));
		DP[t][1]=max(make_pair(DP[t-1][0].first*HF*P[1][d],DP[t-1][0].second),make_pair(DP[t-1][1].first*FF*P[1][d],DP[t-1][1].second));
		double sum=DP[t][0].first+DP[t][1].first;
		DP[t][0].first/=sum,DP[t][1].first/=sum;
//		printf("(%.9f,%d),(%.9f,%d)\n",DP[t][0].first,DP[t][0].second,DP[t][1].first,DP[t][1].second);
//		if(t==10)for(;;);
	}
	t--;
	auto &ans=max(DP[t][0],DP[t][1]);
	printf("%d\n",ans.second);
	return 0;
}
