#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Point
{
	LL X,Y;
	Point(){}
	Point(const LL _X,const LL _Y):X(_X),Y(_Y){}
};
bool operator<(const Point &a,const Point &b){return a.X!=b.X?a.X<b.X:a.Y<b.Y;}
bool operator==(const Point &a,const Point &b){return a.X==b.X&&a.Y==b.Y;}
LL Area(const Point &a,const Point &b,const Point &c)
{
	return abs((a.X*b.Y+b.X*c.Y+c.X*a.Y)-(a.Y*b.X+b.Y*c.X+c.Y*a.X));
}
int N;
LL S;
Point P[5000];
LL Area(const int a,const int b,const int c){return Area(P[a],P[b],P[c]);}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld",&N,&S)==2)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&P[i].X,&P[i].Y);
		sort(P,P+N),N=(int)(unique(P,P+N)-P);
		assert(N>=3);
		int a=0,b=1,c=2;
		for(bool changed=true;changed;)
		{
			changed=false;
			for(int i=0;i<N;i++)if(i!=a&&i!=b&&i!=c)
			{
				if(Area(a,b,i)>Area(a,b,c))c=i,changed=true;
				if(Area(a,i,c)>Area(a,b,c))b=i,changed=true;
				if(Area(i,b,c)>Area(a,b,c))a=i,changed=true;
			}
		}
		const LL ax=P[a].X,ay=P[a].Y,bx=P[b].X,by=P[b].Y,cx=P[c].X,cy=P[c].Y;
		printf("%lld %lld\n",ax+(bx-cx),ay+(by-cy));
		printf("%lld %lld\n",bx+(cx-ax),by+(cy-ay));
		printf("%lld %lld\n",cx+(ax-bx),cy+(ay-by));
	}
	return 0;
}
