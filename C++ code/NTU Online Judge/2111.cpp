#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const double EPS=1e-9;
struct Point
{
	double X,Y;
	Point(){}
	Point(const double _X,const double _Y):X(_X),Y(_Y){}
};
struct Vector
{
	double X,Y;
	Vector(){}
	Vector(const double _X,const double _Y):X(_X),Y(_Y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
double Cross(const Vector &a,const Vector &b){return (a.X*b.Y-a.Y*b.X)/max(fabs(a.X),fabs(a.Y))/max(fabs(b.X),fabs(b.Y));}
double Dot(const Vector &a,const Vector &b){return (a.X*b.X+a.Y*b.Y)/max(fabs(a.X),fabs(a.Y))/max(fabs(b.X),fabs(b.Y));}
int N;
Point P[1000],W;
void GetW()
{
	double sum=P[N-1].X*P[0].Y-P[N-1].Y*P[0].X;
	W=Point((P[0].X+P[N-1].X)/3.0*sum,(P[0].Y+P[N-1].Y)/3.0*sum);
	for(int i=1;i<N;i++)
	{
		const double area=P[i-1].X*P[i].Y-P[i-1].Y*P[i].X;
		W.X+=area*(P[i-1].X+P[i].X)/3.0;
		W.Y+=area*(P[i-1].Y+P[i].Y)/3.0;
		sum+=area;
	}
	W.X/=sum,W.Y/=sum;
}
vector<Point>HULL;
void BuildHull()
{
	HULL.clear();
	vector<Point>&up=HULL,down;
	up.push_back(P[0]);
	for(int i=1,sz=1;i<N;i++)
	{
		while(sz>=2&&Cross(up[sz-1]-up[sz-2],P[i]-up[sz-2])>-EPS)up.pop_back(),--sz;
		up.push_back(P[i]),++sz;
	}
	down.push_back(P[0]);
	for(int i=1,sz=1;i<N;i++)
	{
		while(sz>=2&&Cross(down[sz-1]-down[sz-2],P[i]-down[sz-2])<EPS)down.pop_back(),--sz;
		down.push_back(P[i]),++sz;
	}
	for(int i=(int)down.size()-2;i>=0;i--)HULL.push_back(down[i]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf",&P[i].X,&P[i].Y);
		GetW();
		sort(P,P+N,[](const Point &a,const Point &b)->bool{return fabs(a.X-b.X)<EPS?a.Y<b.Y:a.X<b.X;});
		BuildHull();
		int ans=0;
		for(int i=1;i<(int)HULL.size();i++)
		{
			if(Dot(W-HULL[i-1],HULL[i]-HULL[i-1])>EPS&&Dot(W-HULL[i],HULL[i-1]-HULL[i])>EPS)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
