#include<cstdio>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0);
int N;
struct Term
{
	int w,a,b;
	Term(){}
	Term(int w,int a,int b):w(w),a(a),b(b){}
	bool operator<(Term t)const{if(a!=t.a)return a<t.a;return b<t.b;}
};
vector<Term> TERM;
double getvalue(double a,double b)
{
//p==E^(a+bn)/(1+E^(a+bn))
//1-p==1/(1+E^(a+bn))
	double ans=1.0,e;
	for(int i=0;i<TERM.size();i++)
	{
		Term &t=TERM[i];
		e=exp(a*t.a+b*t.b);
		if(t.w)ans*=(1.0+e)/e;
		else ans*=1.0+e;
		ans*=2.0;
	}
	return ans;
}
double randdouble(){return (double)rand()/RAND_MAX;}
int main()
{
	srand(time(NULL)*2147483647*1000000007);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
//log(p/(1-p)) == a + bn
//p/(1-p)==E^(a+bn)
//p==E^(a+bn)-p*E^(a+bn)
//p(1+E^(a+bn))==E^(a+bn)
//p==E^(a+bn)/(1+E^(a+bn))
//1-p==1/(1+E^(a+bn))
//1/(1-p)==1+E^(a+bn)
//1/p==1+E^(-a-bn)
	while(scanf("%d",&N)==1&&N)
	{
		TERM.clear();
		for(int i=0,n,w;i<N;i++)
		{
			scanf("%d%d",&n,&w);
			TERM.push_back(Term(w,1,n));
		}
		double x=0.0,y=0.0,dis=100.0,ratio=0.999,k=0.1,value=getvalue(x,y),v,angle,dx,dy,dv;
		while(dis>EPS)
		{
			double angle=randdouble()*2.0*PI;
			dx=dis*sin(angle);
			dy=dis*cos(angle);
			v=getvalue(x+dx,y+dy);
			dv=v-value;
			if(dv<0.0||randdouble()<=exp(-dv/(k*dis)))x+=dx,y+=dy,value=v;
			dis*=ratio;
		}
		printf("%.4f %.4f\n",x,y);
	}
	return 0;
}
//-3.1748 1.5874
