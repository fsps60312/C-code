#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int T;
LL N,M;
inline void Mul(LL &a,const LL &b){a*=b%MOD;a%=MOD;}
inline void Sub(LL &a,const LL &b){a-=b%MOD;a+=MOD;a%=MOD;}
inline void Add(LL &a,const LL &b){a+=b%MOD;a+=MOD;a%=MOD;}
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
//	LL t=N*M*min(N,M);
//	t+=
	//(N-N/i*i)(M-M/i*i)
	//N*M-M(N/i*i)-N(M/i*i)+(N/i*i)(M/i*i)
	//N*M
	LL ans=1LL,sum=GetSum(min(N,M));
	Mul(ans,N),Mul(ans,M),Mul(ans,min(N,M));
	LL ta=1LL;
	Mul(ta,M),Mul(ta,sum);
	Sub(ans,ta);
	ta=1LL;
	Mul(ta,N),Mul(ta,sum);
	Sub(ans,ta);
	//(N/i*i)(M/i*i)
	//(N/i)(M/i)*i*i
	//n(n+1)(2n+1)/6
	//2nnn+3nn+n
	//a^3-b^3=(a-b)(aa+ab+bb)
	//aa-bb=(a+b)(a-b)
	ans=N*M*min(N,M)-
	for(LL i=1LL;i<=min(N,M);i++)Add(ans,(N/i*i)*(M/i*i));return ans;
	for(LL l=1LL,r,a,b;l<=min(N,M);)
	{
		r=min(N/(N/l),M/(M/l));
//		l--;
//		tmp=2LL*(r-l)*(r*r+r*l+l*l);
//		tmp+=3LL*(r+l)*(r-l);
//		tmp+=r-l;
//		tmp=
		a=r*(r+1LL)/2LL;
		if(a%3LL==0LL)Mul(a/=3LL,2LL*r+1LL);
		else Mul(a,(2LL*r+1LL)/3LL);
		l--;
		b=l*(l+1LL)/2LL;
		if(b%3LL==0LL)Mul(b/=3LL,2LL*l+1LL);
		else Mul(b,(2LL*l+1LL)/3LL);
		ta=1LL;
		Mul(ta,N/r),Mul(ta,M/r),Mul(ta,a-b);
		Add(ans,ta);
		l=++r;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
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
