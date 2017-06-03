#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const double EPS=1e-8,INF=1e100;
void getmax(double &a,const double b){if(b>a)a=b;}
struct SparseTable
{
	double MN[17][100000],MX[17][100000];
	int BIT[100000];
	void Build(const int n,const double *s)
	{
		for(int i=0;i<n;i++)MN[0][i]=MX[0][i]=s[i];
		for(int d=1;(1<<d)<=n;d++)
		{
			for(int i=0;i+(1<<d)<=n;i++)
			{
				MN[d][i]=min(MN[d-1][i],MN[d-1][i+(1<<(d-1))]);
				MX[d][i]=max(MX[d-1][i],MX[d-1][i+(1<<(d-1))]);
			}
		}
		for(int i=0,bit=0;i<n;i++)
		{
			while((1<<(bit+1))<=(i+1))bit++;
			BIT[i]=bit;
		}
	}
	double Query(const int l,const int r)const
	{
		assert(l<=r);
		const int bit=BIT[r-l];
		assert(l+(1<<bit)-1<=r&&l+(1<<(bit+1))-1>r);
		return max(MX[bit][l],MX[bit][r-(1<<bit)+1])-min(MN[bit][l],MN[bit][r-(1<<bit)+1]);
	}
};
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
Cycle MinCycle(const vector<Point>&ps,const int j,const int k)
{
	Cycle ans=Cycle(ps[j],ps[k]);
	for(int i=0;i<k;i++)if(!ans.Contains(ps[i]))ans=Cycle(ps[i],ps[j],ps[k]);
	return ans;
}
Cycle MinCycle(const vector<Point>&ps,const int j)
{
	Cycle ans=Cycle(ps[0],ps[j]);
	for(int i=1;i<j;i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,j,i);
	return ans;
}
Cycle MinCycle(const vector<Point>&ps)
{
	Cycle ans=Cycle(ps[0],0.0);
	for(int i=1;i<(int)ps.size();i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,i);
	return ans;
}
Point P[100000];
Cycle MinCycle(const int l,const int r)
{
	vector<Point>ps;
	for(int i=l;i<=r;i++)ps.push_back(P[i]);
	random_shuffle(ps.begin(),ps.end());
	return MinCycle(ps);
}
SparseTable SP[2];
bool SmallerThan(const int l,const int r,const double radius)
{
	for(int i=0;i<2;i++)
	{
//		printf("%d(%d,%d),%.9f\n",i,l,r,SP[i].Query(l,r));
		if(SP[i].Query(l,r)/2.0>radius)return false;
	}
	return MinCycle(l,r).r<=radius;
}
int N,M;
void BuildSP()
{
	static double s[100000];
	for(int i=0;i<N;i++)s[i]=P[i].x;
	SP[0].Build(N,s);
	for(int i=0;i<N;i++)s[i]=P[i].y;
	SP[1].Build(N,s);
//	for(int i=0;i<N;i++)s[i]=(P[i].x+P[i].y)/2.0;
//	SP[2].Build(N,s);
//	for(int i=0;i<N;i++)s[i]=(P[i].x-P[i].y)/2.0;
//	SP[3].Build(N,s);
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
			if(SmallerThan(i,mid,radius))l=mid;
			else r=mid-1;
		}
		ANS.push_back(MinCycle(i,r).o);
		i=r+1;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("wyk6b.in","r",stdin);
	srand(7122);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
	BuildSP();
	double l=0.0,r=2000000.0;
	for(;r-l>EPS;)
	{
		const double mid=0.5*(l+r);
		if(Solve(mid))r=mid;
		else l=mid;
	}
	printf("%.9f\n",r);
	assert(Solve(r));
	printf("%d\n",(int)ANS.size());
	for(int i=0;i<(int)ANS.size();i++)printf("%.9f %.9f\n",ANS[i].x,ANS[i].y);
//	for(;;);
	return 0;
}


