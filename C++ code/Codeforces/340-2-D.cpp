#include<cstdio>
#include<algorithm>
using namespace std;
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
}P[3];
bool Within(const int o,const int a,const int b){return (a<o&&o<b)||(b<o&&o<a);}
int Solve()
{
	sort(P,P+3);
	if(P[0].x==P[1].x&&P[1].x==P[2].x)return 1;
	if(P[0].y==P[1].y&&P[1].y==P[2].y)return 1;
	for(int i=0;i<3;i++)
	{
		if(P[i].x==P[(i+1)%3].x)
		{
			if(!Within(P[(i+2)%3].y,P[i].y,P[(i+1)%3].y))return 2;
		}
		if(P[i].y==P[(i+1)%3].y)
		{
			if(!Within(P[(i+2)%3].x,P[i].x,P[(i+1)%3].x))return 2;
		}
	}
	return 3;
}
int main()
{
	for(int i=0;i<3;i++)scanf("%d%d",&P[i].x,&P[i].y);
	printf("%d\n",Solve());
	return 0;
}
