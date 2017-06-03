#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cassert> 
using namespace std;
const double EPS=1e-9;
const double PI=acos(-1.0);
int N; 
struct Point
{
	double x,y;
	Point(){}
	Point(const double &_x,const double &_y):x(_x),y(_y){}
	Point operator-(const Point &p)const{return Point(x-p.x,y-p.y);}
	double Angle()const
	{
		double ans=0.0,x=this->x,y=this->y;
		if(x<0.0)
		{
			if(y>=0.0)ans+=0.5*PI,swap(x,y),y=-y;
			else ans+=1.0*PI,x=-x,y=-y;
		}
		else if(y<0.0)ans+=1.5*PI,swap(x,y),x=-x;
		double tmp=sqrt(x*x+y*y);
		if(y<x)return ans+asin(y/tmp);
		else return ans+acos(x/tmp);
	}
}HOUSE[1500];
double Dif(const double a,const double b){double ans=b-a;if(ans<=EPS)ans+=2.0*PI;return ans;}
int main()
{
//	Point p;
//	while(scanf("%lf%lf",&p.x,&p.y))printf("%.4f\n",p.Angle()/PI*180.0);
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lf%lf",&HOUSE[i].x,&HOUSE[i].y);
	double ans=N*(N-1.0)*(N-2.0)*(N-3.0)/24.0*2.0,drap=0.0;
	for(int i=0;i<N;i++)
	{
		vector<double>vec;
		for(int j=0;j<N;j++)if(j!=i)vec.push_back((HOUSE[j]-HOUSE[i]).Angle());
		sort(vec.begin(),vec.end());
		for(int j=0;j<N-1;j++)vec.push_back(vec[j]);
//for(int j=0;j<vec.size();j++)printf("(%.0lf,%.0lf)",vec[j].x,vec[j].y);puts("");
		double tmp=(N-1.0)*(N-2.0)*(N-3.0)/6.0;
		for(int l=0,r=1;l<N-1;l++)
		{
			while(r==l||Dif(vec[l],vec[r])<PI)r++,assert(r<vec.size());
			double n=r-l-1.0;
			tmp-=n*(n-1.0)/2.0;
		}
		drap+=tmp;
	}
//	printf("ans=%.4f,drap=%.4f\n",ans,drap);
	printf("%.4f\n",(ans-drap)/(N*(N-1.0)*(N-2.0)/6.0)+3.0);
	return 0;
}
