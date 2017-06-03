#include<cstdio>
#include<cmath>
const double PI=acos(-1.0);
double W,H,X,Y,R;
double Hypot(const double &a,const double &b){return sqrt(a*a+b*b);}
int main()
{
	while(scanf("%lf%lf%lf%lf%lf",&W,&H,&X,&Y,&R)==5)
	{
		bool ul,ur,dl,dr;
		ul=(Hypot(X-0.0,Y-H)>R);
		ur=(Hypot(X-W,Y-H)>R);
		dl=(Hypot(X-0.0,Y-0.0)>R);
		dr=(Hypot(X-W,Y-0.0)>R);
		double ans=2.0*PI;
		if(!ul)ans-=0.5*PI;
		else
		{
			if(H-Y<R)ans-=acos((H-Y)/R);
			if(X<R)ans-=acos(X/R);
		}
		if(!ur)ans-=0.5*PI;
		else
		{
			if(H-Y<R)ans-=acos((H-Y)/R);
			if(W-X<R)ans-=acos((W-X)/R);
		}
		if(!dl)ans-=0.5*PI;
		else
		{
			if(Y<R)ans-=acos(Y/R);
			if(X<R)ans-=acos(X/R);
		}
		if(!dr)ans-=0.5*PI;
		else
		{
			if(Y<R)ans-=acos(Y/R);
			if(W-X<R)ans-=acos((W-X)/R);
		}
		printf("%.9f\n",ans*R);
		break;
	}
	return 0;
}
