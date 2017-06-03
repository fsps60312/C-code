#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct rectangle
{
	double x1;
	double x2;
	double y1;
	double y2;
	bool check(double a,double b)
	{
		return a>x1&&a<x2&&b>y2&&b<y1;
	}
};
struct circle
{
	double x;
	double y;
	double r;
	bool check(double a,double b)
	{
		return (a-x)*(a-x)+(b-y)*(b-y)<r*r;
	}
};
struct triangle
{
	double x1;
	double x2;
	double x3;
	double y1;
	double y2;
	double y3;
	bool inside(double a,double b,double c,double d,double e,double f)
	{
		//x(a,b)+y(e,f)=(c,d)
		//ax+ey==c
		//bx+fy==d
		//abx+bey==bc		afx+efy==cf
		//abx+afy==ad		bex+efy==ed
		//(be-af)y==bc-ad	(af-be)x==cf-ed
		return (b*c-a*d)/(b*e-a*f)>0&&(c*f-e*d)/(a*f-b*e)>0;
	}
	bool check(double a,double b)
	{
		return inside(x2-x1,y2-y1,a-x1,b-y1,x3-x1,y3-y1)&&inside(x1-x2,y1-y2,a-x2,b-y2,x3-x2,y3-y2);
	}
};
struct shapetype
{
	char c[2];
	int index;
};
vector<rectangle> r;
vector<circle> c;
vector<triangle> t;
vector<shapetype> S;
shapetype tmp;
bool check(shapetype a,double x,double y)
{
	switch(a.c[0])
	{
		case'r':return r[a.index].check(x,y);
		case'c':return c[a.index].check(x,y);
		default:return t[a.index].check(x,y);
	}
}
int main()
{
	r.clear();
	c.clear();
	t.clear();
	S.clear();
	while(scanf("%s",tmp.c)==1)
	{
		if(tmp.c[0]=='*') break;
		switch(tmp.c[0])
		{
			case'r':
				{
					tmp.index=r.size();
					S.push_back(tmp);
					rectangle i;
					scanf("%lf%lf%lf%lf",&i.x1,&i.y1,&i.x2,&i.y2);
					r.push_back(i);
				}break;
			case'c':
				{
					tmp.index=c.size();
					S.push_back(tmp);
					circle i;
					scanf("%lf%lf%lf",&i.x,&i.y,&i.r);
					c.push_back(i);
				}break;
			default:
				{
					tmp.index=t.size();
					S.push_back(tmp);
					triangle i;
					scanf("%lf%lf%lf%lf%lf%lf",&i.x1,&i.y1,&i.x2,&i.y2,&i.x3,&i.y3);
					t.push_back(i);
				}break;
		}
	}
	double a,b;
	int T=0;
	while(scanf("%lf%lf",&a,&b)==2)
	{
		if(a==b&&b==9999.9) break;
		T++;
		bool included=false;
		for(int i=0;i<S.size();i++)
		{
			if(check(S[i],a,b))
			{
				included=true;
				printf("Point %d is contained in figure %d\n",T,i+1);
			}
		}
		if(!included) printf("Point %d is not contained in any figure\n",T);
	}
	return 0;
}
