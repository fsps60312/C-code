#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
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
		double tmp=x*x+y*y;
		if(y<x)return ans+asin(y/tmp);
		else return ans+acos(x/tmp);
	}
	bool operator<(const Point &p)const{return Angle()<p.Angle();}
}HOUSE[1500];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lf%lf",&HOUSE[i].x,&HOUSE[i].y);
	for(int i=0;i<N;i++)
	{
		vector<int>vec;
		for(int j=0;j<N;j++)if(j!=i)vec.push_back(HOUSE[j]-HOUSE[i]);
		sort(vec.begin(),vec.end());
		for(int j=0;j<N-1;j++)vec.push_back(vec[j]);
		for(int l=0,r=1;l<N-1;l++)
		{
			while(vec[j].Angle())
		}
	}
	return 0;
}
