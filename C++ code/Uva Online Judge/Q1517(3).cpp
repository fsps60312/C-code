#include<cstdio>
#include<set>
#include<vector>
using namespace std;
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
	bool operator<(Point p)const{return x!=p.x?x<p.x:y<p.y;}
};
int T,S,R,W,P;
set<Point>SENSOR,ANS;
vector<Point>WALL;
bool AtRange(int v,int l,int r){return (v>=l&&v<=r)||(v>=r&&v<=l);}
bool OnBoth(int up,int down,int xl1,int xr1,int xl2,int xr2){return AtRange(up,xl1*down,xr1*down)&&AtRange(up,xl2*down,xr2*down);}
int WallIntersect(Point p1,Point p2)
{
	//(y1-y2)x+(x2-x1)y==x2y1-x1y2
	int a1=p1.y-p2.y,b1=p2.x-p1.x,c1=p2.x*p1.y-p1.x*p2.y,a2,b2,c2,ans=0;
	for(int i=0;i<WALL.size();i+=2)
	{
		int &x1=WALL[i].x,&y1=WALL[i].y,&x2=WALL[i+1].x,&y2=WALL[i+1].y;
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
			if(b2*c1==b1*c2&&a2*c1==a1*c2)return -1;
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
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&S,&R,&W,&P);
		SENSOR.clear(),WALL.clear();
		for(int i=0,x,y;i<S;i++)
		{
			scanf("%d%d",&x,&y);
			SENSOR.insert(Point(x,y));
		}
		for(int i=0,x1,y1,x2,y2,tmp;i<W;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			WALL.push_back(Point(x1,y1));
			WALL.push_back(Point(x2,y2));
		}
		for(int idx=0,tx,ty,x,y;idx<P;idx++)
		{
			scanf("%d%d",&tx,&ty);
			ANS.clear();
//			printf("(%d,%d)",tx,ty);
			for(int dx=-R;dx<=R;dx++)
			{
				for(int dy=-R;dy<=R;dy++)
				{
					x=tx+dx,y=ty+dy;
					if(SENSOR.find(Point(x,y))==SENSOR.end())continue;
					int r=dx*dx+dy*dy;
					if(r>R*R)continue;
					int wall=WallIntersect(Point(tx,ty),Point(x,y));
//					printf(" %d(%d,%d)",wall,x,y);
					if(wall==-1||wall>=R)continue;
					if(r<=(R-wall)*(R-wall))ANS.insert(Point(x,y));
				}
			}
//			puts("");
			printf("%d",ANS.size());
			for(set<Point>::iterator it=ANS.begin();it!=ANS.end();it++)printf(" (%d,%d)",(*it).x,(*it).y);
			puts("");
		}
	}
	return 0;
}
