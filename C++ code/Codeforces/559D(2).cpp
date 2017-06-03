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
double Area_DP[100000][61];
double Area(const int l,const int k)
{
	double &ans=Area_DP[l][k];
	ans=Area_DP[l][k-1]+(P[(l+k-1)%N].x*P[(l+k)%N].y-P[(l+k)%N].x*P[(l+k-1)%N].y);
	return 0.5*fabs(ans+P[(l+k)%N].x*P[l].y-P[l].x*P[(l+k)%N].y);
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
double DotOnSide_DP[100000][61];
double DotOnSide(const int l,const int k)
{
	double &ans=DotOnSide_DP[l][k];
	ans=DotOnSide_DP[l][k-1]+DotOnSide(P[(l+k-1)%N],P[(l+k)%N]);
	return ans+DotOnSide(P[l],P[(l+k)%N]);
}
double DotCnt(const int l,const int k)
{
	//area=dotin+doton/2-1
	const double ans=Area(l,k)+1.0+0.5*DotOnSide(l,k);
//	printf("area=%.9f,DotOnSide=%.9f\n",Area(l,k),DotOnSide(l,k));
	if(k==1)return DotOnSide(P[l],P[(l+1)%N])+1.0;
	else return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%I64d%I64d",&P[i].x,&P[i].y),Area_DP[i][0]=0.0,DotOnSide_DP[i][0]=0.0;
		double area=P[N-1].x*P[0].y-P[0].x*P[N-1].y;
		for(int i=0;i<N-1;i++)area+=P[i].x*P[i+1].y-P[i+1].x*P[i].y;
		double dots=DotOnSide(P[0],P[N-1]);
		for(int i=0;i<N-1;i++)dots+=DotOnSide(P[i],P[i+1]);
		double ans=0.5*fabs(area)+1.0+0.5*dots;
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
