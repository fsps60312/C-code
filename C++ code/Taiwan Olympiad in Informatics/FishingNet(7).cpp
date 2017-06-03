#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
struct Vector
{
	double x,y;
	Vector(){}
	Vector(const double _x,const double _y):x(_x),y(_y){}
};
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.x-b.x,a.y-b.y);}
double Cross(const Vector &a,const Vector &b){return a.x*b.y-a.y*b.x;}
int N;
vector<Point>S;
double DIST;
int CNT;
double Sq(const double v){return v*v;}
double Hypot(const Point &a,const Point &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
void Trim()
{
	DIST=0.0,CNT=0;
	sort(S.begin(),S.end());
	vector<bool>live;live.resize(S.size(),false);
	vector<int>ids;
	ids.push_back(0);
	int n=1;
	for(int i=1;i<(int)S.size();i++)
	{
		while(n>=2&&Cross(S[i]-S[ids[n-2]],S[ids[n-1]]-S[ids[n-2]])>0.0)ids.pop_back(),--n;
		ids.push_back(i),++n;
	}
	for(const int v:ids)live[v]=true;//,printf("(%.3f,%.3f)\n",S[v].x,S[v].y);
	for(int i=1;i<n;i++)DIST+=Hypot(S[ids[i-1]],S[ids[i]]);
	assert(n==(int)ids.size());
	CNT+=n-1;
//	printf("%d\n",(int)ids.size());
	ids.clear();
	ids.push_back(0);
	n=1;
	for(int i=1;i<(int)S.size();i++)
	{
		while(n>=2&&Cross(S[i]-S[ids[n-2]],S[ids[n-1]]-S[ids[n-2]])<0.0)ids.pop_back(),--n;
		ids.push_back(i),++n;
	}
	for(const int v:ids)live[v]=true;//,printf("(%.3f,%.3f)\n",S[v].x,S[v].y);puts("");
	for(int i=1;i<n;i++)DIST+=Hypot(S[ids[i-1]],S[ids[i]]);
	assert(n==(int)ids.size());
	CNT+=n-1;
//	printf("%d\n",(int)ids.size());
	vector<Point>nxts;
	for(int i=0;i<(int)S.size();i++)if(live[i])nxts.push_back(S[i]);
	S.swap(nxts);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	S.clear();
	for(int i=0;i<N;i++)
	{
		double x,y;scanf("%lf%lf",&x,&y);
		S.push_back(Point(x,y));
		if(S.size()>7021)Trim();
	}
	Trim();
	printf("%d %.10f\n",CNT,DIST);
}
