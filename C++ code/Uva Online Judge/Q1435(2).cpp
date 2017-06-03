#include<cstdio>
#include<algorithm>
typedef long long LL;
using namespace std;
LL A,B,M,N;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
void exgcd(LL a,LL b,LL &g,LL &x,LL &y)
{
	if(!b)//ax+by==g
	{
		g=a;
		x=1LL;
		y=0LL;
		return;
	}
	exgcd(b,a%b,g,y,x);//(a%b)x+by==g
	//(a-a/b*b)x+by==g
	//ax-a/b*bx+by==g
	//ax+b(y-a/b*x)==g
	y-=a/b*x;
}
bool CanDiv(LL v,LL a,LL b)
{
	LL g,x,y;
	exgcd(a,b,g,x,y);//ax+by==g
	if(v%g)return false;
//	printf("%lld %lld %lld\n",x,y,g);
	x*=v/g;
	y*=v/g;//ax+by==v
	LL d=b/g;
	x=(x%d+d)%d;
	if(x==0)x+=d;
//	printf("%lld %lld %lld\n",x,(v-a*x)/b,d);
	if((v-a*x)%b)printf("error\n");
	if((v-a*x)/b>0)return true;
	return false;
}
bool solve()
{
	if(A>B)swap(A,B);
	if(M>N)swap(M,N);
	if(M%A==0&&N%B==0)return true;
	if(M%B==0&&N%A==0)return true;
	LL LCM=A/gcd(A,B)*B;
	if(M%LCM==0&&CanDiv(N,A,B))return true;
	if(N%LCM==0&&CanDiv(M,A,B))return true;
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
//	printf("%d\n",CanDiv(62,7,4));
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld",&A,&B,&M,&N);
		printf(solve()?"YES\n":"NO\n");
	}
	return 0;
}
