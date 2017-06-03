#include<cstdio>
#include<set>
#include<vector>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a<b?b:a;}
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	Point(){}
	Point(LL x,LL y):x(x),y(y){}
	Point operator-(Point a){return Point(x-a.x,y-a.y);}
	LL operator^(Point a){return x*a.y-y*a.x;}
	bool operator<(Point p)const{return x!=p.x?x<p.x:y<p.y;}
};
LL T,S,R,W,P;
set<Point>SENSOR,ANS;
vector<Point>WALL;
bool Intersect(Point p1,Point p2,Point p3,Point p4)
{
	if(min(p1.x,p2.x)>max(p3.x,p4.x)
	||min(p1.y,p2.y)>max(p3.y,p4.y)
	||max(p1.x,p2.x)<min(p3.x,p4.x)
	||max(p1.y,p2.y)<min(p3.y,p4.y))return false;
	Point v12=p1-p2,v13=p1-p3,v14=p1-p4;
	Point v34=p3-p4,v31=p3-p1,v32=p3-p2;
	return (v12^v13)*(v12^v14)<=0LL&&(v34^v31)*(v34^v32)<=0LL;
}
LL WallIntersect(Point p1,Point p2)
{
	LL ans=0LL;
	for(LL i=0;i<WALL.size();i+=2)
	{
		if(Intersect(p1,p2,WALL[i],WALL[i+1]))
		{
			ans++;
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld",&S,&R,&W,&P);
		SENSOR.clear(),WALL.clear();
		for(LL i=0,x,y;i<S;i++)
		{
			scanf("%lld%lld",&x,&y);
			SENSOR.insert(Point(x,y));
		}
		for(LL i=0,x1,y1,x2,y2,tmp;i<W;i++)
		{
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			WALL.push_back(Point(x1,y1));
			WALL.push_back(Point(x2,y2));
		}
//		printf("walls :%lld\n",WallIntersect(Point(0,0),Point(100,0)));
		for(LL idx=0,tx,ty,x,y;idx<P;idx++)
		{
			scanf("%lld%lld",&tx,&ty);
			ANS.clear();
//			printf("(%lld,%lld)",tx,ty);
			for(LL dx=-R;dx<=R;dx++)
			{
				for(LL dy=-R;dy<=R;dy++)
				{
					x=tx+dx,y=ty+dy;
					if(SENSOR.find(Point(x,y))==SENSOR.end())continue;
					LL r=dx*dx+dy*dy;
					if(r>R*R)continue;
					LL wall=WallIntersect(Point(tx,ty),Point(x,y));
//					printf(" %lld(%lld,%lld)",wall,x,y);
					if(wall>R)continue;
					if(r<=(R-wall)*(R-wall))ANS.insert(Point(x,y));
				}
			}
//			puts("");
			printf("%d",ANS.size());
			for(set<Point>::iterator it=ANS.begin();it!=ANS.end();it++)printf(" (%lld,%lld)",(*it).x,(*it).y);
			puts("");
		}
	}
	return 0;
}
