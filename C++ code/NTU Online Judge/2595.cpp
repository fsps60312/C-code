#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
#include<utility>
using namespace std;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
const double EPS=1e-9,PI=acos(-1.0);
struct Point
{
	double _x,_y;
	Point(){}
	Point(const int x,const int y):_x(x),_y(y){}
};
double Hypot(const double a,const double &b){return sqrt(a*a+b*b);}
double Distance(const Point &a,const Point &b){return Hypot(a._x-b._x,a._y-b._y);}
double GetAngle(const double a,const double b,const double c)
{
	return acos((a*a+b*b-c*c)/(2.0*a*b));
}
double Angle(double angle)
{
	if(angle<0.0)angle+=2.0*PI;
	if(angle>2.0*PI)angle-=2.0*PI;
	assert(0.0<=angle&&angle<=2.0*PI);
	return angle;
}
int N;
double R1,R2;
void GetAngles(vector<double>&angles,const Point &o0,const Point &o1)
{
	if(Distance(o0,o1)-EPS>=R2+R1)return;
	if(Distance(o0,o1)+EPS<=R2-R1)return;
	const double mid_angle=atan2(o1._y-o0._y,o1._x-o0._x);
	const double dis=GetAngle(R2,Distance(o0,o1),R1);
	angles.push_back(Angle(mid_angle-dis));
	angles.push_back(Angle(mid_angle+dis));
}
void GetAngles(vector<double>&angles,const Point &o,const Point &p1,const Point &p2)
{
	const double a=p2.y-p1.y,b=p1.x-p2.x;
	const double dist=fabs(a*o.x+b*o.y-(a*p1.x+b*p1.y))/sqrt(a*a+b*b);
	
}
Point P[10];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lf%lf",&N,&R1,&R2)==3)
	{
		R1-=EPS,R2+=EPS;
		assert(0.0<R1&&R1<R2);
		for(int i=0;i<N;i++)scanf("%lf%lf",&P[i]._x,&P[i]._y);
		pair<double,Point>ans=make_pair(1e100,Point(0,0));
		for(int i=0;i<N;i++)
		{
			vector<double>angles;
			for(int j=0;j<N;j++)if(j!=i)GetAngles(angles,P[i],P[j]);
			for(int j=0;j<N;j++)if(j!=i)for(int k=j+1;k<N;k++)if(k!=i)GetAngles(angles,P[i],P[j],P[k]);
			angles.push_back(0.0),angles.push_back(2.0*PI);
			sort(angles.begin(),angles.end()),angles.resize(unique(angles.begin(),angles.end())-angles.begin());
			for(int j=1;j<(int)angles.size();j++)if(IsValid(P[i],(angles[j-1]+angles[j])/2.0))
			{
				getmin(ans,TrinarySearch(P[i],angles[j-1],angles[j])); 
			}
		}
		assert(ans.first<1e100);
		printf("%.10f %.10f\n",ans.second._x,ans.second._y);
	}
	return 0;
}
