#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
void getmax(double &a,const double &b){if(b>a)a=b;}
int N,K;
double DP[3001],P,LEVEL[3001],ODD[3001];
double Solve()
{
	if(P==0.0)return 0;
	if(P==1.0)return N/K;
	const double loga=log(P),logb=log(1.0-P);
	for(int i=0;i<=N;i++)DP[i]=0.0;
	if(true)
	{
		for(int i=K;i<=N;i++)
		{
			double &v=ODD[i]=1.0;
			for(int j=0;j<=K-1;j++)v-=exp(LEVEL[i]-LEVEL[j]-LEVEL[i-j]+j*loga+(i-j)*logb);
		}
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=i-K;j>=0;j--)getmax(DP[i],DP[j]+ODD[i-j]);
	}
	return DP[N];
}
int main()
{
	freopen("C:\\Users\\Burney\\Desktop\\in.txt","r",stdin);
	freopen("C:\\Users\\Burney\\Desktop\\new.txt","w",stdout);
	LEVEL[0]=0.0;
	for(int i=1;i<=3000;i++)LEVEL[i]=LEVEL[i-1]+log(i);
	int testcount;scanf(1,"%d",&testcount);
	while(testcount--)
	{
		scanf(3,"%d%d%lf",&N,&K,&P);
		static int kase=1;
		printf("Case #%d: %.9f\n",kase++,Solve());
	}
	return 0;
}
