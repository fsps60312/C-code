#include<cstdio>
#include<cmath>
const double PI=acos(-1.0),EPS=1e-9;
int N;
double R,V,S,F;
int main()
{
	scanf("%d%lf%lf",&N,&R,&V);
	while(N--)
	{
		scanf("%lf%lf",&S,&F);
		double len=F-S,ans=0.0;
		double remain=fmod(len,2.0*PI*R);
		ans+=len-remain;
		remain*=0.5;
		double l=0.0,r=PI;
		while(r-l>EPS)
		{
			double mid=0.5*(l+r);
			if(mid*R+R*sin(mid)<remain)l=mid;
			else r=mid;
		}
		ans+=2.0*(0.5*(l+r)*R);
		printf("%.9f\n",ans/V);
	}
	return 0;
}
