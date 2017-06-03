#include<cstdio>
#include<cassert>
#include<utility>
#include<cmath>
using namespace std;
typedef long long LL;
const int INF=2147483647;
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
int N,H;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
	Point ToUp()const{return Point(x,y+H);}
}P[101];
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
double Dist(const Point &a,const Point &b){return Hypot(a.x-b.x,a.y-b.y);}
double DP[100][2];
bool FrontIsOk(const int y,const int loc)
{
	for(int i=0;i<loc;i++)
	{
		if(P[i].y>y||P[i].ToUp().y<y)return false;
	}
	return true;
}
bool IsOk(const Point a,const Point b,const int l,const int r)
{
	assert(l-1<=r);
	for(int i=l;i<=r;i++)
	{
//		const double y=(double)(a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x))/((P[i].x-a.x)+(b.x-P[i].x));
//		if(P[i].Y>y||P[i].ToUp().y<y)return false;
		if((LL)P[i].y*((P[i].x-a.x)+(b.x-P[i].x))>a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x)||(LL)P[i].ToUp().y*((P[i].x-a.x)+(b.x-P[i].x))<a.y*(b.x-P[i].x)+b.y*(P[i].x-a.x))return false;
	}
	return true;
}
double GetFront(const int loc)
{
	for(int i=0;i<=loc;i++)DP[i][0]=DP[i][1]=1e100;
	for(int i=0;i<=loc;i++)
	{
		if(FrontIsOk(P[i].y,i))DP[i][0]=P[i].x-P[0].x;
		if(FrontIsOk(P[i].ToUp().y,i))DP[i][1]=P[i].x-P[0].x;
		for(int j=i+1;j<=loc;j++)
		{
			if(IsOk(P[i],P[j],i+1,j-1))getmin(DP[j][0],DP[i][0]+Dist(P[i],P[j]));
			if(IsOk(P[i],P[j].ToUp(),i+1,j-1))getmin(DP[j][1],DP[i][0]+Dist(P[i],P[j].ToUp()));
			if(IsOk(P[i].ToUp(),P[j],i+1,j-1))getmin(DP[j][0],DP[i][1]+Dist(P[i].ToUp(),P[j]));
			if(IsOk(P[i].ToUp(),P[j].ToUp(),i+1,j-1))getmin(DP[j][1],DP[i][1]+Dist(P[i].ToUp(),P[j].ToUp()));
		}
	}
	return DP[loc][1];
}
bool BackIsOk(const int y,const int loc)
{
	for(int i=loc+1;i<=N;i++)
	{
		if(P[i].y>y||P[i].ToUp().y<y)return false;
	}
	return true;
}
double GetBack(const int loc)
{
	for(int i=N;i>=loc;i--)DP[i][0]=DP[i][1]=1e100;
	for(int i=N;i>=loc;i--)
	{
		if(BackIsOk(P[i].y,i))DP[i][0]=P[N].x-P[i].x;
		if(BackIsOk(P[i].ToUp().y,i))DP[i][1]=P[N].x-P[i].x;
		for(int j=i-1;j>=loc;j--)
		{
			if(IsOk(P[j],P[i],j+1,i-1))getmin(DP[j][0],DP[i][0]+Dist(P[i],P[j]));
			if(IsOk(P[j],P[i].ToUp(),j+1,i-1))getmin(DP[j][1],DP[i][0]+Dist(P[i],P[j].ToUp()));
			if(IsOk(P[j].ToUp(),P[i],j+1,i-1))getmin(DP[j][0],DP[i][1]+Dist(P[i].ToUp(),P[j]));
			if(IsOk(P[j].ToUp(),P[i].ToUp(),j+1,i-1))getmin(DP[j][1],DP[i][1]+Dist(P[i].ToUp(),P[j].ToUp()));
		}
	}
	return DP[loc][1];
}
double Solve()
{
	pair<int,int>upon=make_pair(INF,-1),down=make_pair(-INF,-1);
	for(int i=0;i<=N;i++)getmin(upon,make_pair(P[i].y+H,i)),getmax(down,make_pair(P[i].y,i));
	assert(upon.second!=-1&&down.second!=-1);
	if(upon.first>=down.first)return (double)(P[N].x-P[0].x);
//	puts("pass");
//	printf("upon.s=%d, down.s=%d, %.10f %.10f\n",upon.second,down.second,GetFront(upon.second),GetBack(upon.second));
	return GetFront(upon.second)+GetBack(upon.second);
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<=N;i++)scanf("%d%d",&P[i].x,&P[i].y);
		scanf("%d",&H);
		printf("%.10f\n",Solve());
	}
	return 0;
}
