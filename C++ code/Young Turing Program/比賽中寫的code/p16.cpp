#include<cstdio>
#include<cassert>
#include<algorithm>
#define int long long
using namespace std;
int A,B,MOD;
void Exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return;}
	Exgcd(b,a%b,y,x);
	(((y-=a/b*x)%=MOD)+=MOD)%=MOD;
}
int Gcd(int a,int b){return b==0?a:Gcd(b,a%b);}
int Getb()
{
	int x,y;
	Exgcd(MOD,B,x,y);
	return y;
}
int Solve()
{
	const int g=Gcd(B,MOD);
	printf("g=%lld\n",g);
	//g*X=A
	if(A%g!=0)return -1;
	int x1=A/g,x2=(x1+MOD/g)%MOD;
	const int b=Getb();
	int ans1=(x1*b)%MOD,ans2=(x2*b)%MOD;
	if(ans1==ans2)return ans1;
	const int gap=abs(ans1-ans2);
	ans1%=gap;ans1+=gap;ans1%=gap;
	return ans1;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&A,&B,&MOD)==3)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
