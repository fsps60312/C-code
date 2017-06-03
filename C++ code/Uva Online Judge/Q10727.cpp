#include<cstdio>
#include<map>
#include<cmath>
using namespace std;
const double INF=1e4,EXP=1e-9;
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
		ans+=exp(a*t.a+b*t.b);
	}
	return ans;
}
double F(double b)
{
	double l=-INF,r=INF,ml,mr;
	while(abs(r-l)>EXP)
	{
		ml=l+(r-l)/3.0;
		mr=r-(r-l)/3.0;
		if(getvalue(ml,b)>getvalue(mr,b))l=ml;
		else r=mr;
	}
	return l;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
//	double a=1.0;
//	while(1)
//	{
//		a*=10.0;
//		printf("%.10lf\n",a);
//	}
//log(p/(1-p)) = a + bn
	while(scanf("%d",&N)==1&&N)
	{
		TERM.clear(),TTERM.clear();
		TERM[Term(0,0)]=1;
		for(int i=0,n,w;i<N;i++)
		{
			scanf("%d%d",&n,&w);
			if(w)mul(1,n,0,0);
			else mul(0,0,-1,-n);
		}
		double l=-INF,r=INF,ml,mr;
		for(double i=-INF;i<=INF;i+=1.0)printf("%.4f\n",getvalue(i,0.0));
		for(double i=-INF;i<=INF;i+=1.0)printf(" %.4f\n",getvalue(0.0,i));
		while(abs(r-l)>EXP)
		{
			ml=l+(r-l)/3.0;
			mr=r-(r-l)/3.0;
			if(F(ml)>F(mr))l=ml;
			else r=mr;
			printf("l=%.4f r=%.4f\n",l,r);
		}
		printf("%.4f %.4f\n",F(l),l);
	}
	return 0;
}
