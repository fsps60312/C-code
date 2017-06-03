#include<cstdio>
#include<cmath>
#define abs(x) (x>=0.0?x:-(x))
const double SecPerDay=60.0*60.0*12.0;
const int DaySecs=60*60*12;
double K,M;
double mod(double a,double b){return a-b*(int)(a/b);}
int main()
{
//	freopen("in.txt","r",stdin);
	int a;
	while(scanf("%lf%lf",&K,&M)==2)
	{
		printf("%.0f %.0f ",K,M);
		K*=0.5,M*=0.5;
		M=abs(K-M);//time displacement
		M=SecPerDay/M;//days
		K=mod((SecPerDay-K)*M,SecPerDay);//time win
		a=(int)(K/60.0+0.5)%DaySecs;
		if(a<=59)printf("12:%02d\n",a);
		else printf("%02d:%02d\n",a/60,a%60);
	}
	return 0;
}
