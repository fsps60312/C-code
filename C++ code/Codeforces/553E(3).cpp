#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const double INF=1e100,PI=acos(-1.0);
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
struct Complex
{
	double A,B;
	Complex(){}
	Complex(const double _A,const double _B):A(_A),B(_B){}
};
Complex operator*(const Complex &a,const Complex &b){return Complex(a.A*b.A-a.B*b.B,a.A*b.B+b.A*a.B);}
Complex operator+(const Complex &a,const Complex &b){return Complex(a.A+b.A,a.B+b.B);}
Complex operator-(const Complex &a,const Complex &b){return Complex(a.A-b.A,a.B-b.B);}
void FFT(const int n,const int oi,const vector<Complex>&omega,const vector<Complex>&s,vector<Complex>&ans)
{
	assert((int)s.size()==n&&(int)ans.size()==n);
	if(n==1){ans[0]=s[0];return;}
	assert(n%2==0);
	vector<Complex>a,b,ra,rb;
	for(int i=0;i<n;i+=2)a.push_back(s[i]),b.push_back(s[i+1]);
	ra.resize(n/2),rb.resize(n/2);
	FFT(n/2,oi*2,omega,a,ra);
	FFT(n/2,oi*2,omega,b,rb);
	for(int i=0;i<n/2;i++)
	{
		ans[i]=ra[i]+rb[i]*omega[oi*i];
		ans[n/2+i]=ra[i]-rb[i]*omega[oi*i];
	}
}
void Multiply(const int n,const double *a,const double *b,double *ans)
{
//	for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans[i+j]+=a[i]*b[j];return;
	vector<Complex>ca,cb,ma,mb,cans;
	ca.resize(n*2),cb.resize(n*2),ma.resize(n*2),mb.resize(n*2),cans.resize(n*2);
	for(int i=0;i<n;i++)ca[i]=Complex(a[i],0.0),cb[i]=Complex(b[i],0.0),assert(a[i]<0.5*INF&&b[i]<0.5*INF);
	for(int i=n;i<n*2;i++)ca[i]=cb[i]=Complex(0.0,0.0);
	vector<Complex>omega;omega.resize(n*2);
	for(int i=0;i<n*2;i++)omega[i]=Complex(cos(i*PI/n),sin(i*PI/n));
//	printf("(%f,%f)\n",omega[n].A,omega[n].B);
	FFT(n*2,1,omega,ca,ma);
	FFT(n*2,1,omega,cb,mb);
	for(int i=0;i<n*2;i++)ma[i]=ma[i]*mb[i];
	for(int i=0;i<n*2;i++)omega[i]=Complex(cos(-i*PI/n),sin(-i*PI/n));
	FFT(n*2,1,omega,ma,cans);
//	printf("a=");for(int i=0;i<n*2;i++)printf(" %.3lf",a[i]);puts("");
//	printf("b=");for(int i=0;i<n*2;i++)printf(" %.3lf",b[i]);puts("");
//	printf("c=");for(int i=0;i<n*2;i++)printf(" %.3lf",cans[i].A/(n*2.0));puts("");
	for(int i=0;i<n*2;i++)ans[i]+=cans[i].A/(n*2.0);//,printf("cans[i].B=%.10f\n",cans[i].B);
}
int T;
void GetCoefficient(const int time,const double *a,const double *b,double *ans,const double fine)
{
	for(int n=1;time%n==0;n<<=1)Multiply(n,a+n,(b+time)-n,ans+time);
	for(int i=time+1;i<=T;i++)ans[time]+=a[i]*fine;
}
struct Edge
{
	int A,B,COST;
	double P[200001],DP[200001];
};
vector<Edge>EDGE;
int N,M,X;
vector<int>ET[50];
double DP[50][200001];
void BuildDist()
{
	static double dist[50][50];
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)dist[i][j]=(i==j?0:INF);
	for(const Edge &e:EDGE)dist[e.A][e.B]=e.COST;
	for(int k=0;k<N;k++)for(int i=0;i<N;i++)for(int j=0;j<N;j++)getmin(dist[i][j],dist[i][k]+dist[k][j]);
	for(int i=0;i+1<N;i++)DP[i][0]=dist[i][N-1]+X;
	DP[N-1][0]=0.0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	EDGE.reserve(100);
	while(scanf("%d%d%d%d",&N,&M,&T,&X)==4)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static Edge e;
			scanf("%d%d%d",&e.A,&e.B,&e.COST),--e.A,--e.B;
			for(int j=1;j<=T;j++)scanf("%lf",&e.P[j]),e.P[j]/=100000.0,e.DP[j]=0;
			EDGE.push_back(e);
			ET[e.A].push_back(i);
		}
		BuildDist();
		for(int time=1;time<=T;time++)
		{
			for(Edge &e:EDGE)GetCoefficient(time,e.P,DP[e.B],e.DP,DP[e.B][0]+(e.B==N-1?X:0));
			for(int i=0;i+1<N;i++)
			{
				double &dp=DP[i][time]=INF;
				for(const int ei:ET[i])getmin(dp,EDGE[ei].DP[time]+EDGE[ei].COST);
			}
			DP[N-1][time]=0.0;
		}
		printf("%.10f\n",DP[0][T]);
	}
	return 0;
}
