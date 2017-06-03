#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
struct Point
{
	double X,Y;
	Point(){}
	Point(const double &_X,const double &_Y):X(_X),Y(_Y){}
};
Point MidPoint(const Point &a,const Point &b){return Point((a.X+b.X)/2,(a.Y+b.Y)/2);}
bool Same(const double a,const double b,const double eps){return fabs(a-b)<=eps*1e-11;}
bool SameAngle(const Point &a,const Point &b,const Point &c)
{
	return Same(a.X*b.Y-b.X*a.Y,b.X*c.Y-c.X*b.Y,fabs(a.X*b.Y)+fabs(b.X*a.Y)+fabs(b.X*c.Y)+fabs(c.X*b.Y))
		&&Same(a.X*b.X+a.Y*b.Y,b.X*c.X+b.Y*c.Y,fabs(a.X*b.X)+fabs(a.Y*b.Y)+fabs(b.X*c.X)+fabs(b.Y*c.Y));
}
int N;//N<=100000
vector<Point>P;
vector<int>Z;
#include<utility>
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		vector<int>xs,ys;
		long long xsum=0,ysum=0;
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			xs.push_back(x),ys.push_back(y);
			xsum+=x,ysum+=y;
		}
		P.clear();
		for(int i=0;i<N;i++)
		{
			const int j=(i+1)%N;
			const Point p0=Point((double)((long long)xs[i]*N-xsum)/N,(double)((long long)ys[i]*N-ysum)/N);
			const Point p1=Point((double)((long long)xs[j]*N-xsum)/N,(double)((long long)ys[j]*N-ysum)/N);
			P.push_back(p0);
			P.push_back(MidPoint(p0,p1));
		}
		N*=2;
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
		for(int i=N;i<N*2;i++)if(Z[i]>=N)++ans;
		assert(ans%2==0);
		printf("%d\n",ans/2);
	}
	return 0;
}
