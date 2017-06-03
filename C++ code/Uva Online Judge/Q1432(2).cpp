#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
void getmin(double &a,const double &b){if(b<a)a=b;}
const double PI=acos(-1.0);
int N,K;
void Swap(int &a,int &b){static int c;c=a,a=b,b=c;}
double Angle(int dx,int dy,const double &r)
{
	double ans=0.0;
	if(dx<0)
	{
		if(dy>=0)ans+=0.5*PI,Swap(dx,dy),dy=-dy;
		else ans+=PI,dx=-dx,dy=-dy;
	}
	else if(dy<0)ans+=1.5*PI,Swap(dx,dy),dx=-dx;
	if(dx==0)ans+=0.5*PI;
	else ans+=atan((double)dy/dx);
	return ans;
}
struct Point
{
	double angle,radius;
	Point(){}
//	Point(double a,double r):angle(a),radius(r){}
	Point(const int &dx,const int &dy){radius=sqrt((double)dx*dx+(double)dy*dy);angle=Angle(dx,dy,radius);}
}P[5000];
bool cmpr(const Point &a,const Point &b){return a.radius<b.radius;}
double FanArea(const double &r,const double &a){return r*r*a*0.5;}
vector<Point>S;
void InsertPoint(vector<Point>&s,const Point &p)
{
	int n=s.size();n--;
	s.push_back(Point());
	for(;n>=0&&p.angle<s[n].angle;n--)s[n+1]=s[n];
	s[++n]=p;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		static int kase=1;
		printf("Case #%d: ",kase++);
//		printf("N=%d,K=%d\n",N,K);
		for(int i=0;i<N;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			P[i]=Point(x,y);
		}
		if(K<=1){puts("0.00");continue;}
		sort(P,P+N,cmpr);
		double ans=1e100;
		S.clear();
		for(int i=0;i<N;i++)
		{
			InsertPoint(S,P[i]);
			if(i+1<N&&P[i].radius==P[i+1].radius)continue;
			if(S.size()<K)continue;
			double angle=1e100;
			for(int j=0;j<S.size();j++)
			{
				if(j)assert(S[j].angle>=S[j-1].angle);
				if(j+K-1<S.size())getmin(angle,S[j+K-1].angle-S[j].angle);
				else getmin(angle,S[j+K-1-S.size()].angle+2.0*PI-S[j].angle);
			}
			getmin(ans,FanArea(P[i].radius,angle));
		}
		printf("%.2f\n",ans);
	}
	return 0;
}
