#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
using namespace std;
const long double PI=acos((long double)-1.0);
struct Complex
{
	long double a,b;
	Complex(){}
	Complex(const long double _a,const long double _b):a(_a),b(_b){}
	Complex operator-()const{return Complex(-a,-b);}
};
Complex operator*(const Complex &a,const Complex &b){return Complex(a.a*b.a-a.b*b.b,a.a*b.b+b.a*a.b);}
Complex operator+(const Complex &a,const Complex &b){return Complex(a.a+b.a,a.b+b.b);}
int CntBits(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
void DFT(const vector<Complex>&s,const Complex &omega,vector<Complex>&ans)
{
	const int n=s.size();
	if(n==1)
	{
		ans.clear(),ans.push_back(s[0]);
		return;
	}
	vector<Complex>left_s,right_s,left_ans,right_ans;
	for(int i=0;i<n;i++)(i&1?left_s:right_s).push_back(s[i]);
	DFT(right_s,omega*omega,right_ans);
	DFT(left_s,omega*omega,left_ans);
	ans.resize(n);
	for(int i=0;i<n/2;i++)
	{
		ans[i]=left_ans[i]*omega+right_ans[i];
		ans[i+n/2]=-left_ans[i]*omega+right_ans[i];
	}
}
vector<long double>Mul(vector<long double>a,vector<long double>b)
{
	if(a.size()>b.size())swap(a,b);
	while(CntBits(b.size())>1)b.push_back(0.0);
	while(a.size()<b.size())a.push_back(0.0);
	vector<long double>s;
	s.resize(a.size()+b.size()-1,0.0);
	for(int i=0;i<(int)a.size();i++)for(int j=0;j<(int)b.size();j++)s[i+j]+=a[i]*b[j];
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
LL Rev(const LL v)
{
	LL x,y;
	ExGcd(v,MOD,x,y);
	x%=MOD;
	if(x<0LL)x+=MOD;
	return x;
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
	for(int i=0;i<=K;i++)va.push_back((long double)(a[i]*Pow2(b.N*i)%MOD*REVLV[i]%MOD));
	for(int i=0;i<=K;i++)vb.push_back((long double)(b[i]*REVLV[i]%MOD));
	vector<long double>vs=Mul(va,vb);
	Poly s=Poly(a.N+b.N,K);
	for(int i=0;i<=K;i++)s[i]=(LL)(vs[i]+0.5)%MOD*LEVEL[i]%MOD;
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
