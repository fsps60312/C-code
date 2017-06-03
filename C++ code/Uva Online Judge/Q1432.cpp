#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
void getmin(double &a,const double &b){if(b<a)a=b;}
const double PI=acos(-1.0);
int N,K,X[5000],Y[5000];
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
	int idx;
	Point(){}
	Point(const int &dx,const int &dy){radius=sqrt((double)dx*dx+(double)dy*dy);angle=Angle(dx,dy,radius);}
	bool operator<(const Point &p)const{return angle<p.angle;}
}P[5000];
struct Deq
{
	vector<Point>p;
	int l;
	void clear(){p.clear();l=0;}
	int Sz(){return p.size()-l;}
	bool empty(){return Sz()==0;}
	const Point &back(){return p[p.size()-1];}
	const Point &front(){return p[l];}
	void pop_back(){p.pop_back();}
	void pop_front(){l++;}
	void push_back(const Point &v){p.push_back(v);}
}DEQ;
double FanArea(const double &r,const double &a){return r*r*a*0.5;}
int main()
{
//	int x,y;while(scanf("%d%d",&x,&y)==2)printf("%.4f\n",Angle(x,y,sqrt(x*x+y*y)));
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&K)==2&&N&&K)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
			P[i]=Point(X[i],Y[i]);
			printf("(%d,%d)=>(%.2f,%.2f)\n",X[i],Y[i],P[i].angle,P[i].radius);
		}
		sort(P,P+N);
		for(int i=0;i<N;i++)
		{
			P[i].idx=i;
			printf("%.2f %.2f\n",P[i].angle,P[i].radius);
		}
		DEQ.clear();
		for(int i=N-K;i<N;i++)
		{
			P[i].idx-=N;
			P[i].angle-=2.0*PI;
			while(!DEQ.empty()&&DEQ.back().radius<=P[i].radius)DEQ.pop_back();
			DEQ.push_back(P[i]);
//			printf("frontidx=%d,radius=%.2f\n",DEQ.front().idx,DEQ.front().radius);
			P[i].idx+=N;
			P[i].angle+=2.0*PI;
		}
//		printf("sz=%d\n",DEQ.Sz());
		double ans=1e100;
		for(int i=0;i<N;i++)
		{
			while(!DEQ.empty()&&DEQ.front().idx<=i-K)DEQ.pop_front();
			while(!DEQ.empty()&&DEQ.back().radius<=P[i].radius)DEQ.pop_back();
			DEQ.push_back(P[i]);
			double angle;
			if(i-K+1>=0)angle=P[i].angle-P[i-K+1].angle;
			else angle=P[i].angle+2.0*PI-P[i-K+1+N].angle;
			printf("frontidx=%d,angle=%.2f,now%.2f,radius=%.2f\n",DEQ.front().idx,angle,P[i].angle,DEQ.front().radius);
			double ta=FanArea(DEQ.front().radius,angle);
			printf("%d:%.2f(%.2f,%.2f)\n",i,ta,P[i].angle,P[i].radius);
			getmin(ans,ta);
		}
		static int kase=1;
		printf("Case #%d: %.2f\n",kase++,ans);
	}
	return 0;
}
