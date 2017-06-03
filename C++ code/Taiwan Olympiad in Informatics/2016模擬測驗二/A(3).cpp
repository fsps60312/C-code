#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0),EPS=1e-8;
double Angle(const double x,const double y)
{
	if(y>=0.0&&x>0.0)return atan2(y,x);
	if(y>0.0&&x<=0.0)return 0.5*PI+atan2(-x,y);
	else if(y<=0.0&&x<0.0)return 1.0*PI+atan2(-y,-x);
	else if(y<0.0&&x>=0.0)return 1.5*PI+atan2(x,-y);
	else assert(0);
	return -1.0;
}
double OX,OY,X[500],Y[500];
int N;
pair<double,double>Segment(const int i1,const int i2)
{
	double a=Angle(X[i1]-OX,Y[i1]-OY),b=Angle(X[i2]-OX,Y[i2]-OY);
	assert(0.0<=a&&a<=2.0*PI),assert(0.0<=b&&b<=2.0*PI);
	double angle=b-a;
	if(angle<0.0)angle+=2.0*PI;
	assert(angle>=0.0&&angle<2.0*PI);
	if(angle<PI)return make_pair(a,b);
	else return make_pair(b,a);
}
void getmax(double &a,const double b){if(b>a)a=b;}
bool Solve()
{
	vector<pair<double,double> >segs;
	for(int i=0;i<N;i++)
	{
		const pair<double,double>&p=Segment(i,(i+1)%N);
		if(p.first<p.second)segs.push_back(p);
		else segs.push_back(make_pair(p.first,2.0*PI)),segs.push_back(make_pair(0.0,p.second));
	}
	sort(segs.begin(),segs.end());
	double r=0.0;
	for(const auto &p:segs)
	{
		assert(p.first<=p.second);
		if(p.first<=r+EPS)getmax(r,p.second);
		else return false;
	}
	return r+EPS>=2.0*PI;
}
int main()
{
//	assert(fabs(atan2(sqrt(3.0),1.0)-PI/3.0)<EPS);
//	freopen("in.txt","r",stdin);
	assert(scanf("%lf%lf",&OX,&OY)==2);
	assert(scanf("%d",&N)==1);
	assert(N>=3&&N<=500);
	for(int i=0;i<N;i++)assert(scanf("%lf%lf",&X[i],&Y[i])==2);
	puts(Solve()?"YES":"NO");
	return 0;
}
