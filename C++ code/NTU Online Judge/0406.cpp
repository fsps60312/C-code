#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Point
{
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
};
Point P[8];
Point MidPoint(const Point &a,const Point &b){assert((a.X+b.X)%2==0&&(a.Y+b.Y)%2==0);return Point((a.X+b.X)/2,(a.Y+b.Y)/2);}
bool Input()
{
	bool ans=false;
	for(int i=0;i<8;i+=2)
	{
		int &x=P[i].X,&y=P[i].Y;
		scanf("%d%d",&x,&y),ans|=(x||y);
		x*=2,y*=2;
	}
	for(int i=1;i<8;i+=2)P[i]=MidPoint(P[i-1],P[(i+1)%8]);
	return ans;
}
int Area(const Point &a,const Point &b,const Point &c)
{
	return abs(a.X*b.Y+b.X*c.Y+c.X*a.Y-b.X*a.Y-a.X*c.Y-c.X*b.Y);
}
int Area(const int a,const int b,const int c)
{
	return Area(P[a],P[b],P[c]);
}
void getmin(int &a,const int b){if(b<a)a=b;}
int TOTAL_AREA;
int ANS;
void Check(const int a,const int b,const int c)
{
	getmin(ANS,abs(Area(P[a],P[b],P[c])*2-TOTAL_AREA));
}
void Check(const int a,const int b,const int c,const int d)
{
	getmin(ANS,abs((Area(P[a],P[b],P[c])+Area(P[c],P[d],P[a]))*2-TOTAL_AREA));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(Input())
	{
		ANS=2147483647;
		TOTAL_AREA=Area(0,2,4)+Area(4,6,0);
		Check(0,2,3);
		Check(0,2,4);
		Check(0,2,4,5);
		Check(1,2,3);
		Check(1,2,4);
		Check(1,2,4,5);
		Check(1,2,4,6);
		Check(1,7,0);
		Check(2,4,5);
		Check(2,4,6);
		Check(2,4,6,7);
		Check(3,4,5);
		Check(3,4,6);
		Check(3,4,6,7);
		Check(4,6,7);
		Check(5,6,7);
		double ans1=0.5*(TOTAL_AREA-ANS),ans2=0.5*(TOTAL_AREA+ANS);
		static int kase=0;
		printf("Cake %d: %.3f %.3f\n",++kase,0.125*ans1,0.125*ans2);
	}
	return 0;
}
