#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
const int MAX_N=500000;
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
};
struct Vector
{
	double x,y;
	Vector(){}
	Vector(const double _x,const double _y):x(_x),y(_y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.x-b.x,a.y-b.y);}
double Cross(const Vector &a,const Vector &b){return a.x*b.y-a.y*b.x;}
vector<vector<Point> >GetTobau(vector<Point>&s)
{
	sort(s.begin(),s.end(),[](const Point &a,const Point &b)->bool{return a.x!=b.x?a.x<b.x:a.y<b.y;});
	vector<vector<Point> >ret;
	vector<Point>ans;
	for(int cnt=0;cnt<2;cnt++)
	{
		ans.clear();
		for(const auto &p:s)
		{
			#define n ans.size()
			if(n>0&&ans.back().x==p.x&&ans.back().y==p.y)
			{
				continue;
			}
			while(n>=2&&Cross(ans[n-2]-ans[n-1],ans[n-1]-p)<0.0)ans.pop_back();
			#undef n
			ans.push_back(p);
		}
		ret.push_back(ans);
		reverse(s.begin(),s.end());
	}
	return ret;
}
double TriSearch(const vector<Point>&a,const Point &p)
{
	auto f=[&](int i)->double{return (a[i].x+p.x)/(a[i].y+p.y);};
	int l=0,r=(int)a.size()-1;
	while(r-l>=3)
	{
		const int ml=(l+l+r)/3,mr=(l+r+r)/3;
		if(f(ml)<f(mr))l=ml;
		else r=mr;
	}
	double ans=f(l);
	for(int i=l+1;i<=r;i++)getmax(ans,f(i));
	return ans;
}
void Solve(double &ans,const vector<Point>&a,vector<Point>&b)
{
	const auto &t=GetTobau(b);
	assert((int)t.size()==2&&!t[0].empty()&&!t[1].empty());
	for(const auto p:a)
	{
		getmax(ans,TriSearch(t[0],p));
		getmax(ans,TriSearch(t[1],p));
	}
}
struct React
{
	int u,a,p;
	React(){}
	React(const int _u,const int _a,const int _p):u(_u),a(_a),p(_p){}
};
bool operator<(const React &a,const React &b)
{
	return a.p*b.u<b.p*a.u;
}
int N;
React S[MAX_N];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		double ans=0.0;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d%d",&S[i].u,&S[i].a,&S[i].p);
			if(S[i].a>=0)
			{
				getmax(ans,(double)S[i].p/S[i].u);
				if(S[i].a==0)--i,--N;
			}
		}
		sort(S,S+N);
		vector<React>v;
		for(int i=N-1;i>=0;i--)
		{
			if(v.empty()||S[i].a*v.back().u>v.back().a*S[i].u)v.push_back(S[i]);
		}
		vector<Point>p[2];
		for(const auto &e:v)
		{
			(e.a>0?p[0]:p[1]).push_back(Point(e.p/fabs(e.a),e.u/fabs(e.a)));
		}
		if(!p[0].empty()&&!p[1].empty())Solve(ans,p[0],p[1]);
		printf("%.10f\n",ans);
	}
	return 0;
}
