#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0),EPS=1e-9;
double X1,Y1,X2,Y2;
bool Quadrant[8];
void Solve(double _a1,double _a2,double &x,double &y,double &z)
{
	printf("%.4f %.4f\n",_a1,_a2);
	if(abs(_a1-0.5*PI)<EPS)
	{
		if(abs(_a2-0.5*PI)<EPS){x=0.0,y=10.0,z=0.0;return;}
		double t=tan(_a2);
		//t*z=x=10-z
		//x+z=10
		puts("_a1\n");
		y=0.0;
		z=10.0/(1.0+t);
		x=10-z;
		return;
	}
	if(abs(_a2-0.5*PI)<EPS)
	{
		double t=tan(_a1);
		//t*x=y=10-x
		//x+y=10
		//y=10-x
		printf("_a2=%.4f,%.4f\n",_a2,abs(_a2-0.5*PI));
		z=0.0;
		x=10.0/(1.0+t);
		y=10.0-x;
		return;
	}
	double f=tan(_a1),g=tan(_a2);
	printf("f=%.4f,g=%.4f\n",f,g);
	static double a,b,c;
//x+y+z=10
//y/x=tan(x)=a
//sqrt(x*x+y*y)/z=tan(y)=b
//y=ax
//bbzz=xx+yy
//(1+a)x+z=10
//bbzz=(1+aa)xx
//z=10-(1+a)x
//bbzz=bb(100+(1+2a+aa)xx-(20+20a)x)
//=100bb-(20+20a)bbx+(1+2a+aa)bbxx
//(bb+2abb+aabb-1-aa)xx+(-20bb-20abb)x+100bb=0
//x=
//	a=g*g*(1+2*f+f*f)-1-f*f;
//	b=-20.0*g*g*(1+f);
//	c=100.0*g*g;
//	x=(-b+sqrt(b*b-4.0*a*c))/(2.0*a);
//	y=g*x;
//	z=10.0-x-y;
	a=g*g*(1+2*f+f*f)-1-f*f;
	b=-20.0*g*g*(1+f);
	c=100.0*g*g;
	x=(-b+sqrt(b*b-4.0*a*c))/(2.0*a);
	y=g*x;
	z=10.0-x-y;
	printf("varify:%.4f %.4f\n",y/x-tan(_a1),sqrt(x*x+y*y)/z-tan(_a2));
}
double Solve()
{
//	printf("%.4f %.4f %.4f %.4f\n",X1,Y1,X2,Y2);
	double ans=1e100;
	double x1,y1,z1,x2,y2,z2;
	Solve(X1,Y1,x1,y1,z1),Solve(X2,Y2,x2,y2,z2);
	printf("(%.4f,%.4f,%.4f)(%.4f,%.4f,%.4f)\n",x1,y1,z1,x2,y2,z2);
	return 0.0;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int x1,y1,x2,y2;
	while(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)==4&&!(x1==-1&&y1==-1&&x2==-1&&y2==-1))
	{
		while(x1>=90)x1-=90,x2-=90;
		if(y1>90)y1=180-y1,y2=180-y2;
		if(x2<0)x2+=360;
		for(int i=0;i<8;i++)Quadrant[i]=false;
		if(y2<=90)
		{
			if(x2>=0&&x2<=90)Quadrant[0]=true;
			if(x2>=90&&x2<=180)Quadrant[1]=true;
			if(x2>=180&&x2<=270)Quadrant[2]=true;
			if(x2>=270||x2<=0)Quadrant[3]=true;
		}
		if(y2>=90)
		{
			if(x2>=0&&x2<=90)Quadrant[4]=true;
			if(x2>=90&&x2<=180)Quadrant[5]=true;
			if(x2>=180&&x2<=270)Quadrant[6]=true;
			if(x2>=270||x2<=0)Quadrant[7]=true;
		}
		while(x2>=90)x2-=90;
		if(y2>90)y2=180-y2;
//		x1%=180,y1%=180,x2%=180,y2%=180;
//		if(x1>90)x1-=180;if(y1>90)y1-=180;
//		if(x2>90)x2-=180;if(y2>90)y2-=180;
		printf("%d %d %d %d\n",x1,y1,x2,y2);
		X1=x1*PI/180.0,Y1=y1*PI/180.0,X2=x2*PI/180.0,Y2=y2*PI/180.0;
		static int kase=1;
		printf("Case %d: %.4f\n",kase++,Solve());
	}
	return 0;
}
