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
	bool operator<(Point p)const{return x!=p.x?x<p.x:y<p.y;}
};
LL T,S,R,W,P;
set<Point>SENSOR,ANS;
vector<Point>WALL;
bool AtRange(LL v,LL l,LL r){return (v>=l&&v<=r)||(v>=r&&v<=l);}
bool OnBoth(LL up,LL down,LL xl1,LL xr1,LL xl2,LL xr2){return AtRange(up,xl1*down,xr1*down)&&AtRange(up,xl2*down,xr2*down);}

//    if (max(a1, a2) < min(b1, b2) ||
//        max(a.y, b.y) < min(c.y, d.y) ||
//        min(a1, a2) > max(b1, b2) ||
//        min(a.y, b.y) > max(c.y, d.y) )
//        return false;
bool Sensible(LL a1,LL a2,LL b1,LL b2){return min(a1,a2)<=max(b1,b2)&&max(a1,a2)>=min(b1,b2);}
LL WallIntersect(Point p1,Point p2)
{
	//(y1-y2)x+(x2-x1)y==x2y1-x1y2
	LL a1=p1.y-p2.y,b1=p2.x-p1.x,c1=p2.x*p1.y-p1.x*p2.y,a2,b2,c2,ans=0;
	for(LL i=0;i<WALL.size();i+=2)
	{
		LL x1=WALL[i].x,y1=WALL[i].y,x2=WALL[i+1].x,y2=WALL[i+1].y;
		a2=y1-y2,b2=x2-x1,c2=x2*y1-x1*y2;
		//a1 x + b1 y == c1
		//a2 x + b2 y == c2
		//b2a1 x + b1b2 y == b2c1
		//b1a2 x + b1b2 y == b1c2
		//(b2a1-b1a2)x == b2c1-b1c2
		//a1a2 x + a2b1 y == a2c1
		//a1a2 x + a1b2 y == a1c2
		//(a2b1-a1b2)y == a2c1-a1c2
		if(b2*a1==b1*a2)
		{
			if(b2*c1==b1*c2&&a2*c1==a1*c2&&Sensible(p1.x,p2.x,x1,x2)&&Sensible(p1.y,p2.y,y1,y2))ans++;
			continue;
		}
//		if((b2*c1-b1*c2)/(b2*a1-b1*a2)>=x1)
		if(OnBoth(b2*c1-b1*c2,b2*a1-b1*a2,x1,x2,p1.x,p2.x)&&OnBoth(a2*c1-a1*c2,a2*b1-a1*b2,y1,y2,p1.y,p2.y))
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
//		printf("walls :%lld\n",WallIntersect(Point(0,0),Point(100,10)));
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
