#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0);
class Vector
{
	private:
		int x,y;
		Vector(){}
		int Cross(const Vector &p)const{return x*p.y-y*p.x;}//sin
		int Dot(const Vector &p)const{return x*p.x+y*p.y;}//cos
	public:
		Vector(const int _x,const int _y):x(_x),y(_y){}
		bool IsOnLeft(const Vector &v)const{return Cross(v)>0;}
		bool IsOnRight(const Vector &v)const{return Cross(v)<0;}
		bool IsOnLeftOrSame(const Vector &v)const{return Cross(v)>=0;}
		bool IsOnRightOrSame(const Vector &v)const{return Cross(v)<=0;}
		bool IsSame(const Vector &v)const{return Cross(v)==0&&Dot(v)>=0;}
//	void Print()const{printf("vector(%d,%d)\n",x,y);}
};
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	bool Same(const Point &p)const{return x==p.x&&y==p.y;}
	Vector operator-(const Point &p)const{return Vector(x-p.x,y-p.y);}
}P[1000];
struct Fraction
{
	int up,down;
	Fraction(){}
	Fraction(const int _up,const int _down):up(_up),down(_down){if(down<0)up*=-1,down*=-1;}
	bool operator<(const Fraction &f)const{return up*f.down<f.up*down;}
	bool operator<=(const Fraction &f)const{return up*f.down<=f.up*down;}
	bool operator!=(const Fraction &f)const{return up*f.down!=f.up*down;}
	bool operator==(const Fraction &f)const{return up*f.down==f.up*down;}
//	void Print()const{printf("fraction(%d,%d)\n",up,down);}
};
struct Segment
{
	Point p1,p2;
	Segment(){}
	Segment(const Point &_p1,const Point &_p2):p1(_p1),p2(_p2){}
	Segment Inverse()const{return Segment(p2,p1);}
	Vector ToVector()const{return p2-p1;}
	bool IsParallel(const Segment &l)const{return ToVector().IsSame(l.ToVector());}
	Fraction IntersectionDistance(const Segment &l)const
	{
		//p1.x+t(p2.x-p1.x)=l.p1.x+T(l.p2.x-l.p1.x),p1.y+t(p2.y-p1.y)=l.p1.y+T(l.p2.y-l.p1.y)
		//t(p2.x-p1.x)-T(l.p2.x-l.p1.x)=l.p1.x-p1.x,t(p2.y-p1.y)-T(l.p2.y-l.p1.y)=l.p1.y-p1.y
		const int a=p2.x-p1.x,b=-(l.p2.x-l.p1.x),c=l.p1.x-p1.x;
		const int A=p2.y-p1.y,B=-(l.p2.y-l.p1.y),C=l.p1.y-p1.y;
		//at+bT=c,At+BT=C
		//Bat+BbT=Bc,Abt+BbT=Cb
		//(Ba-Ab)t=Bc-Cb
		return Fraction(B*c-C*b,B*a-A*b);
	}
	Fraction IntersectionDistance(const Point &p)const
	{
		if(abs(p2.x-p1.x)>abs(p2.y-p1.y))return Fraction(p.x-p1.x,p2.x-p1.x);
		else return Fraction(p.y-p1.y,p2.y-p1.y);
	}
	bool ExcludeIntersected(const Segment &l)const
	{
		const Fraction t=IntersectionDistance(l);
		return Fraction(0,1)<t&&t<Fraction(1,1);
	}
	bool BothExcludeIntersected(const Segment &l)const
	{
		return ExcludeIntersected(l)&&l.ExcludeIntersected(*this);
	}
	bool InRange(const int o,const int a,const int b)const{return (a<=o&&o<=b)||(b<=o&&o<=a);}
	bool IncludePoint(const Point &p)const
	{
		return (p.x-p1.x)*(p2.y-p.y)==(p2.x-p.x)*(p.y-p1.y)\
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
	void Intersection(const Segment &l,double &x,double &y)const
	{
		//p1.x+t(p2.x-p1.x)=l.p1.x+T(l.p2.x-l.p1.x),p1.y+t(p2.y-p1.y)=l.p1.y+T(l.p2.y-l.p1.y)
		//t(p2.x-p1.x)-T(l.p2.x-l.p1.x)=l.p1.x-p1.x,t(p2.y-p1.y)-T(l.p2.y-l.p1.y)=l.p1.y-p1.y
		const double a=p2.x-p1.x,b=-(l.p2.x-l.p1.x),c=l.p1.x-p1.x;
		const double A=p2.y-p1.y,B=-(l.p2.y-l.p1.y),C=l.p1.y-p1.y;
		//at+bT=c,At+BT=C
		//Bat+BbT=Bc,Abt+BbT=Cb
		//(Ba-Ab)t=Bc-Cb
		const double t=(B*c-C*b)/(B*a-A*b);
		x=p1.x+t*(p2.x-p1.x);
		y=p1.y+t*(p2.y-p1.y);
	}
};
struct Deq
{
	Segment S[1000];
	int L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const Segment &v){S[++R]=v;}
	void PopBack(){R--;}
	void PopFront(){L++;}
	Segment Front(const int i)const{return S[L+i];}
	Segment Back(const int i)const{return S[R-i];}
	int Size()const{return R-L+1;}
	Segment operator[](const int i){return S[L+i];}
};
bool SHADOW[1000];
int N;
bool CmpAngle(const Segment &a,const Segment &b){return a.Angle()>b.Angle();}
bool GetHalfPlaneIntersection(vector<Segment>&segs,vector<Segment>&ans)
{
	sort(segs.begin(),segs.end(),CmpAngle);
	static Deq deq;
	deq.Clear();
	for(int i=0;i<(int)segs.size();i++)
	{
		const Segment &seg=segs[i];
		bool usable=true;
		while(deq.Size()&&deq.Back(0).ToVector().IsOnRightOrSame(seg.ToVector()))
		{
			if(deq.Back(0).IsParallel(seg))
			{
				if(deq.Back(0).ToVector().IsOnLeftOrSame(seg.p1-deq.Back(0).p1)){usable=false;break;}
			}
			else if(deq.Size()>=2)
			{
				if(deq.Back(0).IntersectionDistance(deq.Back(1))<deq.Back(0).IntersectionDistance(seg))break;
			}
			else break;
			deq.PopBack();
		}
		if(deq.Size())
		{
//			deq.Back(0).ToVector().Print(),seg.ToVector().Print();
			if(!deq.Back(0).ToVector().IsOnRightOrSame(seg.ToVector()))return false;
		}
		if(usable)deq.PushBack(seg);
	}
	if(deq.Size()<3)return false;
	if(!deq.Back(0).ToVector().IsOnRight(deq.Front(0).ToVector()))return false;
	while(deq.Front(0).IntersectionDistance(deq.Front(1))<=deq.Front(0).IntersectionDistance(deq.Back(0)))deq.PopFront();
	while(deq.Back(0).IntersectionDistance(deq.Front(0))<=deq.Back(0).IntersectionDistance(deq.Back(1)))deq.PopBack();
	assert(deq.Size()>=3);
	for(int i=0;i<deq.Size();i++)ans.push_back(deq[i]);
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
			vector<Segment>ans;
			return GetHalfPlaneIntersection(segs,ans);
		}
	}
	if(true)
	{
		int start=0;
		for(int i=1;i<=N;i++)if(!SHADOW[i-1]&&SHADOW[i%N]){start=i%N;break;}
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
			if(l.IncludePoint(P[j])&&l.ToVector().IsOnRight(P[j+1]-l.p1))return false;
			if(l.IncludePoint(P[j+1])&&l.Inverse().ToVector().IsOnLeft(P[j]-l.p2)>0)return false;
			if(l.BothExcludeIntersected(Segment(P[j],P[j+1])))return false;
		}
	}
	if(bounds.size()==2)
	{
		vector<Segment>segs;
		if(true)
		{
			vector<Segment>tmp;
			for(int i=1;i<=N;i++)if(bounds[1]<=i-1||i%N<=bounds[0])
			{
				tmp.push_back(Segment(P[i-1],P[i%N]));
			}
			if(!GetHalfPlaneIntersection(tmp,segs))return false;
//			printf("segs.size()=%d\n",segs.size());
		}
		const int n=segs.size();
		const Segment shade=Segment(P[bounds[0]],P[bounds[1]]);
		for(int i=0;i<n;i++)if(shade.IsOnLine(segs[i].p1)&&shade.IsOnLine(segs[i].p2))return false;
		vector<Fraction>f;
		for(int i=0;i<n;i++)if(!shade.IsParallel(segs[i]))
		{
			const Fraction f1=segs[i].IntersectionDistance(segs[(i+n-1)%n]);
			const Fraction f2=segs[i].IntersectionDistance(segs[(i+1)%n]);
			const Fraction fo=segs[i].IntersectionDistance(shade); 
			if((f1<fo&&fo<f2)||(f2<fo&&fo<f1))f.push_back(shade.IntersectionDistance(segs[i]));
		}
//		printf("f.size()=%d\n",(int)f.size());
		for(int i=0;i<n;i++)
		{
			const Segment &s1=segs[i],&s2=segs[(i+1)%n];
			if(shade.IntersectionDistance(s1)==shade.IntersectionDistance(s2))
			{
				if(shade.ToVector().IsOnLeft(s1.ToVector())!=shade.ToVector().IsOnLeft(s2.ToVector()))return false;
				f.push_back(shade.IntersectionDistance(s1));
			}
		}
		if(f.empty())return false;
//		printf("f.size()=%d\n",(int)f.size());
		assert(f.size()==2);
		for(int i=0;i<(int)f.size();i++)if(f[i]<Fraction(0,1)||Fraction(1,1)<f[i])return true;
		return false;
	}
	else
	{
		const Segment seg1=Segment(P[bounds[0]],P[bounds[1]]),seg2=Segment(P[bounds[2]],P[bounds[3]]);
		if(seg1.IsParallel(seg2))return false;
		const Fraction fo=seg1.IntersectionDistance(seg2);
		vector<pair<Segment,Fraction> >range;
		range.push_back(make_pair(seg1,fo));
		for(int i=3;i<(int)bounds.size();i+=2)
		{
			const Segment &seg=Segment(P[bounds[i-1]],P[bounds[i]]);
			if(seg1.IsParallel(seg))
			{
				if(!seg.IsOnLine(seg1.p1))return false;
				range.push_back(make_pair(seg,seg.IntersectionDistance(seg1.p1)));
			}
			else
			{
				if(seg1.IntersectionDistance(seg)!=fo)return false;
				range.push_back(make_pair(seg,seg.IntersectionDistance(seg1)));
			}
		}
		printf("range.size()=%d\n",(int)range.size());
		for(int i=0;i<(int)range.size();i++)
		{
			const pair<Segment,Fraction>&p=range[i];
			const Fraction &f1=(Fraction(0,1)<p.second?Fraction(0,1):p.second);
			const Fraction &f2=(Fraction(0,1)<p.second?p.second:Fraction(0,1));
			for(int j=0;j<N;j++)
			{
				const Segment &seg=Segment(P[j],P[(j+1)%N]);
				if(!p.first.IsParallel(seg)&&p.first.BothExcludeIntersected(seg))
				{
					const Fraction &f=p.first.IntersectionDistance(seg);
					if(f1<f&&f<f2)return false;
				}
				if(p.first.IsOnLine(P[j]))
				{
					const Fraction &f=p.first.IntersectionDistance(P[j]);
					if(f1<f&&f<f2)
					{
						const Segment &reg=Segment(P[(j+N-1)%N],P[j]);
						if(p.first.IsParallel(seg))
						{
							if(!SHADOW[j])return false;
						}
						else if(p.first.IsParallel(reg))
						{
							if(!SHADOW[(j+N-1)%N])return false;
						}
						else
						{
							if(p.first.ToVector().IsOnLeft(seg.ToVector())==p.first.ToVector().IsOnLeft(reg.ToVector()))return false;
						}
					}
				}
			}
		}
		bool *vis=new bool[N];
		for(int i=0;i<N;i++)vis[i]=false;
		for(int i=1;i<(int)bounds.size();i+=2)for(int j=bounds[i-1];j<bounds[i];j++)vis[j]=true;
		vector<int>seg_ids;
		for(int i=0;i<N;i++)if(!vis[i])seg_ids.push_back(i);
		delete[]vis;
		for(int i=1;i<=(int)seg_ids.size();i++)
		{
			double x,y;
			seg1.Intersection(seg2,x,y);
			const Point &p1=P[seg_ids[i-1]],&p2=P[seg_ids[i%seg_ids.size()]];
			const double x1=p1.x-x,y1=p1.y-y,x2=p2.x-x,y2=p2.y-y;
			if(x1*y2-x2*y1>=0.0)return false;
		}
		return true;
	}
}
int main()
{
//	freopen("gob3.in","r",stdin);
	freopen("inn.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].x,&P[i].y);
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
/*
6
2 4
3 3
4 4
3 1
2 3
0 -1
S
C
S
S
C
S
*/
