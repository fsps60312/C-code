#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const double EPS=1e-8;
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
	bool operator==(const Point &p)const{return x==p.x&&y==p.y;}
};
Point MidPoint(const Point &a,const Point &b){return Point(0.5*(a.x+b.x),0.5*(a.y+b.y));}
double Sq(const double v){return v*v;}
double Dist(const Point &a,const Point &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
Point Excenter(const Point &a,const Point &b,const Point &c)
{
	if(a==b)return MidPoint(a,c);
	if(a==c)return MidPoint(a,b);
	if(b==c)return MidPoint(a,b);
	const Point ab=MidPoint(a,b),bc=MidPoint(b,c);
	const double ax=a.y-b.y,ay=b.x-a.x,cx=b.y-c.y,cy=c.x-b.x;
	//ab.x+t*ax==bc.x+T*cx, ab.y+t*ay==bc.y+T*cy
	//ab.x-bc.x+t*ax==T*cx, ab.y-bc.y+t*ay==T*cy
	//(ab.x-bc.x+t*ax)/cx==(ab.y-bc.y+t*ay)/cy
	//t=((ab.y-bc.y)/cy-(ab.x-bc.x)/cx)/((ax/cx)-(ay/cy))
	const double t=((ab.y-bc.y)*cx-(ab.x-bc.x)*cy)/((ax*cy)-(ay*cx));
	return Point(ab.x+t*ax,ab.y+t*ay);
}
struct Cycle
{
	Point o;
	double r;
	Cycle(){}
	Cycle(const Point &_o,const double _r):o(_o),r(_r){}
	Cycle(const Point &a,const Point &b):o(MidPoint(a,b)),r(Dist(a,b)/2.0){}
	Cycle(const Point &a,const Point &b,const Point &c):o(Excenter(a,b,c)),r((Dist(o,a)+Dist(o,b)+Dist(o,c))/3.0){}
	bool Contains(const Point &p)const{return Dist(o,p)<=r+EPS;}//EPS is crutial
};
struct Vector
{
	vector<vector<Point>*>pss;
	const Point &operator[](int id)const
	{
		for(int i=0;i<(int)pss.size();i++)
		{
			const vector<Point>&ps=*pss[i];
			if(id<(int)ps.size())return ps[id];
			id-=ps.size();
		}
		assert(0);
		static Point error;return error;
	}
};
struct SegTree
{
	vector<Point>S[400000];
	void Build(const int id,const int l,const int r,const Point *data)
	{
		S[id].clear();
		for(int i=l;i<=r;i++)S[id].push_back(data[i]);
		random_shuffle(S[id].begin(),S[id].end());
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid,data),Build(id*2+1,mid+1,r,data);
		}
	}
	void Query(const int id,const int l,const int r,const int bl,const int br,Vector &ans)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){ans.pss.push_back(S+id);return;}
		const int mid=(l+r)/2;
		Query(id*2,l,mid,bl,br,ans),Query(id*2+1,mid+1,r,bl,br,ans);
	}
}SEG_TREE;
Cycle MinCycle(const Vector &ps,const int j,const int k)
{
	Cycle ans=Cycle(ps[j],ps[k]);
	for(int i=0;i<k;i++)if(!ans.Contains(ps[i]))ans=Cycle(ps[i],ps[j],ps[k]);
	return ans;
}
Cycle MinCycle(const Vector &ps,const int j)
{
	Cycle ans=Cycle(ps[0],ps[j]);
	for(int i=1;i<j;i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,j,i);
	return ans;
}
Cycle MinCycle(const Vector &ps)
{
	Cycle ans=Cycle(ps[0],0.0);
	int sz=0;
	for(int i=0;i<(int)ps.pss.size();i++)sz+=ps.pss[i]->size();
	for(int i=1;i<sz;i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,i);
	return ans;
}
Point P[100000];
int N,M;
Cycle MinCycle(const int l,const int r)
{
	Vector ps;SEG_TREE.Query(1,0,N-1,l,r,ps);
	return MinCycle(ps);
}
vector<Point>ANS;
bool Solve(const double radius)
{
	ANS.clear();
	for(int i=0;i<N;)
	{
		if((int)ANS.size()>=M)return false;
		int l=i,r=N-1;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(MinCycle(i,mid).r<=radius)l=mid;
			else r=mid-1;
		}
		ANS.push_back(MinCycle(i,r).o);
		i=r+1;
	}
	return true;
}
int main()
{
	srand(7122);
//	freopen("in.txt","r",stdin);
//	freopen("wyk10a.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
	SEG_TREE.Build(1,0,N-1,P);
	double l=0.0,r=2000000.0;
	for(;r-l>EPS;)
	{
		const double mid=0.5*(l+r);
//		if(mid==l||mid==r)break;
//		printf("(%.9f,%.9f)\n",l,r);
		if(Solve(mid))r=mid;
		else l=mid;
	}
	printf("%.9f\n",r);
	assert(Solve(r));
	printf("%d\n",(int)ANS.size());
	for(int i=0;i<(int)ANS.size();i++)printf("%.9f %.9f\n",ANS[i].x,ANS[i].y);
	return 0;
}
