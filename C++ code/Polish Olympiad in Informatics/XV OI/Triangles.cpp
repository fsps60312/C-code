#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Fraction
{
	LL UPON,DOWN;
	Fraction(const LL _UPON,const LL _DOWN):UPON(_UPON),DOWN(_DOWN){assert(UPON>=0&&DOWN>0);}
};
bool operator<(const Fraction &a,const Fraction &b){return a.UPON*b.DOWN<b.UPON*a.DOWN;}
struct Point
{
	LL X,Y;
	Point(){}
	Point(const LL _X,const LL _Y):X(_X),Y(_Y){}
};
struct Vector
{
	LL X,Y;
	Vector(){}
	Vector(const LL _X,const LL _Y):X(_X),Y(_Y){}
	int Quadrant()const
	{
		if(X>0&&Y>=0)return 1;
		if(X<=0&&Y>0)return 2;
		if(X<0&&Y<=0)return 3;
		if(X>=0&&Y<0)return 4;
		assert(0);return -1;
	}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
bool operator<(const Vector &a,const Vector &b)
{
	const int qa=a.Quadrant(),qb=b.Quadrant();
	if(qa!=qb)return qa<qb;
	switch(qa)
	{
		case 1:return Fraction(a.Y,a.X)<Fraction(b.Y,b.X);
		case 2:return Fraction(-a.X,a.Y)<Fraction(-b.X,b.Y);
		case 3:return Fraction(-a.Y,-a.X)<Fraction(-b.Y,-b.X);
		case 4:return Fraction(a.X,-a.Y)<Fraction(b.X,-b.Y);
		default:assert(0);return false;
	}
}
LL Cross(const Vector &a,const Vector &b){return a.X*b.Y-b.X*a.Y;}
int N;
Point P[3000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&P[i].X,&P[i].Y);
		LL ans=0;
		for(int u=0;u<N;u++)
		{
			vector<Vector>ps;
			for(int i=0;i<N;i++)if(i!=u)ps.push_back(P[i]-P[u]);
			sort(ps.begin(),ps.end());
			for(int i=0;i<N-1;i++)ps.push_back(ps[i]);
			LL xsum=0,ysum=0;
			LL pre_ans=ans;
			for(int r=0,l=0;r<(N-1)*2;r++)
			{
				while(l<=r-(N-1)||Cross(ps[r],ps[l])>0)xsum-=ps[l].X,ysum-=ps[l].Y,++l;
				assert(r-(N-1)<l&&l<=r);
				printf("(%d,%d),(%lld,%lld)~(%lld,%lld)\n",l,r,ps[l].X,ps[l].Y,ps[r].X,ps[r].Y);
				if(r>=N-1)
				{
					ans+=xsum*ps[r].Y-ps[r].X*ysum;
				}
				xsum+=ps[r].X,ysum+=ps[r].Y;
			}
			printf("u=%d(%lld,%lld), add=%lld\n",u+1,P[u].X,P[u].Y,ans-pre_ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
