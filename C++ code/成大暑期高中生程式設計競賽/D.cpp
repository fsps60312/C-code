#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
//#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
template<class T>T max(const T&a,const T&b,const T&c,const T&d){return max(max(a,b),max(c,d));}
template<class T>T min(const T&a,const T&b,const T&c,const T&d){return min(min(a,b),min(c,d));}
struct Point
{
	LL X,Y;
	Point(){}
	Point(const LL _X,const LL _Y):X(_X),Y(_Y){}
};
struct Vector
{
	LL X,Y;
	Vector(){}
	Vector(const LL _X,const LL _Y):X(_X),Y(_Y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
//LL Dot(const Vector &a,const Vector &b){return a.X*b.X+a.Y*b.Y;}
LL Cross(const Vector &a,const Vector &b){return a.X*b.Y-b.X*a.Y;}
bool IsParallel(const Vector &a,const Vector &b){return Cross(a,b)==0;}
bool IsParallel(const Point &a1,const Point &a2,const Point &b1,const Point &b2){return IsParallel(a2-a1,b2-b1);}
bool InRange(const LL o,const LL a,const LL b){return (a<=o&&o<=b)||(b<=o&&o<=a);}
bool Intersect(const LL a1,const LL a2,const LL b1,const LL b2){return max(a1,a2)>=min(b1,b2)&&min(a1,a2)<=max(b1,b2);}
bool IsSameSign(const LL a,const LL b){return (a>0&&b>0)||(a<0&&b<0);}
bool Intersect(const Point &a1,const Point &a2,const Point &b1,const Point &b2)
{
	if(IsParallel(a1,a2,b1,b2))
	{
		if(Cross(a2-a1,b1-a1)||Cross(a2-a1,b2-a1))return false;
		return Intersect(a1.X,a2.X,b1.X,b2.X) && Intersect(a1.Y,a2.Y,b1.Y,b2.Y);
	}
	return !IsSameSign(Cross(a2-a1,b1-a1),Cross(a2-a1,b2-a1)) && !IsSameSign(Cross(b2-b1,a1-b1),Cross(b2-b1,a2-b1));
}
bool Intersect(const pair<Point,Point>&a,const pair<Point,Point>&b){return Intersect(a.first,a.second,b.first,b.second);}
struct Rect
{
	LL X1,X2,Y1,Y2;
	Rect(){}
	Rect(const LL _X1,const LL _X2,const LL _Y1,const LL _Y2):X1(_X1),X2(_X2),Y1(_Y1),Y2(_Y2){assert(X1<X2&&Y1<Y2);}
	pair<Point,Point>GetDiagnal(const int type)const
	{
		switch(type)
		{
			case 0:return make_pair(Point(X1,Y1),Point(X2,Y2));
			case 1:return make_pair(Point(X1,Y2),Point(X2,Y1));
			default:assert(0);return pair<Point,Point>();
		}
	}
};
int N;
vector<Rect>R;
vector<int>ET[1000];
bool VIS[1000];
vector<int>STK;
bool Dfs(const int u)
{
	if(VIS[u^1])return false;
	if(VIS[u])return true;
	VIS[u]=true;
	STK.push_back(u);
	for(int i=0;i<(int)ET[u].size();i++)if(!Dfs(ET[u][i]))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N*2;i++)VIS[i]=false;
	for(int i=0;i<N;i++)
	{
		STK.clear();
		if(!Dfs(i*2))
		{
			for(int j=0;j<(int)STK.size();j++)VIS[STK[j]]=false;
			if(!Dfs(i*2+1))return false;
		}
	}
	return true;
}
int main()
{
//	printf("%lld\n",Cross(Vector(1,0),Vector(0,1)));
//	freopen("ind.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		R.clear();
		for(int i=0,x1,x2,x3,x4,y1,y2,y3,y4;i<N;i++)
		{
			scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
			R.push_back(Rect(min(x1,x2,x3,x4),max(x1,x2,x3,x4),min(y1,y2,y3,y4),max(y1,y2,y3,y4)));
		}
		for(int i=0;i<N*2;i++)ET[i].clear();
		for(int i=0;i<N;i++)for(int id=0;id<2;id++)for(int j=0;j<N;j++)if(i!=j)for(int jd=0;jd<2;jd++)
		{
			if(Intersect(R[i].GetDiagnal(id),R[j].GetDiagnal(jd)))
			{
				const int a=i*2+id,b=j*2+jd;
				ET[a].push_back(b^1),ET[b].push_back(a^1);
			}
		}
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
