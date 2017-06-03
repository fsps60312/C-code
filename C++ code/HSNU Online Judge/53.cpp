#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=910193;
int N;
LL L;
void Exgcd(const LL &a,const LL &b,LL &x,LL &y)
{
	if(b==0LL){assert(a==1LL);x=1LL,y=0LL;return;}
	Exgcd(b,a%b,y,x);
	//by+(a-a/b*b)x==g
	//ax+by-a/b*b*x==g
	y-=a/b*x;
}
void Mul(LL &a,const LL &b){a*=b,a%=MOD;}
void Div(LL &a,const LL &b)
{
	static LL x,y;
//	printf("b=%lld\n",b);
	Exgcd(b,MOD,x,y);
	//b*x%MOD==1
	a*=x;
	a%=MOD,a+=MOD,a%=MOD; 
}
int main()
{
	scanf("%d",&N);
	while(N--)
	{
		scanf("%lld",&L);
		//C(L*2,L)-C(L*2,L-1)
		//=(2L)!/L!/L!-(2L)!/(L-1)!/(L+1)!
		//=(2L)!/(L+1)!/L!
		//=((L+2)...(2L))/(L!)
		LL ans=1LL;
		for(LL i=L+2LL;i<=2LL*L;i++)Mul(ans,i);
		for(LL i=1LL;i<=L;i++)Div(ans,i);
		printf("%lld\n",ans);
	}
	return 0;
}
