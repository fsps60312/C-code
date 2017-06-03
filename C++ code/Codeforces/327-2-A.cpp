#include<cstdio>
double L,P,Q;
int main()
{
	scanf("%lf",&L);
	scanf("%lf%lf",&P,&Q);
	double t=L/(P+Q);
	double loc1=P*t;
	printf("%.9f\n",loc1);
	return 0;
}
