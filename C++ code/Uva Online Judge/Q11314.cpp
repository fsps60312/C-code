#include<cstdio>
#include<cmath>
using namespace std;
int T;
double AX,AY,BX,BY;
inline double Dis(const double &a,const double &b){return sqrt(a*a+b*b);}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf",&AX,&AY,&BX,&BY);
		//sqrt(AX^2+(AY-Y)^2)+sqrt((BX-X)^2+BY^2)+sqrt(X^2+Y^2)
		printf("%.3f\n",Dis(AX-BX,AY-BY)+Dis(BX+AX,AY+BY));
	}
	return 0;
}
