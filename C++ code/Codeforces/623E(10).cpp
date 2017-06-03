#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
using namespace std;
const double PI=acos(-1.0),EPS=1e-9;
struct Complex
{
	double a,b;
	Complex(){}
	Complex(const double &_a,const double &_b):a(_a),b(_b){}//:a(fmod(_a,(double)MOD)),b(fmod(_b,(double)MOD)){}
	Complex operator-()const{return Complex(-a,-b);}
};
inline Complex operator*(const Complex &c1,const Complex &c2){return Complex(c1.a*c2.a-c1.b*c2.b,c1.a*c2.b+c2.a*c1.b);}
inline Complex operator+(const Complex &c1,const Complex &c2){return Complex(c1.a+c2.a,c1.b+c2.b);}
vector<Complex>OMEGA;
inline const Complex &Omega(const int i,const int n)
{
	return OMEGA[i<0?i+n:i];
}
void DFT(const vector<Complex>&s,const int n,const int oa,const int on,vector<Complex>&ans)
{
	if(n==1)
	{
		ans.resize(on);
		for(int i=0;i<on;i++)ans[i]=s[i];
		return;
	}
	vector<Complex>ch_s,ch_ans;
	assert(n%2==0);
	ch_s.resize(on);
	for(int offset=0;offset<on;offset+=n)
	{
		for(int i=0;i<n/2;i++)ch_s[offset+i]=s[offset+i*2],ch_s[offset+n/2+i]=s[offset+i*2+1];//i+n/2: left
	}
	DFT(ch_s,n/2,oa*2,on,ch_ans);
	assert((int)ch_ans.size()==on);
	ans.resize(on);
	for(int offset=0;offset<on;offset+=n)
	{
		for(int i=0,x=0;i<n/2;i++,x+=oa)
		{
			ans[offset+i]=ch_ans[offset+n/2+i]*Omega(x,on)+ch_ans[offset+i];
			ans[offset+n/2+i]=-ch_ans[offset+n/2+i]*Omega(x,on)+ch_ans[offset+i];
		}
	}
}
vector<Complex>Mul(const vector<Complex>&a,const vector<Complex>&b)
{
	assert(a.size()==b.size());
	const int n=a.size();
	OMEGA.clear();
	for(int i=0;i<n;i++)OMEGA.push_back(Complex(cos(2.0*PI*i/n),sin(2.0*PI*i/n)));
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
	DFT(a,n,1,n,da);
	DFT(b,n,1,n,db);
	assert((int)da.size()==n&&(int)db.size()==n);
	for(int i=0;i<n;i++)ds.push_back(da[i]*db[i]);
	vector<Complex>s;
	DFT(ds,n,-1,n,s);
	for(int i=0;i<n;i++)s[i].a/=n,s[i].b/=n;//,printf("(%.9f,%.9f)\n",(double)s[i].a,(double)s[i].b);//,printf("%.9f\n",(double)s[i].b)/*assert(fabs(v.b)<EPS),*/;
//	puts("\npass\n");
	return s;
}
typedef long long LL;
const LL MOD=1e9+7;
vector<int>Mul(const vector<int>&a,const vector<int>&b)
{
	vector<Complex>ca,cb;
	for(const auto &v:a)ca.push_back(Complex((double)v,0.0));
	for(const auto &v:b)cb.push_back(Complex((double)v,0.0));
	const vector<Complex>&cs=Mul(ca,cb);
	vector<int>s;
	for(const Complex &v:cs)s.push_back((int)(fmod(v.a,(double)MOD)+0.5));//,printf("v=(%.9f,%.9f)\n",(double)v.a,(double)v.b);//,assert(fabs(v.b)<EPS);
	return s;
}
LL Mod(const LL v)
{
	LL ans=v%MOD;
	if(ans<0LL)ans+=MOD;
	return ans;
}
vector<int>BigMul(vector<int>a,vector<int>b)
{
	int n=1;
	while(n<(int)max(a.size(),b.size()))n<<=1;
	n<<=1;
	while((int)a.size()<n)a.push_back(0);
	while((int)b.size()<n)b.push_back(0);
	vector<int>a1,a2,b1,b2;
	const int bitmask=(1<<15)-1;
	for(int i=0;i<n;i++)a1.push_back(a[i]&bitmask),a2.push_back(a[i]>>15);
	for(int i=0;i<n;i++)b1.push_back(b[i]&bitmask),b2.push_back(b[i]>>15);
	const vector<int>&c11=Mul(a1,b1),&c12=Mul(a1,b2),&c21=Mul(a2,b1),&c22=Mul(a2,b2);
	vector<int>s;
	for(int i=0;i<n;i++)
	{
		s.push_back((int)Mod((LL)c11[i]+((LL)(c12[i]+c21[i])<<15)+((LL)c22[i]<<30)));
	}
	return s;
}
void ExGcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0LL){x=1LL,y=0LL;assert(a==1LL);return;}
	ExGcd(b,a%b,y,x);//(a-a/b*b)x+by==1
	(y-=a/b*x)%=MOD;//ax+b(y-a/b*x)==1
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
	vector<int>va,vb;
	for(int i=0;i<=K;i++)va.push_back(Mod(a[i]*Pow2(b.N*i)%MOD*REVLV[i]));
	for(int i=0;i<=K;i++)vb.push_back(Mod(b[i]*REVLV[i]));
	const vector<int>&vs=BigMul(va,vb);
	Poly s=Poly(a.N+b.N,K);
	for(int i=0;i<=K;i++)s[i]=(LL)vs[i]*LEVEL[i]%MOD;//,printf("v[%d]=%lld\n",i,(LL)(vs[i]+0.5));
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
//	freopen("in.txt","r",stdin);
	LEVEL[0]=1LL;
	for(int i=1;i<=30000;i++)LEVEL[i]=(LEVEL[i-1]*i)%MOD;
	for(int i=0;i<=30000;i++)REVLV[i]=Rev(LEVEL[i]);
	while(scanf("%lld%d",&N,&K)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
