#include<cstdio>
#include<cmath>
const double PI=acos(-1.0);
double W,H,X,Y,R;
double Hypot(const double &a,const double &b){return sqrt(a*a+b*b);}
double max(const double &a,const double &b){return a>b?a:b;}
int main()
{
	while(scanf("%lf%lf%lf%lf%lf",&W,&H,&X,&Y,&R)==5)
	{
		double ans;
		if(X>=0.0&&Y>=0.0&&X<=W&&Y<=H)
		{
			bool ul,ur,dl,dr;
			ul=(Hypot(X-0.0,Y-H)>R);
			ur=(Hypot(X-W,Y-H)>R);
			dl=(Hypot(X-0.0,Y-0.0)>R);
			dr=(Hypot(X-W,Y-0.0)>R);
			ans=2.0*PI;
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
		}
		else if(X>=0.0&&X<=W)
		{
			ans=PI;
			double y;
			if(Y<0.0)y=0.0-Y;
			else y=Y-H;
			if(y>=R)ans=0.0;
			else
			{
				ans-=max(X>=R?-1e100:acos(X/R),asin(y/R));
				ans-=max(W-X>=R?-1e100:acos((W-X)/R),asin(y/R));
			}
		}
		else if(Y>=0.0&&Y<=H)
		{
			ans=PI;
			double x;
			if(X<0.0)x=0.0-X;
			else x=X-W;
			if(x>=R)ans=0.0;
			else
			{
				ans-=max(Y>=R?-1e100:acos(Y/R),asin(x/R));
				ans-=max(H-Y>=R?-1e100:acos((H-Y)/R),asin(x/R));
			}
		}
		else
		{
			double x,y;
			if(X<0.0)x=0.0-X;
			else x=X-W;
			if(Y<0.0)y=0.0-Y;
			else y=Y-H;
			if(Hypot(x,y)>=R)ans=0.0;
			else
			{
				ans=0.5*PI;
				ans-=asin(x/R);
				ans-=asin(y/R);
			}
		}
		printf("%.9f\n",ans*R);
	}
	return 0;
}
