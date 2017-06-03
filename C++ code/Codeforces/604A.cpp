#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const double S[5]={500, 1000, 1500, 2000, 2500};
double M[5],W[5],HS,HU;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lf",&M[0])==1)
	{
		for(int i=1;i<5;i++)scanf("%lf",&M[i]);
		for(int i=0;i<5;i++)scanf("%lf",&W[i]);
		scanf("%lf%lf",&HS,&HU);
		double ans=100.0*HS-50.0*HU;
		for(int i=0;i<5;i++)ans+=max(0.3*S[i],(1.0-M[i]/250.0)*S[i]-50.0*W[i]);
		printf("%.0f\n",ans);
	}
	return 0;
}
