#include<cstdio>
#include<algorithm>
using namespace std;
double N;
double A,B,C;
double Solve()
{
	double exp=40.0*A+60.0*B+100.0*C;
	return A*max(40.0,exp)+B*max(60.0,exp)+C*max(100.0,exp);
}
int main()
{
	while(scanf("%lf",&N)==1)
	{
		scanf("%lf%lf%lf",&A,&B,&C);
		A/=100.0,B/=100.0,C/=100.0;
		printf("%.10f\n",N*Solve());
	}
	return 0;
}
