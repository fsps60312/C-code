#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
LL Sq(const LL &v){return v*v;}
LL Dist(const LL &x1,const LL &y1,const LL &x2,const LL &y2){return Sq(x1-x2)+Sq(y1-y2);}
struct Point
{
	LL x,y,dist;
	Point(){}
	Point(const LL _x,const LL _y,const LL &_dist):x(_x),y(_y),dist(_dist){}
	bool operator<(const Point &p)const
	{
		if(dist!=p.dist)return dist<p.dist;
		if(x!=p.x)return x<p.x;
		if(y!=p.y)return y<p.y;
		return false;
	}
};
int N;
LL X1,Y1,X2,Y2;
set<Point>S1,S2;
LL MaxDist(const set<Point>&s,const LL &x,const LL &y)
{
	if(s.empty())return 0LL;
	auto p=s.end();p--;
	return Dist(x,y,p->x,p->y); 
}
int main()
{
	while(scanf("%d%I64d%I64d%I64d%I64d",&N,&X1,&Y1,&X2,&Y2)==5)
	{
		S1.clear(),S2.clear();
		for(int i=0;i<N;i++)
		{
			LL x,y;
			scanf("%I64d%I64d",&x,&y);
			S1.insert(Point(x,y,Dist(X1,Y1,x,y)));
			S2.insert(Point(x,y,Dist(X2,Y2,x,y)));
		}
		LL ans=INF;
		getmin(ans,MaxDist(S2,X2,Y2));
		for(const Point &p:S1)
		{
			auto it=S2.find(Point(p.x,p.y,Dist(X2,Y2,p.x,p.y)));
			assert(it!=S2.end());
			S2.erase(it);
			getmin(ans,MaxDist(S2,X2,Y2)+Dist(X1,Y1,p.x,p.y)); 
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
