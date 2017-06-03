#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0),EPS=1e-9,INF=1e100;
int Sign(const double v){if(fabs(v)<EPS)return 0;return v<0.0?-1:1;}
int Sign(const double a,const double b){return Sign(a-b);}
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
	bool Same(const Point &p)const{return Sign(x,p.x)==0&&Sign(y,p.y)==0;}
	Point operator+(const Point &p)const{return Point(x+p.x,y+p.y);}
	Point operator-(const Point &p)const{return Point(x-p.x,y-p.y);}
	double Cross(const Point &p)const{return x*p.y-y*p.x;}//sin
	double Dot(const Point &p)const{return x*p.x+y*p.y;}//cos
}P[1000];
bool InRange(const double o,const double a,const double b){return Sign(a,o)==Sign(o,b);}
struct Segment
{
	Point p1,p2;
	Segment(){}
	Segment(const Point &_p1,const Point &_p2):p1(_p1),p2(_p2){}
	Segment Inverse()const{return Segment(p2,p1);}
	bool IsParallel(const Segment &l)const{return Sign((p2.x-p1.x)*(l.p2.y-l.p1.y),(l.p2.x-l.p1.x)*(p2.y-p1.y))==0;}
	double Cross(const Point &p){return (p2-p1).Cross(p-p1);}
	Point Intersection(const Segment &l)const
	{
		//p1.x+t(p2.x-p1.x)=l.p1.x+T(l.p2.x-l.p1.x),p1.y+t(p2.y-p1.y)=l.p1.y+T(l.p2.y-l.p1.y)
		//t(p2.x-p1.x)-T(l.p2.x-l.p1.x)=l.p1.x-p1.x,t(p2.y-p1.y)-T(l.p2.y-l.p1.y)=l.p1.y-p1.y
		const double a=p2.x-p1.x,b=-(l.p2.x-l.p1.x),c=l.p1.x-p1.x;
		const double A=p2.y-p1.y,B=-(l.p2.y-l.p1.y),C=l.p1.y-p1.y;
		//at+bT=c,At+BT=C
		//Bat+BbT=Bc,Abt+BbT=Cb
		//(Ba-Ab)t=Bc-Cb
		const double t=(B*c-C*b)/(B*a-A*b);
		return Point(p1.x+t*(p2.x-p1.x),p1.y+t*(p2.y-p1.y));
	}
	double IntersectionDistance(const Segment &l)const
	{
		const double a=p2.x-p1.x,b=-(l.p2.x-l.p1.x),c=l.p1.x-p1.x;
		const double A=p2.y-p1.y,B=-(l.p2.y-l.p1.y),C=l.p1.y-p1.y;
		const double t=(B*c-C*b)/(B*a-A*b);
		return t;
	}
	double IntersectionDistance(const Point &p)const
	{
		if(fabs(p2.x-p1.x)>fabs(p2.y-p1.y))return (p.x-p1.x)/(p2.x-p1.x);
		else return (p.y-p1.y)/(p2.y-p1.y);
	}
	bool ExcludeIntersected(const Segment &l)const
	{
		const double t=IntersectionDistance(l);
		return Sign(0.0,t)==-1&&Sign(t,1.0)==-1;
	}
	bool BothExcludeIntersected(const Segment &l)const
	{
		return ExcludeIntersected(l)&&l.ExcludeIntersected(*this);
	}
	bool IncludePoint(const Point &p)const
	{
		return Sign((p.x-p1.x)*(p2.y-p.y),(p2.x-p.x)*(p.y-p1.y))==0\
			&&InRange(p.x,p1.x,p2.x)\
			&&InRange(p.y,p1.y,p2.y);
	}
	bool IsOnLine(const Point &p)const
	{
		return p1.Same(p)||IsParallel(Segment(p1,p));
	}
	double Angle()const
	{
		double _x=p2.x-p1.x,_y=p2.y-p1.y,x,y,ans=0.0;
		if(_x>0.0&&_y>=0.0)x=_x,y=_y,ans=0.0*PI;
		else if(_x<=0.0&&_y>0.0)x=_y,y=-_x,ans=0.5*PI;
		else if(_x<0.0&&_y<=0.0)x=-_x,y=-_y,ans=1.0*PI;
		else if(_x>=0.0&&_y<0.0)x=-_y,y=_x,ans=1.5*PI;
		else assert(0);
		return ans+atan2(y,x);
	}
};
struct Deq
{
	Segment S[1000];
	int L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const Segment &v){S[++R]=v;}
	void PopBack(){R--;}
	Segment Front(const int i)const{return S[L+i];}
	Segment Back(const int i)const{return S[R-i];}
	int Size()const{return R-L+1;}
	Segment operator[](const int i){return S[L+i];}
};
bool SHADOW[1000];
int N;
bool GetHalfPlaneIntersection(vector<Segment>&segs,vector<Point>&ps)
{
	sort(segs.begin(),segs.end(),[](const Segment &a,const Segment &b)->bool{return a.Angle()<b.Angle();});
	static Deq deq;
	deq.Clear();
	for(int i=0;i<N;i++)
	{
		bool usable=true;
		while(deq.Size()&&Sign(deq.Back(0).Angle(),segs[i].Angle()-PI)==1)
		{
			if(deq.Back(0).IsParallel(segs[i]))
			{
				if(Sign(deq.Back(0).Cross(segs[i].p1))==1){usable=false;break;}
			}
			else if(deq.Size()>=2)
			{
				if(Sign(deq.Back(0).IntersectionDistance(segs[i]),\
					deq.Back(0).IntersectionDistance(deq.Back(1).Inverse()))==1)break;
			}
			deq.PopBack();
		}
		if(deq.Size()&&Sign(deq.Back(0).Angle(),segs[i].Angle()-PI)<=0)return false;
		if(usable)deq.PushBack(segs[i]);
	}
	if(deq.Size()<3)return false;
	if(Sign(deq.Back(0).Angle(),deq.Front(0).Angle()+PI)<=0)return false;
	ps.clear();
	ps.push_back(deq.Front(0).Intersection(deq.Back(0)));
	for(int i=1;i<deq.Size();i++)ps.push_back(deq[i-1].Intersection(deq[i]));
	return true;
}
bool Solve()
{
	if(true)
	{
		bool light=false,dark=false;
		for(int i=0;i<N;i++)
		{
			if(!SHADOW[i])light=true;
			else dark=true;
		}
		if(!light)return false;
		if(!dark)
		{
			vector<Segment>segs;
			for(int i=1;i<=N;i++)segs.push_back(Segment(P[i-1],P[i%N]));
			vector<Point>ps;
			return GetHalfPlaneIntersection(segs,ps);
		}
	}
	if(true)
	{
		int start=0;
		for(int i=0;i<N;i++)if(!SHADOW[i]){start=(i+1)%N;break;}
		rotate(P,P+start,P+N);
		rotate(SHADOW,SHADOW+start,SHADOW+N);
	}
	vector<int>bounds;
	for(int i=0;i<N;i++)if(SHADOW[(i+N-1)%N]!=SHADOW[i])bounds.push_back(i);
	assert(bounds.size()%2==0);
	for(int i=1;i<(int)bounds.size();i+=2)
	{
		const Segment l=Segment(P[bounds[i-1]],P[bounds[i]]);
		for(int j=bounds[i-1];j<bounds[i];j++)
		{
			if(l.IncludePoint(P[j])&&Sign((l.p2-l.p1).Cross(P[j+1]-l.p1))==-1)return false;
			if(l.IncludePoint(P[j+1])&&Sign((l.p1-l.p2).Cross(P[j]-l.p2))==1)return false;
			if(l.BothExcludeIntersected(Segment(P[j],P[j+1])))return false;
		}
	}
	if(bounds.size()==2)
	{
		vector<Segment>segs;
		for(int i=1;i<=N;i++)if(bounds[1]<=i-1||i%N<=bounds[0])
		{
			segs.push_back(Segment(P[i-1],P[i%N]));
		}
		vector<Point>ps;
		GetHalfPlaneIntersection(segs,ps);
		const int n=ps.size();
		const Segment shade=Segment(P[bounds[0]],P[bounds[1]]);
		vector<double>intersect_points;
		for(int i=1;i<=n;i++)if(Segment(ps[i-1],ps[i%n]).ExcludeIntersected(shade))
		{
			intersect_points.push_back(shade.IntersectionDistance(Segment(ps[i-1],ps[i%n])));
		}
		for(int i=0;i<n;i++)if(shade.IsOnLine(ps[i]))intersect_points.push_back(shade.IntersectionDistance(ps[i]));
		if(intersect_points.size()<=1)return false;
		assert(intersect_points.size()==2);
		for(const auto v:intersect_points)if(Sign(v,0.0)==-1||Sign(1.0,v)==-1)return true;
		return false;
	}
	else
	{
		const Segment seg1=Segment(P[bounds[0]],P[bounds[1]]),seg2=Segment(P[bounds[2]],P[bounds[3]]);
		if(seg1.IsParallel(seg2))return false;
		const Point p=seg1.Intersection(seg2);
		for(int i=5;i<(int)bounds.size();i+=2)if(!Segment(P[bounds[i-1]],P[bounds[i]]).IsOnLine(p))return false;
		bool *vis=new bool[N];
		for(int i=0;i<N;i++)vis[i]=false;
		for(int i=1;i<(int)bounds.size();i++)for(int j=bounds[i-1];j<bounds[i];j++)vis[j]=true;
		vector<int>ids;
		for(int i=0;i<N;i++)if(!vis[i])ids.push_back(i);
		delete[]vis;
		for(int i=1;i<=(int)ids.size();i++)if(Sign((P[ids[i-1]]-p).Cross(P[ids[i%ids.size()]]-p))>=0)return false;
		return true;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
		for(int i=0;i<N;i++)
		{
			static char type[2];
			scanf("%s",type);
			if(type[0]=='C')SHADOW[i]=true;
			else if(type[0]=='S')SHADOW[i]=false;
			else assert(0);
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
