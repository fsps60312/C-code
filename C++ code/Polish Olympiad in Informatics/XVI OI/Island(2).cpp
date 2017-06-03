#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
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
double Cross(const Vector &v1,const Vector &v2){return v1.X*v2.Y-v1.Y*v2.X;}
struct Ray
{
	Point P;
	Vector V;
	Ray(){}
	Ray(const Point &_P,const Vector &_V):P(_P),V(_V){}
	double Abs()const{return sqrt(V.X*V.X+V.Y*V.Y);}
};
double Intersection(const Ray &r1,const Ray &r2)
{
	//p1.x+t*v1.x=p2.x+T*v2.x
	//p1.y+t*v1.y=p2.y+T*v2.y
	//p1.x*v2.y+t*v1.x*v2.y=p2.x*v2.y+T*v2.x*v2.y
	//p1.y*v2.x+t*v1.y*v2.x=p2.y*v2.x+T*v2.y*v2.x
	//(v1.x*v2.y-v1.y*v2.x)t=(p2.x*v2.y-p1.x*v2.y)-(p2.y*v2.x-p1.y*v2.x)
	return ((r2.P.X*r2.V.Y-r1.P.X*r2.V.Y)-(r2.P.Y*r2.V.X-r1.P.Y*r2.V.X))/(r1.V.X*r2.V.Y-r1.V.Y*r2.V.X);
}
Point P[100000];
vector<int>BLOCKED[100000];
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("wsp2.in","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			P[i]=Point(x,y);
			BLOCKED[i].clear();
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			BLOCKED[a].push_back(b);
			BLOCKED[b].push_back(a);
		}
		for(int i=0;i<N;i++)sort(BLOCKED[i].begin(),BLOCKED[i].end());
		for(int i=0;i<N;i++)
		{
			for(int j=1;j<(int)BLOCKED[i].size();j++)assert(BLOCKED[i][j-1]<BLOCKED[i][j]);
		}
		vector<Ray>roads;
		for(int u=0;u<N;u++)
		{
			for(int nxt=N-1,cur=(int)BLOCKED[u].size()-1;roads.empty()||(Cross(roads.back().V,P[nxt]-P[u])<-EPS&&Intersection(roads.back(),Ray(P[u],P[nxt]-P[u]))<=1.0);nxt--)
			{
				if(cur!=-1&&nxt==BLOCKED[u][cur]){--cur;continue;}
				const Ray r=Ray(P[u],P[nxt]-P[u]);
				for(int sz=(int)roads.size();sz>=2&&Intersection(roads[sz-1],roads[sz-2])>Intersection(roads[sz-1],r);)roads.pop_back(),--sz;
				roads.push_back(r);
				break;
			}
		}
		assert(!roads.empty());
//		for(int i=0;i<(int)roads.size();i++)
//		{
//			Ray r=roads[i];
//			printf("(%f,%f)(%f,%f)\n",r.P.X,r.P.Y,r.V.X,r.V.Y);
//		}
		double ans;
		if((int)roads.size()==1)ans=roads[0].Abs();
		else
		{
			ans=roads[0].Abs()*Intersection(roads[0],roads[1]);
			const int sz=(int)roads.size();
			for(int i=1;i+1<sz;i++)
			{
				ans+=roads[i].Abs()*(Intersection(roads[i],roads[i+1])-Intersection(roads[i],roads[i-1]));
			}
			ans+=roads[sz-1].Abs()*(1.0-Intersection(roads[sz-1],roads[sz-2]));
		}
		printf("%.10f\n",ans);
	}
	return 0;
}
