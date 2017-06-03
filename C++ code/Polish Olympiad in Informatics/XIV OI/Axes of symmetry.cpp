#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
LL Gcd(LL a,LL b)
{
	if(!b)return a;
	while((a%=b)&&(b%=a));
	return max(a,b);
}
struct Fraction
{
	LL UPON,DOWN;
	Fraction(){}
	Fraction(const LL _UPON,const LL _DOWN):UPON(_UPON),DOWN(_DOWN)
	{
		if(DOWN<0)UPON*=-1,DOWN*=-1;
		assert(DOWN>0);
		const LL g=Gcd(abs(UPON),DOWN);
		UPON/=g,DOWN/=g;
	}
};
Fraction operator+(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.DOWN+b.UPON*a.DOWN,a.DOWN*b.DOWN);}
Fraction operator-(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.DOWN-b.UPON*a.DOWN,a.DOWN*b.DOWN);}
Fraction operator*(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.UPON,a.DOWN*b.DOWN);}
Fraction operator/(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.DOWN,a.DOWN*b.UPON);}
Fraction operator+=(Fraction &a,const Fraction &b){return a=a+b;}
Fraction operator-=(Fraction &a,const Fraction &b){return a=a-b;}
Fraction operator*=(Fraction &a,const Fraction &b){return a=a*b;}
Fraction operator/=(Fraction &a,const Fraction &b){return a=a/b;}
bool operator==(const Fraction &a,const Fraction &b){return a.UPON==b.UPON&&a.DOWN==b.DOWN;}
struct Point
{
	Fraction X,Y;
	Point(){}
	Point(const Fraction &_X,const Fraction &_Y):X(_X),Y(_Y){}
};
Point MidPoint(const Point &a,const Point &b){return Point(Fraction(1,2)*(a.X+b.X),Fraction(1,2)*(a.Y+b.Y));}
bool SameAngle(const Point &a,const Point &b,const Point &c)
{
	if(b.X==Fraction(0,1))return a.X==Fraction(0,1)-c.X&&a.Y==c.Y;
	if(b.Y==Fraction(0,1))return a.Y==Fraction(0,1)-c.Y&&a.X==c.X;
//	return (a.X*b.Y-b.X*a.Y==b.X*c.Y-c.X*b.Y)&&(a.X*b.X+a.Y*b.Y==b.X*c.X+b.Y*c.Y);
	return (a.X/b.X-a.Y/b.Y==c.Y/b.Y-c.X/b.X)&&(a.X/b.Y+a.Y/b.X==c.X/b.Y+c.Y/b.X);
}
int N;//N<=100000
vector<Point>P;
void MinusCenter()
{
	Fraction xsum=Fraction(0,1),ysum=Fraction(0,1);
	assert((int)P.size()==N);
	for(int i=0;i<N;i++)xsum+=P[i].X,ysum+=P[i].Y;
	xsum/=Fraction(N,1),ysum/=Fraction(N,1);
	for(int i=0;i<N;i++)P[i].X-=xsum,P[i].Y-=ysum;
}
vector<int>Z;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		vector<Point>s;
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			s.push_back(Point(Fraction(x,1),Fraction(y,1)));
		}
		P.clear();
		for(int i=0;i<N;i++)
		{
			P.push_back(s[i]);
			P.push_back(MidPoint(s[i],s[(i+1)%N]));
		}
		N*=2;
		MinusCenter();
		for(int i=0;i<N*2;i++)P.push_back(P[i]);
		Z.resize(P.size());
		Z[0]=1;
		for(int i=1,mx=0;i<(int)Z.size();i++)
		{
			if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-1+1,Z[mx-(i-mx)]);
			else Z[i]=1;
			while(i-Z[i]>=0&&i+Z[i]<(int)Z.size()&&SameAngle(P[i-Z[i]],P[i],P[i+Z[i]]))++Z[i];
			if(i+Z[i]>=mx+Z[mx])mx=i;
		}
		int ans=0;
		for(int i=N;i<N*2;i++)if(Z[i]>N)++ans;
		assert(ans%2==0);
		printf("%d\n",ans/2);
	}
	return 0;
}
