#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
using namespace std;
const double PI=acos(-1.0),EPS=1e-8;
struct Vector
{
	double x,y;
	Vector(){}
	Vector(const double _x,const double _y):x(_x),y(_y){}
};
bool IsParallel(const Vector &a,const Vector &b){return fabs(a.x*b.y-a.y*b.x)<EPS;}
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.x-b.x,a.y-b.y);}
bool Intersected(const Point &pa,const Point &pb,const Point &pc,const Point &pd)
{
	if(IsParallel(pb-pa,pd-pc))return false;
	const double a=pa.x,b=pa.y,c=pc.x,d=pc.y;
	const double x=pb.x-pa.x,y=pb.y-pa.y,X=pd.x-pc.x,Y=pd.y-pc.y;
	const double t=((c*Y-a*Y)-(d*X-b*X))/(x*Y-y*X);
	const double T=((y*c-y*a)-(x*d-x*b))/(x*Y-y*X);
	return 0.0<t&&t<1.0&&0.0<T&&T<1.0;
}
Point Intersection(const Point &pa,const Point &pb,const Point &pc,const Point &pd)
{
	const double a=pa.x,b=pa.y,c=pc.x,d=pc.y;
	const double x=pb.x-pa.x,y=pb.y-pa.y,X=pd.x-pc.x,Y=pd.y-pc.y;
	const double t=((c*Y-a*Y)-(d*X-b*X))/(x*Y-y*X);
	const double T=((y*c-y*a)-(x*d-x*b))/(x*Y-y*X);
	const Point p1=Point(a+t*x,b+t*y),p2=Point(c+T*X,d+T*Y);
	assert(fabs(p1.x-p2.x)<EPS&&fabs(p1.y-p2.y)<EPS);
	return Point(0.5*(p1.x+p2.x),0.5*(p1.y+p2.y));
}
double Angle(const Vector &v)
{
	const double x=v.x,y=v.y;
	if(y>=0.0&&x>0.0)return atan2(y,x);
	if(y>0.0&&x<=0.0)return 0.5*PI+atan2(-x,y);
	else if(y<=0.0&&x<0.0)return 1.0*PI+atan2(-y,-x);
	else if(y<0.0&&x>=0.0)return 1.5*PI+atan2(x,-y);
	else assert(0);
	return -1.0;
}
//struct Segment
//{
//	Point a,b;
//	Segment(){}
//	Segment(const Point &_a,const Point &_b):a(_a),b(_b){}
//};
Point O;
vector<Point>P;
void AddPoint(const Point &p)
{
	for(int i=1;i<(int)P.size();i++)if(Intersected(P[i-1],P[i],P.back(),p))
	{
		const Point q=Intersection(P[i-1],P[i],P.back(),p);
		P.resize(i);
		P.push_back(q);
	}
	P.push_back(p);
}
double AngleChanged(const int i1,const int i2)
{
	double a=Angle(P[i1]-O),b=Angle(P[i2]-O);
	double pos=b-a,neg=a-b;
	if(pos<0.0)pos+=2.0*PI;
	if(neg<0.0)neg+=2.0*PI;
//	printf("pos=%.3f,neg=%.3f\n",pos/PI*180,neg/PI*180);
	assert(pos>=0.0&&neg>=0.0&&fabs(pos+neg-2.0*PI)<EPS);
	if(pos<neg)return pos;
	else return -neg;
}
int main()
{
	assert(fabs(atan2(sqrt(3.0),1.0)-PI/3.0)<EPS);
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf",&O.x,&O.y)==2)
	{
		if(true)
		{
			int n;scanf("%d",&n);
			P.clear();
			for(int i=0;i<n;i++)
			{
				static Point p;
				scanf("%lf%lf",&p.x,&p.y);
				AddPoint(p);
			}
		}
//		for(int i=0;i<(int)P.size();i++)printf("(%.3f,%.3f)\n",P[i].x,P[i].y);
		double angle=0.0;
		for(int i=1;i<(int)P.size();i++)
		{
			angle+=AngleChanged(i-1,i);
		}
		angle+=AngleChanged((int)P.size()-1,0);
//		printf("angle=%.3f\n",angle/PI*180);
		if(fabs(angle-0.0)<EPS)puts("NO");
		else if(fabs(angle-2.0*PI)<EPS||fabs(angle+2.0*PI)<EPS)puts("YES");
		else assert(0);
	}
	return 0;
}
