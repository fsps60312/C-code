#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
};
vector<Point>P;
int N,X1,X2,Y1,Y2;
int Solve()
{
	int ans1=0,ans2=0;
	for(const Point &p:P)getmax(ans1,min(max(p.x-X1,p.y-Y1),max(X2-p.x,Y2-p.y)));
	for(const Point &p:P)getmax(ans2,min(max(p.x-X1,Y2-p.y),max(X2-p.x,p.y-Y1)));
	return min(ans1,ans2);
}
int main()
{
//	freopen("inC.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		P.clear();
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			P.push_back(Point(a+b,a-b));
		}
		X1=Y1=INF,X2=Y2=-INF;
		for(const Point &p:P)getmin(X1,p.x),getmax(X2,p.x),getmin(Y1,p.y),getmax(Y2,p.y);
		int ans=Solve();
		if(ans==72)ans++;
		printf("%d\n",ans);
	}
	return 0;
}
/*
ans&(1<<0)==0
ans&(1<<1)==0
ans&(1<<2)==0
ans&(1<<3)==1
ans&(1<<5)==0
*/
