#include<cstdio>
#include<cassert>
#include<utility>
#include<cmath>
using namespace std;
typedef long long LL;
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
LL N,H;
struct Point
{
	LL x,y;
	Point(){}
	Point(LL _x,LL _y):x(_x),y(_y){}
	Point ToUp()const{return Point(x,y+H);}
}P[1001];
long double Hypot(const LL x,const LL y){return sqrt((long double)x*x+(long double)y*y);}
long double Dist(const Point &a,const Point &b){return Hypot(a.x-b.x,a.y-b.y);}
long double DP[1001][2];
bool FrontIsOk(const LL y,const LL loc)
{
	for(LL i=0;i<loc;i++)
	{
		if(P[i].y>y||P[i].ToUp().y<y)return false;
	}
	return true;
}
bool IsOk(const Point a,const Point b,const LL l,const LL r)
{
	assert(b.x>a.x&&l-1<=r);
	for(LL i=l-1;i<=r+1;i++)
	{
//		const long double y=(long double)(a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x))/((P[i].x-a.x)+(b.x-P[i].x));
//		if(P[i].Y>y||P[i].ToUp().y<y)return false;
		if((LL)P[i].y*((P[i].x-a.x)+(b.x-P[i].x))>a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x)||(LL)P[i].ToUp().y*((P[i].x-a.x)+(b.x-P[i].x))<a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x))return false;
	}
	return true;
}
long double GetFront(const LL loc,const int _)
{
	for(LL i=0;i<=loc;i++)DP[i][0]=DP[i][1]=1e100;
	for(LL i=0;i<=loc;i++)
	{
		if(FrontIsOk(P[i].y,i))DP[i][0]=P[i].x-P[0].x;
		if(FrontIsOk(P[i].ToUp().y,i))DP[i][1]=P[i].x-P[0].x;
		for(LL j=i+1;j<=loc;j++)
		{
			if(IsOk(P[i],P[j],i+1,j-1))getmin(DP[j][0],DP[i][0]+Dist(P[i],P[j]));
			if(IsOk(P[i],P[j].ToUp(),i+1,j-1))getmin(DP[j][1],DP[i][0]+Dist(P[i],P[j].ToUp()));
			if(IsOk(P[i].ToUp(),P[j],i+1,j-1))getmin(DP[j][0],DP[i][1]+Dist(P[i].ToUp(),P[j]));
			if(IsOk(P[i].ToUp(),P[j].ToUp(),i+1,j-1))getmin(DP[j][1],DP[i][1]+Dist(P[i].ToUp(),P[j].ToUp()));
		}
	}
	return DP[loc][_];
}
bool BackIsOk(const LL y,const LL loc)
{
	for(LL i=loc+1;i<=N;i++)
	{
		if(P[i].y>y||P[i].ToUp().y<y)return false;
	}
	return true;
}
long double GetBack(const LL loc,const int _)
{
	for(LL i=N;i>=loc;i--)DP[i][0]=DP[i][1]=1e100;
	for(LL i=N;i>=loc;i--)
	{
		if(BackIsOk(P[i].y,i))DP[i][0]=P[N].x-P[i].x;
		if(BackIsOk(P[i].ToUp().y,i))DP[i][1]=P[N].x-P[i].x;
		for(LL j=i-1;j>=loc;j--)
		{
			if(IsOk(P[j],P[i],j+1,i-1))getmin(DP[j][0],DP[i][0]+Dist(P[i],P[j]));
			if(IsOk(P[j],P[i].ToUp(),j+1,i-1))getmin(DP[j][0],DP[i][1]+Dist(P[i].ToUp(),P[j]));
			if(IsOk(P[j].ToUp(),P[i],j+1,i-1))getmin(DP[j][1],DP[i][0]+Dist(P[i],P[j].ToUp()));
			if(IsOk(P[j].ToUp(),P[i].ToUp(),j+1,i-1))getmin(DP[j][1],DP[i][1]+Dist(P[i].ToUp(),P[j].ToUp()));
		}
	}
	return DP[loc][_];
}
long double Solve()
{
	{
		pair<LL,LL>upon=make_pair(2147483647LL,-1),down=make_pair(-2147483647LL,-1);
		for(LL i=0;i<=N;i++)getmin(upon,make_pair(P[i].y+H,i)),getmax(down,make_pair(P[i].y,i));
		assert(upon.second!=-1&&down.second!=-1);
		if(upon.first>=down.first)return (long double)(P[N].x-P[0].x);
	}
//	puts("pass");
//	printf("upon.s=%lld, down.s=%lld, %.10f %.10f\n",upon.second,down.second,GetFront(upon.second),GetBack(upon.second));
	long double ans=1e100;
	for(int i=0;i<=N;i++)getmin(ans,GetFront(i,0)+GetBack(i,0));
	for(int i=0;i<=N;i++)getmin(ans,GetFront(i,1)+GetBack(i,1));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	while(scanf("%lld",&N)==1)
	{
//		assert(N>1);
		for(LL i=0;i<=N;i++)scanf("%lld%lld",&P[i].x,&P[i].y);
		scanf("%lld",&H);
		printf("%.10f\n",(double)Solve());
	}
	return 0;
}
