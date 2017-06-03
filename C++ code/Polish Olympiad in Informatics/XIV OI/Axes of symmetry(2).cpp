#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
struct Point
{
	double X,Y;
	Point(){}
	Point(const double &_X,const double &_Y):X(_X),Y(_Y){}
};
Point MidPoint(const Point &a,const Point &b){return Point(0.5*(a.X+b.X),0.5*(a.Y+b.Y));}
bool Same(const double a,const double b){return fabs(a-b)<EPS;}
bool SameAngle(const Point &a,const Point &b,const Point &c)
{
	return Same(a.X*b.Y-b.X*a.Y,b.X*c.Y-c.X*b.Y)&&Same(a.X*b.X+a.Y*b.Y,b.X*c.X+b.Y*c.Y);
}
int N;//N<=100000
vector<Point>P;
void MinusCenter()
{
	double xsum=0,ysum=0;
	assert((int)P.size()==N);
	for(int i=0;i<N;i++)xsum+=P[i].X,ysum+=P[i].Y;
	xsum/=N,ysum/=N;
	for(int i=0;i<N;i++)P[i].X-=xsum,P[i].Y-=ysum;
}
vector<int>Z;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		vector<Point>s;
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			s.push_back(Point(x,y));
		}
		P.clear();
		for(int i=0;i<N;i++)
		{
			P.push_back(s[i]);
			P.push_back(MidPoint(s[i],s[(i+1)%N]));
		}
		N*=2;
		MinusCenter();
		for(int i=0;i<N*2;i++)P.push_back(P[i]);
		Z.resize(P.size());
		Z[0]=1;
		for(int i=1,mx=0;i<(int)Z.size();i++)
		{
			if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-1+1,Z[mx-(i-mx)]);
			else Z[i]=1;
			while(i-Z[i]>=0&&i+Z[i]<(int)Z.size()&&SameAngle(P[i-Z[i]],P[i],P[i+Z[i]]))++Z[i];
			if(i+Z[i]>=mx+Z[mx])mx=i;
		}
		int ans=0;
		for(int i=N;i<N*2;i++)if(Z[i]>N)++ans;
		assert(ans%2==0);
		printf("%d\n",ans/2);
	}
	return 0;
}
