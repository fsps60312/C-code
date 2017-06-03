#include<cstdio>
#include<cstdlib>
#include<cmath>
double p,q,r,s,t,u;
double absf(double a)
{
	return a>=0?a:-a;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%lf%lf%lf%lf%lf%lf",&p,&q,&r,&s,&t,&u)==6)
	{
		//p*e^-x+q*sin(x)+r*cos(x)+s*tan(x)+t*x^2==-u
		//p,r>=0
		//q,s,t<=0
		//+-+--
		//-+-++
		//f'(x)==p*e^-x+q*cos(x)+r*sin(x)+s*(1+tan(x)^2)+t*2x
		//+-+--
		//+-+
		//(tan(x+u)-tan(x))/u==(((tan(x)+tan(u))/(1-tan(x)tan(u)))-tan(x))/u
		//==((tan(x)+u)/(1-u*tan(x))-tan(x))/u
		//==(u+u*tan(x)^2)/u==1+tan(x)^2
		double Min=0,Max=1,mid;
		while(Max-Min>=1e-7)
		{
			mid=(Max+Min)/2;
			if(p*exp(-mid)+q*sin(mid)+r*cos(mid)+s*tan(mid)+t*mid*mid+u>0) Min=mid;
			else Max=mid;
		}
		mid=(Max+Min)/2;
		//mid=0.7554;
		//printf(" %lf %lf %lf\n",p*exp(-mid)+q*sin(mid)+r*cos(mid)+s*tan(mid)+t*mid*mid+u,Min,Max);
		if(absf(p*exp(-mid)+q*sin(mid)+r*cos(mid)+s*tan(mid)+t*mid*mid+u)>1e-5) printf("No solution\n");
		else printf("%.4lf\n",(Max+Min)/2);
	}
	return 0;
}
