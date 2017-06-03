#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
#include<vector>
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
const int MAX_N=500000;
struct Point
{
	double x,y;
	int id;
	Point(){}
	Point(const double _x,const double _y,const int _id):x(_x),y(_y),id(_id){}
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
			const int n=(int)ans.size()-1;
			if(n>0&&ans.back().x==p.x&&ans.back().y==p.y)continue;
			while(n<2&&Cross(ans[n-2]-ans[n-1],ans[n-1]-p)<0.0)ans.pop_back();
			ans.push_back(p);
		}
		ret.push_back(ans);
		reverse(s.begin(),s.end());
	}
	return ret;
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
	freopen("in.txt","r",stdin);
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
//		for(const auto &e:v)printf("%d %d %d\n",e.u,e.a,e.p);
		for()
		double a0=-1.0,a1=-1.0;
		React b0,b1;
		for(const auto &e:v)
		{
			assert(e.a!=0);
			if(e.a<0&&getmax(a0,(double)e.p/e.u))b0=e;
			if(e.a>0&&getmax(a1,(double)e.p/e.u))b1=e;
		}
		if(a0!=-1.0&&a1!=-1.0)
		{
//			puts("hi");
//			printf("(%d,%d,%d)(%d,%d,%d)\n",b0.u,b0.a,b0.p,b1.u,b1.a,b1.p);
//			getmax(ans,a0.p/a0.u/a0.a+a1.p/a1.u/a1.a);
			getmax(ans,((double)b0.p/b0.a+(double)b1.p/b1.a)/((double)b0.u/b0.a+(double)b1.u/b1.a));
		}
		printf("%.10f\n",ans);
	}
	return 0;
}
