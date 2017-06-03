//don't know why
#include<cstdio>
typedef long long LL;
LL Gcd(const LL &a,const LL &b){return b?Gcd(b,a%b):a;}
int T,N,K;
int main()
{
	//f(Sum((0.5-x)^k*x^(K-k),k=0~K),x=0~0.5)
	//=f(((0.5-x)^(k+1)-x^(k+1))/((0.5-x)-x),x=0~0.5)
	//=2f(((0.5-x)^(k+1)-x^(k+1))/(0.5-2x),x=0~0.25)
//	f((0.5-x)^a*x^b)
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&K);
		LL up,down;
		down=1LL<<K,up=1LL<<K;
		up-=K+1LL;
		LL g=Gcd(up,down);
		up/=g,down/=g;
		static int kase=1;
		printf("Case #%d: %lld/%lld\n",kase++,up,down);
	}
	return 0;
}
