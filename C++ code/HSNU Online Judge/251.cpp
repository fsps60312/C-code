#include<cstdio>
#include<set>
#include<cassert>
using namespace std;
struct Obstacle
{
	int x1,x2,y1,y2;
	Obstacle(){}
	Obstacle(const int _x1,const int _x2,const int _y1,const int _y2):x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
};
vector<Obstacle>OBSTACLE;
bool CmpX1(const Obstacle &a,const Obstacle &b)
{
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.y1!=b.y1)return a.y1<b.y1;
	return a.y2<b.y2;
}
bool CmpX2(const Obstacle &a,const Obstacle &b)
{
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.y1!=b.y1)return a.y1<b.y1;
	return a.y2<b.y2;
}
bool CmpY1(const Obstacle &a,const Obstacle &b)
{
	if(a.y1!=b.y1)return a.y1<b.y1;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	return a.y2<b.y2;
}
bool CmpY1(const Obstacle &a,const Obstacle &b)
{
	if(a.y2!=b.y2)return a.y2<b.y2;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	return a.y1<b.y1;
}
multiset<Obstacle,CmpX2>XR;
multiset<Obstacle,CmpY1>YD;
multiset<Obstacle,CmpY2>YU;
void Insert(const Obstacle &o){XR.insert(o),YD.insert(o),YU.insert(o);}
void Erase(const Obstacle &o)
{
	XR.erase(XR.find(o));
	YD.erase(YD.find(o)),YU.erase(YU.find(o));
}
bool Solve(const int sidelen)
{
	multiset<Obstacle,CmpX1>xl;
	for(const auto &o:OBSTACLE)xl.insert(o);
	for(int bl=1;;)
	{
		while((*xl.begin()).x1<lb+sidelen)
		{
			auto it=xl.begin();
			Insert(*it);
			xl.erase(it);
		}
		while((*XR.begin()).x2<lb)
		{
			const Obstacle o=*XR.begin();
			Erase(o);
		}
		bl=(*XR.begin()).x2+1;
	}
}
int N,M,B,P;
int main()
{
	scanf("%d%d%d%d",&N,&M,&B,&P);
	for(int i=0,x1,y1,x2,y2;i<P;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		OBSTACLE.push_back(Obstacle(x1,x2,y1,y2));
	}
	int l=0,r=min(N,M);
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(Solve(mid))l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}
