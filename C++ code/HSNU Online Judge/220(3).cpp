#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int T;
LL N,M;
inline void Mul(LL &a,const LL &b){a%=MOD;a*=b%MOD;a%=MOD;a+=MOD;a%=MOD;}
inline void Sub(LL &a,const LL &b){a%=MOD;a-=b%MOD;a%=MOD;a+=MOD;a%=MOD;}
inline void Add(LL &a,const LL &b){a%=MOD;a+=b%MOD;a%=MOD;a+=MOD;a%=MOD;}
LL GetSum(const LL &n)
{
	LL ans=1LL;
	Mul(ans,n),Mul(ans,n);
	for(LL l=1LL,r,ta;l<=n;)
	{
		r=n/(n/l);
		ta=1LL;
		Mul(ta,n/l),Mul(ta,(l+r)*(r-l+1LL)/2LL);
		Sub(ans,ta);
		l=++r;
	}
	return ans;
}
LL min(const LL &a,const LL &b){return a<b?a:b;}
LL Extra()
{
	//(N-N/i*i)(M-M/i*i)
	//N*M-M(N/i*i)-N(M/i*i)+(N/i*i)(M/i*i)
	//N*M
	//(N/i*i)(M/i*i)
	//(N/i)(M/i)*i*i
	//n(n+1)(2n+1)/6
	//2nnn+3nn+n
	//a^3-b^3=(a-b)(aa+ab+bb)
	//aa-bb=(a+b)(a-b)
	LL ans=1LL;
	Mul(ans,N),Mul(ans,M),Mul(ans,min(N,M));
//	for(LL i=1LL;i<=min(N,M);i++)ans-=N/i*i*M,ans-=M/i*i*N,ans+=(N/i)*(M/i)*i*i;return ans;
	for(LL l=1LL,r,ta,a,b;l<=min(N,M);)
	{
		r=min(N/(N/l),M/(M/l));
		ta=1LL;
		Mul(ta,N/l),Mul(ta,(r+l)*(r-l+1)/2LL),Mul(ta,M);
		Sub(ans,ta);
		ta=1LL;
		Mul(ta,M/l),Mul(ta,(r+l)*(r-l+1)/2LL),Mul(ta,N);
		Sub(ans,ta);
		ta=1LL;
		//a=r(r+1)(2r+1)/6
		//b=(l-1)(l)(2l-1)/6
		a=(r*(r+1LL))/2LL;
		if(a%3LL==0LL)a/=3LL,Mul(a,2LL*r+1LL);
		else Mul(a,(2LL*r+1LL)/3LL);
		b=(l*(l-1LL))/2LL;
		if(b%3LL==0LL)b/=3LL,Mul(b,2LL*l-1LL);
		else Mul(b,(2LL*l-1LL)/3LL);
		Sub(a,b);
		Mul(ta,N/l),Mul(ta,M/l),Mul(ta,a);
		Add(ans,ta);
//		printf("(%d,%d)%d\n",l,r,a-b);
		l=++r;
	}
//	for(LL i=1LL;i<=min(N,M);i++)ans+=(N/i*i)*(M/i*i);return ans;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		LL ans=1LL;
		Mul(ans,GetSum(N)),Mul(ans,GetSum(M));
//		for(LL i=1LL;i<=min(N,M);i++)ans-=(N%i)*(M%i),ans%=MOD;
		Sub(ans,Extra());
		printf("%lld\n",ans);
	}
	return 0;
}
