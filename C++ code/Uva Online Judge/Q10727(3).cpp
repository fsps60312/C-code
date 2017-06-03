#include<cstdio>
#include<map>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0);
int N;
struct Term
{
	int a,b;
	Term(){}
	Term(int a,int b):a(a),b(b){}
	bool operator<(Term t)const{if(a!=t.a)return a<t.a;return b<t.b;}
};
map<Term,int> TERM,TTERM;
void mul(int a1,int b1,int a2,int b2)
{
	for(map<Term,int>::iterator it=TERM.begin();it!=TERM.end();it++)
	{
		Term t=it->first;
		Term t1=Term(t.a+a1,t.b+b1);
		if(TTERM.find(t1)==TTERM.end())TTERM[t1]=0;
		TTERM[t1]+=it->second;
		t1=Term(t.a+a2,t.b+b2);
		if(TTERM.find(t1)==TTERM.end())TTERM[t1]=0;
		TTERM[t1]+=it->second;
	}
	TERM=TTERM;
	TTERM=map<Term,int>();
}
double getvalue(double a,double b)
{
	double ans=0.0;
	for(map<Term,int>::iterator it=TERM.begin();it!=TERM.end();it++)
	{
		Term t=it->first;
		ans+=it->second*exp(a*t.a+b*t.b);
	}
	return ans;
}
double randdouble(){return (double)rand()/RAND_MAX;}
int main()
{
	srand(time(NULL));
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
		TERM.clear(),TTERM.clear();
		TERM[Term(0,0)]=1;
		for(int i=0,n,w;i<N;i++)
		{
			scanf("%d%d",&n,&w);
			if(w)mul(0,0,-1,-n);
			else mul(0,0,1,n);
		}
		double x=0.0,y=0.0,dis=100.0,ratio=0.99,k=0.1,value=getvalue(x,y),v,angle,dx,dy,dv;
		while(dis>EPS)
		{
			double angle=randdouble()*2.0*PI;
			dx=dis*sin(angle);
			dy=dis*cos(angle);
//			printf("%.4f %.4f\n",sin(angle),cos(angle));
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
