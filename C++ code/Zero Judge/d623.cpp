#include<cstdio>
#include<algorithm>
using namespace std;
bool Zero(double a){return abs(a)<1e-9;}
int main()
{
	double a,b,c,d;
	while(scanf("%lf%lf%lf%lf",&a,&b,&c,&d)==4)
	{
		if(a==0.0&&b==0.0&&c==0.0&&d==0.0)break;
		double det=a*d-b*c;
		if(Zero(det))puts("cheat!");
		else
		{
			printf("%.5lf %.5lf\n%.5lf %.5lf\n",d/det,-b/det,-c/det,a/det);
		}
	}
	return 0;
}
