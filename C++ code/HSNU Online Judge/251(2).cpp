#include<cstdio>
#include<set>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
struct Obstacle
{
	int x1,x2,y1,y2;
	LL cost;
	Obstacle(){}
	Obstacle(const int _x1,const int _x2,const int _y1,const int _y2,const LL _c):x1(_x1),x2(_x2),y1(_y1),y2(_y2),cost(_c){}
};
vector<Obstacle>OBSTACLE;
struct CmpX1{bool operator()(const Obstacle &a,const Obstacle &b)const
{
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.y1!=b.y1)return a.y1<b.y1;
	if(a.y2!=b.y2)return a.y2<b.y2;
	return a.cost<b.cost;
}};
struct CmpX2{bool operator()(const Obstacle &a,const Obstacle &b)
{
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.y1!=b.y1)return a.y1<b.y1;
	if(a.y2!=b.y2)return a.y2<b.y2;
	return a.cost<b.cost;
}};
struct CmpY1{bool operator()(const Obstacle &a,const Obstacle &b)
{
	if(a.y1!=b.y1)return a.y1<b.y1;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.y2!=b.y2)return a.y2<b.y2;
	return a.cost<b.cost;
}};
struct CmpY2{bool operator()(const Obstacle &a,const Obstacle &b)
{
	if(a.y2!=b.y2)return a.y2<b.y2;
	if(a.x1!=b.x1)return a.x1<b.x1;
	if(a.x2!=b.x2)return a.x2<b.x2;
	if(a.y1!=b.y1)return a.y1<b.y1;
	return a.cost<b.cost;
}};
struct BlockO
{
	multiset<Obstacle,CmpX1>xl;
	multiset<Obstacle,CmpX2>xr;
	multiset<Obstacle,CmpY1>yd;
	multiset<Obstacle,CmpY2>yu;
	LL cost;
	BlockO():cost(0LL){}
	void Insert(const Obstacle &o){cost+=o.cost;xl.insert(o),xr.insert(o),yd.insert(o),yu.insert(o);}
	void Erase(const Obstacle &o){cost-=o.cost;xl.erase(xl.find(o)),xr.erase(xr.find(o)),yd.erase(yd.find(o)),yu.erase(yu.find(o));}
	Obstacle Lx1(){return *xl.begin();}
	Obstacle Lx2(){return *xr.begin();}
	Obstacle Dy1(){return *yd.begin();}
	Obstacle Dy2(){return *yu.begin();}
	bool Empty(){return xl.empty();}
};
void MoveTo(BlockO &a,BlockO &b)
{
	while(!a.Empty())
	{
		const Obstacle o=a.Lx1();
		a.Erase(o),b.Insert(o);
	}
	assert(a.cost==0LL);
}
int N,M,B,P;
bool Solve(const int sidelen)
{
	BlockO right,up,mid,down;
	for(const auto &o:OBSTACLE)right.Insert(o);
//	printf("right.cost=%lld\n",right.cost);
	for(int bl=1;bl+sidelen-1<=M;)
	{
		while(!right.Empty()&&right.Lx1().x1<=bl+sidelen-1)
		{
			const Obstacle o=right.Lx1();
			right.Erase(o),up.Insert(o);
		}
		while(!up.Empty()&&up.Lx2().x2<bl)up.Erase(up.Lx2());
		for(int bd=1;bd+sidelen-1<=N;)
		{
			while(!up.Empty()&&up.Dy1().y1<=bd+sidelen-1)
			{
				const Obstacle o=up.Dy1();
				up.Erase(o),mid.Insert(o);
			}
			while(!mid.Empty()&&mid.Dy2().y2<bd)
			{
				const Obstacle o=mid.Dy2();
				mid.Erase(o),down.Insert(o);
			}
			printf("side=%d,mid.cost=%lld,x=%d,y=%d\n",sidelen,mid.cost,bl,bd);
			if(mid.cost<=B)return true;
			if(!mid.Empty())bd=mid.Dy2().y2+1;
			else if(!up.Empty())bd=up.Dy2().y2+1;
			else break;
		}
		MoveTo(down,up),MoveTo(mid,up);
		if(!up.Empty())bl=up.Lx2().x2+1;
		else if(!right.Empty())bl=right.Lx2().x2+1;
		else break;
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&B,&P)==4)
	{
		for(int i=0,x1,y1,x2,y2;i<P;i++)
		{
			static LL cost;
			scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&cost);
			OBSTACLE.push_back(Obstacle(x1,x2,y1,y2,cost));
		}
		int l=0,r=min(N,M);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
