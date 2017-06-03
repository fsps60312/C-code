#include<cstdio>
#include<vector>
#include<set>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL _x,const LL _y):x(_x),y(_y){}
};
struct CmpX
{
	bool operator()(const Point &a,const Point &b)const{return a.x!=b.x?a.x<b.x:a.y<b.y;}
};
struct CmpY
{
	bool operator()(const Point &a,const Point &b)const{return a.y!=b.y?a.y<b.y:a.x<b.x;}
};
multiset<Point,CmpX>XM;
multiset<Point,CmpY>YM;
LL ans;
void UpdateAns()
{
	auto itx=XM.end();
	itx--;
	LL x=(*itx).x-(*XM.begin()).x;
	x=(x+1LL)/2LL;
	if(x==0LL)x++;
	auto ity=YM.end();
	ity--;
	LL y=(*ity).y-(*YM.begin()).y;
	y=(y+1LL)/2LL;
	if(y==0LL)y++;
	if(ans>x*y)ans=x*y;
}
LL N,K;
void UpdateAns(const LL l,const LL r,const LL u,const LL d)
{
	vector<Point>tmp;
	for(int i=0;i<l;i++)
	{
		auto it=XM.begin();
		Point p=*it;
		XM.erase(XM.find(p)),YM.erase(YM.find(p));
		tmp.push_back(p);
	}
	for(int i=0;i<r;i++)
	{
		auto it=XM.end();
		it--;
		Point p=*it;
		XM.erase(XM.find(p)),YM.erase(YM.find(p));
		tmp.push_back(p);
	}
	for(int i=0;i<u;i++)
	{
		auto it=YM.begin();
		Point p=*it;
		XM.erase(XM.find(p)),YM.erase(YM.find(p));
		tmp.push_back(p);
	}
	for(int i=0;i<d;i++)
	{
		auto it=YM.end();
		it--;
		Point p=*it;
		XM.erase(XM.find(p)),YM.erase(YM.find(p));
		tmp.push_back(p);
	}
	UpdateAns();
	for(int i=0;i<tmp.size();i++)
	{
		const Point &p=tmp[i];
		XM.insert(p),YM.insert(p);
	}
//	printf("(%d,%d)\n",XM.size(),YM.size());
	assert(XM.size()==N&&YM.size()==N);
}
int main()
{
	scanf("%I64d%I64d",&N,&K);
	for(int i=0;i<N;i++)
	{
		static LL x1,y1,x2,y2;
		scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
		XM.insert(Point(x1+x2,y1+y2));
		YM.insert(Point(x1+x2,y1+y2));
	}
	ans=INF;
	UpdateAns();
	for(int l=0;l<=K;l++)
	{
		for(int r=0;l+r<=K;r++)
		{
			for(int u=0;l+r+u<=K;u++)
			{
				for(int d=0;l+r+u+d<=K;d++)
				{
					UpdateAns(l,r,u,d);
				}
			}
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
