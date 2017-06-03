#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL _x,const LL _y):x(_x),y(_y){}
};
bool GetPointList(int &n,vector<Point>&s)
{
	if(scanf("%d",&n)!=1)return false;
	for(int i=0,x,y;i<n;i++)scanf("%d%d",&x,&y),y*=-1,s.push_back(Point(x,y));
	return true;
}
struct Vector
{
	LL x,y;
	int type;
	Vector(){}
	Vector(const LL _x,const LL _y):x(_x),y(_y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.x-b.x,a.y-b.y);}
int Quadrant(const Vector &a)
{
	if(a.x>0&&a.y>=0)return 1;
	if(a.x<=0&&a.y>0)return 2;
	if(a.x<0&&a.y<=0)return 3;
	if(a.x>=0&&a.y<0)return 4;
	assert(0);return -1;
}
LL Cross(const Vector &a,const Vector &b){return a.y*b.x-b.y*a.x;}
bool CmpAngle(const Vector &a,const Vector &b)
{
	if(Quadrant(a)!=Quadrant(b))return Quadrant(a)<Quadrant(b);
	const int q=Quadrant(a);
//	if(q==1||q==3)return a.y*b.x<b.y*a.x;//a.y/a.x<b.y/b.x
//	else return a.x*b.y>b.x*a.y;//-a.x/a.y<-b.x/b.y
	return Cross(a,b)<0;//a.y*b.x<b.y*a.x;
}
int N,M,T;
vector<Point>DRONE,FORT,TOWER;
int main()
{
	freopen("in.txt","r",stdin);
	while(GetPointList(N,DRONE))
	{
		assert(GetPointList(M,FORT)&&GetPointList(T,TOWER));
		for(const Point fort:FORT)
		{
			{
				auto cmp=[fort](Point a,Point b)->bool{return CmpAngle(a-fort,b-fort);};
				sort(DRONE.begin(),DRONE.end(),cmp);
				sort(TOWER.begin(),TOWER.end(),cmp);
//				decltype(cmp) cmp2=cmp;
//				cmp=cmp2;//[fort](Point a,Point b)->bool{return CmpAngle(a-fort,b-fort);};
			}
			for(int i=0;i<N;i++)DRONE.push_back(DRONE[i]);
			for(int i=0;i<T;i++)TOWER.push_back(TOWER[i]);
			int dl=0,dr=0,tl=0,tr=0;
			while(tr<T&&Cross(Point(1,0),TOWER[tr])<=0)++tr;
			while(dr<N&&Cross(Point(1,0),DRONE[dr])<=0)++dr;
			assert(dr==0);//no vector of drone point up
			LL cnt=0;
			for(;tr<T*2&&(tr<T||Cross(Point(1,0),TOWER[tr])>0);++tr)
			{
				while(tl<tr&&Cross(TOWER[tl],TOWER[tr])>=0)
				{
					++tl;
					while(dl<dr&&Cross(DRONE[dl],TOWER[tr])>=0)++dl;
				}
				
				assert(0);
			}
			for(int i=0;i<N;i++)DRONE.pop_back();
			for(int i=0;i<T;i++)TOWER.pop_back();
		}
	}
	return 0;
}
