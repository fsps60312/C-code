#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cassert>
using namespace std;
const double PI=acos(-1.0);
struct Cycle
{
	double x,y,r;
	Cycle(){}
	Cycle(const double &_x,const double &_y,const double &_r):x(_x),y(_y),r(_r){}
	bool operator<(const Cycle &c)const
	{
		if(x!=c.x)return x<c.x;
		if(y!=c.y)return y<c.y;
		return r<c.r;
	}
	bool operator==(const Cycle &c)const{return x==c.x&&y==c.y&&r==c.r;}
}CYC[100];
double Sq(const double &a){return a*a;}
double Dist(const Cycle &a,const Cycle &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
bool Touch(const Cycle &a,const Cycle &b){return Dist(a,b)<a.r+b.r;}
bool Inside(const Cycle &a,const Cycle &b){return Dist(a,b)+a.r<=b.r;}
double Angle(const Cycle &o,const Cycle &a)
{
	double dx=a.x-o.x,dy=a.y-o.y;
	double ans=0.0;
	if(dy<0.0)dx=-dx,dy=-dy,ans+=PI;
	return ans+acos(dx/sqrt(dx*dx+dy*dy));
}
struct Segment
{
	double l,r;
	Segment(){}
	Segment(const double &_l,const double &_r):l(_l),r(_r){}
	bool operator<(const Segment &s)const{return l<s.l;}
};
int N;
int main()
{
	static int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf%lf",&CYC[i].x,&CYC[i].y,&CYC[i].r);
		sort(CYC,CYC+N),N=unique(CYC,CYC+N)-CYC;
//		printf("N=%d\n",N);
		double ans=0.0;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)if(j!=i&&Inside(CYC[i],CYC[j]))goto do_continue;
			static vector<Segment>seg;seg.clear();
			for(int j=0;j<N;j++)if(j!=i&&Touch(CYC[i],CYC[j])&&!Inside(CYC[j],CYC[i]))
			{
				//Dist(CYC[i],CYC[j])
				//cosA=(b*b+c*c-a*a)/2bc
				const double a=CYC[j].r,b=Dist(CYC[i],CYC[j]),c=CYC[i].r;
				const double angle=acos((b*b+c*c-a*a)/(2.0*b*c));
				const double mid=Angle(CYC[i],CYC[j]);
				const double l=mid-angle,r=mid+angle;
				seg.push_back(Segment(max(0.0,l),min(2.0*PI,r)));
				if(l<0.0)seg.push_back(Segment(l+2.0*PI,2.0*PI));
				if(r>=2.0*PI)seg.push_back(Segment(0.0,r-2.0*PI));
			}
			sort(seg.begin(),seg.end());
			static double cur;cur=0.0;
			for(const Segment &s:seg)
			{
				if(cur<s.l)ans+=CYC[i].r*(s.l-cur);
				if(s.r>cur)cur=s.r;
			}
			ans+=CYC[i].r*(2.0*PI-cur);
			do_continue:;
		}
		int b=0;
		while(ans<1.0)ans*=10.0,b--;
		while(ans>=10.0)ans/=10.0,b++;
		assert(b>0&&b<10);
		printf("%.2f %d\n",ans,b);
	}
	return 0;
}
