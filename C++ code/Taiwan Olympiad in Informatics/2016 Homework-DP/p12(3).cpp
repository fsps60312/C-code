#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
int N,R,G;
double P[1000];
const int MXN=1000;
double DP[MXN][7];//still i rounds to go, you have j dollar
int main()
{
	freopen("inn.txt","r",stdin);
	while(scanf("%d%d%d",&N,&R,&G)==3)
	{
		double sum=0.0;
		for(int i=0;i<N;i++)scanf("%lf",&P[i]),sum+=P[i];
		for(int i=0;i<=R*G;i++)
		{
			if(i/G==0)DP[0][i]=sum/N;
			else
			{
				double &v=DP[0][i]=0.0;
				for(int j=0;j<N;j++)v+=(1.0/N)*max(P[j],DP[0][i-G]);
			}
		}
		for(int round=1;round<MXN;round++)
		{
			for(int money=0;money<=R*G;money++)
			{
				if(money/G==0)DP[round][money]=(1.0*(sum/N)+round*DP[round-1][min(R*G,money+1)])/(round+1.0);
				else
				{
					double &v=DP[round][money]=0.0;
					for(int j=0;j<N;j++)
					{
						v+=(1.0/N)*max((1.0*P[j]+round*DP[round-1][min(R*G,money+1)])/(round+1.0),DP[round][money-G]);
					}
				}
			}
		}
		printf("%.9f\n",DP[MXN-1][R*G]);
	}
	return 0;
}
