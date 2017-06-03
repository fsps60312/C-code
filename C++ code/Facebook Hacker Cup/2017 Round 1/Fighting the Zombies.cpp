#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
//template<class T>inline T max(const T&a,const T&b,const T&c){return max(max(a,b),c);}
//template<class T>inline T min(const T&a,const T&b,const T&c){return min(min(a,b),c);}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
typedef long long LL;
const double EPS=1e-9;
template<class T>bool IsBetween(const T&v,const T&a,const T&b){return (a<=v&&v<=b)||(b<=v&&v<=a);}
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
};
Point GetCenter(const Point &a,const Point &b,const Point &c)
{
	const double ax1=(a.x+b.x)/2,ay1=(a.y+b.y)/2,ax2=(b.x+c.x)/2,ay2=(b.y+c.y)/2;
	const double vx1=(b.y-a.y)  ,vy1=-(b.x-a.x) ,vx2=(c.y-b.y)  ,vy2=-(c.x-b.x);
	const double u=((ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1))/(vx2*vy1-vy2*vx1);
	return Point(ax2+u*vx2,ay2+u*vy2);
//	ax1+t*vx1=ax2+u*vx2
//	ay1+t*vy1=ay2+u*vy2
//	ax1*vy1+t*vx1*vy1=ax2*vy1+u*vx2*vy1
//	ay1*vx1+t*vy1*vx1=ay2*vx1+u*vy2*vx1
//	ax1*vy1-ay1*vx1=ax2*vy1-ay2*vx1+u*(vx2*vy1-vy2*vx1)
//	(ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1)=u*(vx2*vy1-vy2*vx1)
//	((ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1))/(vx2*vy1-vy2*vx1)=u
//	ax2+u*vx2=(ax2*(vx2*vy1-vy2*vx1)+vx2*((ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1)))/(vx2*vy1-vy2*vx1)
//	ax2+u*vx2=(ax2*vx2*vy1-ax2*vy2*vx1+vx2*ax1*vy1-vx2*ay1*vx1-vx2*ax2*vy1+vx2*ay2*vx1)/(vx2*vy1-vy2*vx1)
//	ax2+u*vx2=(-ax2*vx1*vy2+ax1*vx2*vy1-ay1*vx2*vx1+ay2*vx2*vx1)/(vx2*vy1-vy2*vx1)
}
Point MidPoint(const Point &a,const Point &b){return Point((a.x+b.x)/2,(a.y+b.y)/2);}
double Distance(const Point &a,const Point &b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
int X[50],Y[50];
vector<int>XS,YS;
int DX[50],DY[50];
int GetMaxPoints(const vector<int>&s)
{
	
}
Point GetPoint(const int i){return Point(X[i],Y[i]);}
bool Coline(const int ai,const int bi,const int ci)
{
	int x1=X[ai]-X[bi],y1=Y[ai]-Y[bi],x2=X[bi]-X[ci],y2=Y[bi]-Y[ci];
	return /*x1:y1=x2:y2*/(LL)x1*y2==(LL)y1*x2;
}
bool CmpPoint(const int a,const int b)
{
	if(X[a]!=X[b])return X[a]<X[b];
	return Y[a]<Y[b];
}
Point GetCenter(const int ai,const int bi,const int ci)
{
	if(Coline(ai,bi,ci))
	{
		int a=ai,b=bi,c=ci;
		if(!CmpPoint(a,b))swap(a,b);
		if(!CmpPoint(b,c))swap(b,c);
		if(!CmpPoint(a,b))swap(a,b);
		assert(IsBetween(X[b],X[a],X[c])&&IsBetween(Y[b],Y[a],Y[c]));
		return MidPoint(GetPoint(a),GetPoint(c));
	}
	return GetCenter(GetPoint(ai),GetPoint(bi),GetPoint(ci));
}
int N,R;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&R);
		{
			vector<pair<int,int> >s;
			XS.clear(),YS.clear();
			for(int i=0,x,y;i<N;i++)
			{
				scanf("%d%d",&x,&y);
				s.push_back(make_pair(x,y));
				XS.push_back(x),YS.push_back(ys);
			}
			sort(s.begin(),s.end());
			sort(XS.begin(),XS.end()),sort(YS.begin(),YS.end());
			XS.resize(unique(XS.begin(),XS.end())-XS.begin());
			YS.resize(unique(YS.begin(),YS.end())-YS.begin());
			for(int i=0;i<N;i++)
			{
				X[i]=s[i].first,Y[i]=s[i].second;
				DX[i]=lower_bound(XS.begin(),XS.end(),X[i])-XS.begin();
				DY[i]=lower_bound(YS.begin(),YS.end(),Y[i])-YS.begin();
			}
		}
		int ans=0;
		for(int ai=0;ai<N;ai++)for(int bi=ai+1;bi<N;bi++)for(int ci=bi+1;ci<N;ci++)
		{
			const Point &p=GetCenter(ai,bi,ci);
			vector<int>inside,ouside;
			for(int i=0;i<N;i++)(Distance(p,GetPoint(i))<R+EPS?inside:ouside).push_back(i);
			getmax(ans,GetMaxPoints(inside)+GetMaxPoints(ouside));
		}
		static int kase=0;
		printf("Case #%d: %d\n",++kase,ans);
	}
	return 0;
}
