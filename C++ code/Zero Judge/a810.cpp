#include<cstdio>
typedef long long LL;
LL A,B,X,Y;
LL gcd(const LL &a,const LL &b){return b==0LL?a:gcd(b,a%b);}
LL Get(const LL &l,const LL &r,const LL &v)
{
	if(l<0LL)
	{
		if(r<0LL)return Get(-r,-l,v);
		return Get(0LL,r,v)+Get(1LL,-l,v);
	}
	return (r/v)-((l+v-1LL)/v)+1LL;
}
const LL INF=9000000000000000000LL;
LL Solve()
{
	if(X==0LL||Y==0LL)return (A<=0LL&&B>=0LL)?1LL:0LL;
	LL ans=Get(A,B,X)+Get(A,B,Y);
	LL g=gcd(X,Y);
	if(X/g<=INF/Y)ans-=Get(A,B,X/g*Y);
	else if(A<=0LL&&B>=0LL)ans--;
	return ans;
}
int main()
{
//	printf("%lld %lld %lld %lld\n",Get(-1,1,2),Get(1,1,2),Get(-2,-2,2),Get(-4,-2,2));
	while(scanf("%lld%lld%lld%lld",&A,&B,&X,&Y)==4)
	{
		if(X<0LL)X=-X;
		if(Y<0LL)Y=-Y;
		printf("%lld\n",Solve());
	}
	return 0;
}
