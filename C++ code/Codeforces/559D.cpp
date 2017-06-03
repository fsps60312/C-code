#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
typedef long long LL;
int Gcd(const int a,const int b){return b==0?a:Gcd(b,a%b);}
struct Point
{
	LL x,y;
}P[100000];
int N;
double Area(const int l,const int k)
{
	double ans=P[(l+k)%N].x*P[l].y-P[l].x*P[(l+k)%N].y;
	for(int i=0;i<k;i++)ans+=P[(l+i)%N].x*P[(l+i+1)%N].y-P[(l+i+1)%N].x*P[(l+i)%N].y;
	return 0.5*fabs(ans);
}
double Pow2(int p)
{
	double a=2.0,ans=1.0;
	while(p)
	{
		if(p&1)ans*=a;
		a*=a,p>>=1;
	}
	return ans;
}
double Odd(const int k)
{
	if(N>120)return 1.0/Pow2(k+1);//Pow2((N-k-1)-N);
	else return (Pow2(N-k-1)-1.0)/(Pow2(N)-1.0-N-0.5*(double)N*(N-1.0));
}
double DotOnSide(const Point &a,const Point &b)
{
	const int dx=abs(a.x-b.x),dy=abs(a.y-b.y);
	return (double)Gcd(dx,dy);
}
double DotOnSide(const int l,const int k)
{
	assert(k>1);
	double ans=DotOnSide(P[l],P[(l+k)%N]);
	for(int i=0;i<k;i++)ans+=DotOnSide(P[(l+i)%N],P[(l+i+1)%N]);
	return ans;
}
double DotCnt(const int l,const int k)
{
	//area=dotin+doton/2-1
	if(k==1)return DotOnSide(P[l],P[(l+1)%N])+1.0;
//	printf("area=%.9f,DotOnSide=%.9f\n",Area(l,k),DotOnSide(l,k));
	return Area(l,k)+1.0+0.5*DotOnSide(l,k);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%I64d%I64d",&P[i].x,&P[i].y);
		double ans=DotCnt(0,N-1);
		for(int k=1;k<=60&&k<N-1;k++)
		{
			const double odd=Odd(k);
//			printf("odd=%.9f\n",odd);
			for(int i=0;i<N;i++)ans-=odd*(DotCnt(i,k)-1.0);//,printf("DotsIn=%.9f\n",DotCnt(i,k));
		}
		printf("%.9f\n",ans);
	}
	return 0;
}
