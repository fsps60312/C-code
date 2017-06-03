#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const double INF=1e100,PI=acos(-1.0);
const int MAXN=65536;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
struct Complex
{
	double A,B;
	Complex():A(0.0),B(0.0){}
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
inline void FFT(const int N,const Complex *omega,const Complex *_s,Complex *_ans)
{
	static int a_base[2][MAXN];
	static Complex ra_base[2][MAXN];
	for(int i=0;i<N;i++)a_base[1][i]=i;
	static int depth,n,oi;
	depth=0,n=N,oi=1;
	static Complex *ans,*ra;
	static int *s,*a;
	for(depth=0;;depth^=1,n>>=1,oi<<=1)
	{
		s=a_base[depth^1],a=a_base[depth&1];
		ans=(n==N?_ans:ra_base[depth^1]);
		if(n==1){for(int i=0;i<N;++i)ans[i]=_s[s[i]];break;}
		assert(n>1);
		for(int offset=0,o=-1;offset<N;offset+=n)
		{
			for(int i=0;i<n;i+=2)a[++o]=s[offset+i];
			for(int i=1;i<n;i+=2)a[++o]=s[offset+i];
		}
	}
	for(depth^=1,n<<=1,oi>>=1;;depth^=1,n<<=1,oi>>=1)
	{
		ans=(n==N?_ans:ra_base[depth^1]),ra=ra_base[depth];
		for(int offset=0;offset<N;)
		{
			for(int i=0;i<n/2;++i,++offset)ans[offset]=ra[offset]+ra[offset+n/2]*omega[oi*i];
			for(int i=0;i<n/2;++i,++offset)ans[offset]=ra[offset-n/2]-ra[offset]*omega[oi*i];
		}
		if(n==N)break;
		assert(n<N);
	}
}
Complex OMEGA[16][MAXN],REOME[16][MAXN];
inline void GetCoefficient(const int time,const double *a,const double *b,double *ans)
{
	for(int n=1,d=0;!(time&(n-1));n<<=1,d++)
	{
//		Multiply(n,a+n,(b+time)-n,ans+time);
		const int m=n<<1;
		static Complex ca[MAXN],cb[MAXN],ma[MAXN],mb[MAXN],cans[MAXN];
		for(int i=0;i<n;i++)ca[i].A=a[n+i],cb[i].A=b[time-n+i];
		FFT(m,OMEGA[d],ca,ma);
		FFT(m,OMEGA[d],cb,mb);
		for(int i=0;i<m;i++)ma[i]=ma[i]*mb[i];
		FFT(m,REOME[d],ma,cans);
		for(int i=0;i<m;i++)ans[time+i]+=cans[i].A/m;
		for(int i=0;i<n;i++)ca[i].A=cb[i].A=0.0;
	}
}
struct Edge
{
	int A,B,COST;
	double P[MAXN],DP[MAXN],SUM[MAXN];
};
vector<Edge>EDGE;
int N,M,T,X;
vector<int>ET[50];
double DP[50][MAXN];
inline void BuildDist()
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
	for(int n=1,d=0;d<16;n<<=1,d++)
	{
		const int m=n*2;
		for(int i=0;i<m;i++)OMEGA[d][i]=Complex(cos(i*PI/n),sin(i*PI/n));
		for(int i=0;i<m;i++)REOME[d][i]=Complex(cos(-i*PI/n),sin(-i*PI/n));
	}
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
		e.SUM[T+1]=0.0;
		for(int j=T;j>=1;j--)e.SUM[j]=e.SUM[j+1]+e.P[j];
		EDGE.push_back(e);
		ET[e.A].push_back(i);
	}
	BuildDist();
	for(int time=1;time<=T;time++)
	{
		for(Edge &e:EDGE)
		{
			GetCoefficient(time,e.P,DP[e.B],e.DP);
//			if(T==19998)assert(0);
//			if(time==6000)assert(0);
			const double fine=DP[e.B][0]+(e.B==N-1?X:0);
			e.DP[time]+=e.SUM[time+1]*fine;
		}
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
