#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
using namespace std;
const long double PI=acos((long double)-1.0),EPS=1e-9;
struct Complex
{
	long double a,b;
	Complex(){}
	Complex(const long double &_a,const long double &_b):a(_a),b(_b){}//:a(fmod(_a,(long double)MOD)),b(fmod(_b,(long double)MOD)){}
	Complex operator-()const{return Complex(-a,-b);}
};
Complex operator*(const Complex &c1,const Complex &c2){return Complex(c1.a*c2.a-c1.b*c2.b,c1.a*c2.b+c2.a*c1.b);}
Complex operator+(const Complex &c1,const Complex &c2){return Complex(c1.a+c2.a,c1.b+c2.b);}
Complex Omega(const int i,const int n)
{
	return Complex(cos(2.0*PI*i/n),sin(2.0*PI*i/n));
}
void DFT(const vector<Complex>&s,const int oa,const int on,vector<Complex>&ans)
{
	const int n=s.size();
//	printf("n=%d,omega=(%.9f,%.9f)\n",n,(double)omega.a,(double)omega.b);
	if(n==1)
	{
		ans.clear(),ans.push_back(s[0]);
		return;
	}
	vector<Complex>left_s,right_s,left_ans,right_ans;
	assert(n%2==0);
	for(int i=0;i<n;i++)(i&1?left_s:right_s).push_back(s[i]);//,printf("s[%d]=(%.9f,%.9f)\n",i,(double)s[i].a,(double)s[i].b);
	DFT(left_s,oa*2,on,left_ans);
	DFT(right_s,oa*2,on,right_ans);
	ans.resize(n);
	int x=0;
	for(int i=0;i<n/2;i++,x+=oa)
	{
		ans[i]=left_ans[i]*Omega(x,on)+right_ans[i];
		ans[i+n/2]=-left_ans[i]*Omega(x,on)+right_ans[i];
	}
}
vector<Complex>Mul(const vector<Complex>&a,const vector<Complex>&b)
{
	assert(a.size()==b.size());
	const int n=a.size();
	vector<Complex>da,db,ds;
//	if(true)
//	{
//		printf("omega=(%.9f,%.9f)\n",(double)omega.a,(double)omega.b);
//		for(const auto &p:a)printf("(%.9f,%.9f)\n",(double)p.a,(double)p.b);puts("");
//		DFT(a,omega,da);
//		for(const auto &p:da)printf("(%.9f,%.9f)\n",(double)p.a,(double)p.b);puts("");
//		DFT(da,Complex(omega.a,-omega.b),db);
//		for(const auto &p:db)printf("(%.9f,%.9f)\n",(double)p.a/n,(double)p.b/n);puts("");
////		exit(0);
//	}
	DFT(a,1,n,da);
	DFT(b,1,n,db);
	assert((int)da.size()==n&&(int)db.size()==n);
	for(int i=0;i<n;i++)ds.push_back(da[i]*db[i]);
	vector<Complex>s;
	DFT(ds,-1,n,s);
	for(int i=0;i<n;i++)s[i].a/=n,s[i].b/=n;//,printf("(%.9f,%.9f)\n",(double)s[i].a,(double)s[i].b);//,printf("%.9f\n",(double)s[i].b)/*assert(fabs(v.b)<EPS),*/;
//	puts("\npass\n");
	return s;
}
vector<long double>Mul(vector<long double>a,vector<long double>b)
{
	int n=1;
	while(n<(int)max(a.size(),b.size()))n<<=1;
	n<<=1;
	while((int)a.size()<n)a.push_back(0.0);
	while((int)b.size()<n)b.push_back(0.0);
	vector<Complex>ca,cb;
	for(const auto &v:a)ca.push_back(Complex(v,0.0));
	for(const auto &v:b)cb.push_back(Complex(v,0.0));
	const vector<Complex>cs=Mul(ca,cb);
	vector<long double>s;
	for(const Complex &v:cs)s.push_back(v.a);//,printf("v=(%.9f,%.9f)\n",(double)v.a,(double)v.b);//,assert(fabs(v.b)<EPS);
	return s;
}
typedef long long LL;
const LL MOD=1e9+7;
void ExGcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0LL){x=1LL,y=0LL;assert(a==1LL);return;}
	ExGcd(b,a%b,y,x);//(a-a/b*b)x+by==1
	(y-=a/b*x)%=MOD;//ax+b(y-a/b*x)==1
}
LL Mod(const LL v)
{
	LL ans=v%MOD+MOD;
	if(ans<0LL)ans+=MOD;
	return ans;
}
LL Rev(const LL v)
{
	LL x,y;
	ExGcd(v,MOD,x,y);
	return Mod(x);
}
struct Poly
{
	vector<LL>S;
	int N;
	Poly(){}
	Poly(const int _N,const int _K):N(_N){S.resize(_K+1);}
	LL &operator[](const int i){return S[i];}
	LL operator[](const int i)const{return S[i];}
};
LL Pow2(LL p)
{
	LL ans=1LL,a=2LL;
	for(;p;p>>=1)
	{
		if(p&1LL)(ans*=a)%=MOD;
		(a*=a)%=MOD;
	}
	return ans;
}
int K;
LL LEVEL[30001],REVLV[30001];
Poly operator*(const Poly &a,const Poly &b)
{
	vector<long double>va,vb;
	for(int i=0;i<=K;i++)va.push_back((long double)Mod(a[i]*Pow2(b.N*i)%MOD*REVLV[i]));
	for(int i=0;i<=K;i++)vb.push_back((long double)Mod(b[i]*REVLV[i]));
	vector<long double>vs=Mul(va,vb);
	Poly s=Poly(a.N+b.N,K);
	for(int i=0;i<=K;i++)s[i]=(LL)(fmod(vs[i],(long double)MOD)+0.5)*LEVEL[i]%MOD;//,printf("v[%d]=%lld\n",i,(LL)(vs[i]+0.5));
	return s;
}
LL N;
LL Solve()
{
	if(N>K)return 0LL;
	static Poly p[20];
	p[0]=Poly(1,K);
	for(int i=0;i<=K;i++)p[0][i]=1LL;
	p[0][0]=0LL;
	int bit;
	for(bit=1;(1<<bit)<=N;bit++)p[bit]=p[bit-1]*p[bit-1];
	Poly ans;
	bool inited=false;
	for(bit--;bit>=0;bit--)if(N&(1<<bit))
	{
		if(!inited)ans=p[bit],inited=true;
		else ans=ans*p[bit];
	}
	LL ret=0LL;
	for(int i=0;i<=K;i++)(ret+=ans[i]*LEVEL[K]%MOD*REVLV[i]%MOD*REVLV[K-i])%=MOD;
	return ret;
}
int main()
{
//	printf("%d %d %d\n",sizeof(__float128),sizeof(long double),sizeof(long long));
	freopen("in.txt","r",stdin);
	LEVEL[0]=1LL;
	for(int i=1;i<=30000;i++)LEVEL[i]=(LEVEL[i-1]*i)%MOD;
	for(int i=0;i<=30000;i++)REVLV[i]=Rev(LEVEL[i]);
	while(scanf("%lld%d",&N,&K)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
