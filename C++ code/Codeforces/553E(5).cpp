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
inline Complex operator*(const Complex &a,const Complex &b){return Complex(a.A*b.A-a.B*b.B,a.A*b.B+b.A*a.B);}
inline Complex operator+(const Complex &a,const Complex &b){return Complex(a.A+b.A,a.B+b.B);}
inline Complex operator-(const Complex &a,const Complex &b){return Complex(a.A-b.A,a.B-b.B);}
inline char GetChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
inline int GetInt()
{
	char c=GetChar();
	while(c<'0'||'9'<c)c=GetChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=GetChar();
	return v; 
}
void FFT(const int N,const int n,const int oi,const vector<Complex>&omega,const vector<Complex>&s,vector<Complex>&ans)
{
	assert((int)s.size()==N&&(int)ans.size()==N);
	if(n==1){for(int i=0;i<N;i++)ans[i]=s[i];return;}
	assert(n%2==0);
	vector<Complex>a,ra;
	for(int offset=0;offset<N;offset+=n)
	{
		for(int i=0;i<n;i+=2)a.push_back(s[offset+i]);
		for(int i=1;i<n;i+=2)a.push_back(s[offset+i]);
	}
	ra.resize(N);
	FFT(N,n/2,oi*2,omega,a,ra);
	for(int offset=0;offset<N;offset+=n)
	{
		for(int i=0;i<n/2;i++)ans[offset+i]=ra[offset+i]+ra[offset+n/2+i]*omega[oi*i];
		for(int i=0;i<n/2;i++)ans[offset+n/2+i]=ra[offset+i]-ra[offset+n/2+i]*omega[oi*i];
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
	FFT(n*2,n*2,1,omega,ca,ma);
	FFT(n*2,n*2,1,omega,cb,mb);
	for(int i=0;i<n*2;i++)ma[i]=ma[i]*mb[i];
	for(int i=0;i<n*2;i++)omega[i]=Complex(cos(-i*PI/n),sin(-i*PI/n));
	FFT(n*2,n*2,1,omega,ma,cans);
	for(int i=0;i<n*2;i++)ans[i]+=cans[i].A/(n*2.0);
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
	N=GetInt(),M=GetInt(),T=GetInt(),X=GetInt();
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0;i<M;i++)
	{
		static Edge e;
		e.A=GetInt(),e.B=GetInt(),e.COST=GetInt();
		--e.A,--e.B;
		for(int j=1;j<=T;j++)e.P[j]=GetInt()/100000.0,e.DP[j]=0;
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
	return 0;
}
